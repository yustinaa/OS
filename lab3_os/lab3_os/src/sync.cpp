#include "sync.h"
#include <iostream>

SyncManager::SyncManager(int count): markerCount(count)
{
    InitializeCriticalSection(&cs);
    startEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);

    markerWaitEvents.resize(count);
    continueEvents.resize(count);
    stopEvents.resize(count);
    finishedEvents.resize(count);
    markerMutexes.resize(count);

    for (int i = 0; i < count; ++i) {
        markerWaitEvents[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        continueEvents[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        stopEvents[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        finishedEvents[i] = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        markerMutexes[i] = CreateMutex(nullptr, FALSE, nullptr);
    }
}

SyncManager::~SyncManager()
{
    DeleteCriticalSection(&cs);
    CloseHandle(startEvent);
    for (int i = 0; i < markerCount; ++i) {
        CloseHandle(markerWaitEvents[i]);
        CloseHandle(continueEvents[i]);
        CloseHandle(stopEvents[i]);
        CloseHandle(finishedEvents[i]);
        CloseHandle(markerMutexes[i]);
    }
}

void SyncManager::signalStart()
{
    SetEvent(startEvent);
}

void SyncManager::signalMarkerWaiting(int index) 
{
    SetEvent(markerWaitEvents[index]);
}

void SyncManager::waitForAllMarkers()
{
    WaitForMultipleObjects(markerCount, markerWaitEvents.data(), TRUE, INFINITE);
}

void SyncManager::signalMarkerToContinue(int index) 
{
    ResetEvent(markerWaitEvents[index]);
    SetEvent(continueEvents[index]);
}

void SyncManager::signalMarkerToStop(int index)
{
    SetEvent(stopEvents[index]);
}

void SyncManager::waitForMarkerStop(int index)
{
    WaitForSingleObject(finishedEvents[index], INFINITE);
}

void SyncManager::enterCriticalSection() 
{
    EnterCriticalSection(&cs);
}

void SyncManager::leaveCriticalSection()
{
    LeaveCriticalSection(&cs);
}

void SyncManager::resetAllMarkerWaiting()
{
    for (int i = 0; i < markerCount; ++i) {
        ResetEvent(markerWaitEvents[i]);
    }
}

void SyncManager::waitForContinue(int index)
{
    WaitForSingleObject(continueEvents[index], INFINITE);
    ResetEvent(continueEvents[index]);
}

void SyncManager::waitForStart()
{
    WaitForSingleObject(startEvent, INFINITE);
}

void SyncManager::markStopped(int index)
{
    SetEvent(finishedEvents[index]);
}

bool SyncManager::waitForAllMarkers(DWORD timeoutMs)
{
    std::vector<HANDLE> events(markerCount);
    for (int i = 0; i < markerCount; ++i) events[i] = markerWaitEvents[i];

    DWORD start = GetTickCount();
    while (true) {
        DWORD result = WaitForMultipleObjects(markerCount, events.data(), TRUE, timeoutMs);
        if (result >= WAIT_OBJECT_0 && result < WAIT_OBJECT_0 + markerCount) return true;

        if (GetTickCount() - start > 1000) return false;
    }
}

