#include "marker_thread.h"
#include "sync.h"
#include <iostream>
#include<vector>
#include <windows.h>
#include<string>
using namespace std;

DWORD WINAPI markerThread(LPVOID param) {
    ThreadParams* p = static_cast<ThreadParams*>(param);
    int id = p->markerId;
    std::vector<int>& arr = *p->array;

    HANDLE startEvent = p->startEvent;
    HANDLE resumeEvent = p->continueEvent;
    HANDLE stopEvent = p->stopEvent;
    HANDLE doneEvent = p->finishedEvent;
    HANDLE arrayMutex = p->arrayMutex;
    CRITICAL_SECTION* cs = p->cs;

    std::vector<int> marked;
    srand(id);

    WaitForSingleObject(startEvent, INFINITE);

    while (true) {
        int index = rand() % arr.size();

        WaitForSingleObject(arrayMutex, INFINITE);

        if (arr[index] == 0) {
            Sleep(5);
            arr[index] = id;
            marked.push_back(index);
            Sleep(5);
            ReleaseMutex(arrayMutex);
            continue;
        }

        ReleaseMutex(arrayMutex);


        EnterCriticalSection(cs);
       
        p->messages.push_back("[Marker " + std::to_string(id) + "] can't mark index "
            + std::to_string(index) + ", total marked: "
            + std::to_string(marked.size()));
        LeaveCriticalSection(cs);

        SetEvent(doneEvent);

        HANDLE events[2] = { resumeEvent, stopEvent };
        DWORD res = WaitForMultipleObjects(2, events, FALSE, INFINITE);

        if (res == WAIT_OBJECT_0 + 1) { // stop
            WaitForSingleObject(arrayMutex, INFINITE);
            for (int idx : marked) arr[idx] = 0;
            ReleaseMutex(arrayMutex);
            return 0;
        }
        else {

            ResetEvent(doneEvent);
        }
    }
}


