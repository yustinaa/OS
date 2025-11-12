#pragma once
#include <windows.h>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct Message {
    char text[20];
};

class S_Manager {
public:
    S_Manager(const string& filename, int numRecords);
    ~S_Manager();

    bool writeMessage(const string& msg);
    bool readMessage(string& outMsg);
    static bool signalReady(int senderId);
    static bool waitAllSendersReady(int numSenders);

    int getNumRecords() const { return numRecords; }

private:
    string filename;
    int numRecords;

    HANDLE hMutex;
    HANDLE hFree;
    HANDLE hFull;
};
