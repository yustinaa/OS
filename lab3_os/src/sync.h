#pragma once
#include <windows.h>
#include <vector>
#include<string>


struct ThreadParams {
    int markerId;
    std::vector<int>* array;

    HANDLE startEvent;
    HANDLE continueEvent;
    HANDLE stopEvent;
    HANDLE finishedEvent;

    HANDLE arrayMutex;

    CRITICAL_SECTION* cs;
    std::vector<std::string> messages;
};
