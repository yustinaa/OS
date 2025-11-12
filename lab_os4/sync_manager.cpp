#include "sync_manager.h"
#include <iostream>

const char* MUTEX_NAME = "Global\\MsgFileMutex";
const char* SEM_FREE_NAME = "Global\\MsgFree";
const char* SEM_FULL_NAME = "Global\\MsgFull";
const char* READY_EVENT_PREFIX = "Global\\SenderReady_";


S_Manager::S_Manager(const std::string& filename, int numRecords): filename(filename), numRecords(numRecords)
{
    hMutex = CreateMutex(nullptr, FALSE, MUTEX_NAME);
    hFree = CreateSemaphore(nullptr, numRecords, numRecords, SEM_FREE_NAME);
    hFull = CreateSemaphore(nullptr, 0, numRecords, SEM_FULL_NAME);

    std::ofstream file(filename, std::ios::binary | std::ios::trunc);
    Message empty{};
    for (int i = 0; i < numRecords; ++i)
        file.write(reinterpret_cast<const char*>(&empty), sizeof(Message));
}

S_Manager::~S_Manager() {
    if (hMutex) CloseHandle(hMutex);
    if (hFree) CloseHandle(hFree);
    if (hFull) CloseHandle(hFull);
}

bool S_Manager::signalReady(int senderId) {
    std::string eventName = READY_EVENT_PREFIX + std::to_string(senderId);
    HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, eventName.c_str());

    if (hEvent) {
        SetEvent(hEvent);
        CloseHandle(hEvent);
        return true;
    }
    return false;
}

bool S_Manager::waitAllSendersReady(int numSenders) {
    std::vector<HANDLE> events;

    for (int i = 0; i < numSenders; ++i) {
        std::string eventName = READY_EVENT_PREFIX + std::to_string(i);
        HANDLE hEvent = CreateEvent(nullptr, TRUE, FALSE, eventName.c_str());
        if (hEvent) {
            events.push_back(hEvent);
        }
    }
    if (events.empty()) {
        return false;
    }

    DWORD result = WaitForMultipleObjects(events.size(), events.data(), TRUE, INFINITE);

    for (HANDLE hEvent : events) {
        CloseHandle(hEvent);
    }

    return (result != WAIT_FAILED);
}


bool S_Manager::writeMessage(const std::string& msg) {
    WaitForSingleObject(hFree, INFINITE);
    WaitForSingleObject(hMutex, INFINITE);

    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    Message message{};
    strcpy_s(message.text, msg.c_str());

    Message cell{};
    for (int i = 0; i < numRecords; ++i) {
        file.seekg(i * sizeof(Message));
        file.read(reinterpret_cast<char*>(&cell), sizeof(Message));
        if (cell.text[0] == '\0') {
            file.seekp(i * sizeof(Message));
            file.write(reinterpret_cast<char*>(&message), sizeof(Message));
            break;
        }
    }

    file.close();
    ReleaseMutex(hMutex);
    ReleaseSemaphore(hFull, 1, nullptr);
    return true;
}

bool S_Manager::readMessage(std::string& outMsg) {
    WaitForSingleObject(hFull, INFINITE);
    WaitForSingleObject(hMutex, INFINITE);

    std::fstream file(filename, std::ios::in | std::ios::out | std::ios::binary);
    Message msg{};
    for (int i = 0; i < numRecords; ++i) {
        file.seekg(i * sizeof(Message));
        file.read(reinterpret_cast<char*>(&msg), sizeof(Message));
        if (msg.text[0] != '\0') {
            outMsg = msg.text;
            Message empty{};
            file.seekp(i * sizeof(Message));
            file.write(reinterpret_cast<char*>(&empty), sizeof(Message));
            break;
        }
    }

    file.close();
    ReleaseMutex(hMutex);
    ReleaseSemaphore(hFree, 1, nullptr);
    return true;
}
