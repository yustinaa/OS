#pragma once
#include <windows.h>
#include <vector>

class SyncManager {
private:
    CRITICAL_SECTION cs;

    HANDLE startEvent;                  
    std::vector<HANDLE> markerWaitEvents;   
    std::vector<HANDLE> continueEvents;     
    std::vector<HANDLE> stopEvents;         
    std::vector<HANDLE> finishedEvents; 

public:
    std::vector<HANDLE> markerMutexes;

    int markerCount;

public:
    SyncManager(int count);
    ~SyncManager();

    void signalStart();

    void signalMarkerToContinue(int index);
    void signalMarkerToStop(int index);
    void waitForMarkerStop(int index);
    void markStopped(int index);


    void waitForAllMarkers();  
    void signalMarkerWaiting(int index);
    void resetAllMarkerWaiting();
    void waitForContinue(int index);

    void enterCriticalSection();
    void leaveCriticalSection();

    void waitForStart();

    bool waitForAllMarkers(DWORD timeoutMs = 50);

    void lockMarker(int index) { WaitForSingleObject(markerMutexes[index], INFINITE); }
    void unlockMarker(int index) { ReleaseMutex(markerMutexes[index]); }
};


struct ThreadParams {
    int markerId;
    std::vector<int>* array;
    SyncManager* syncManager;
    bool* stopFlag;
};

