#include "marker_thread.h"
#include "sync.h"
#include <iostream>
#include<vector>
#include <windows.h>
#include<vector>
using namespace std;

DWORD WINAPI markerThread(LPVOID params) {
    ThreadParams* threadParams = static_cast<ThreadParams*>(params);
    int markerId = threadParams->markerId;
    vector<int>& array = *(threadParams->array);
    SyncManager& syncManager = *(threadParams->syncManager);
    bool& stopFlag = *(threadParams->stopFlag);

    syncManager.waitForStart();

    srand(markerId);
    int markedCount = 0;

    while (!stopFlag) {
        int randomNum = rand();
        int index = randomNum % array.size();

        WaitForSingleObject(syncManager.markerMutexes[markerId - 1], INFINITE);

        if (array[index] == 0) {
            Sleep(5);
            array[index] = markerId;
            Sleep(5);
            markedCount++;
            ReleaseMutex(syncManager.markerMutexes[markerId - 1]);
        }
        else {
            ReleaseMutex(syncManager.markerMutexes[markerId - 1]);

            std::cout << "Marker " << markerId
                << ": marked " << markedCount
                << " elements, cannot mark index " << index << std::endl;

            syncManager.signalMarkerWaiting(markerId - 1);

            syncManager.waitForContinue(markerId - 1);

            if (stopFlag) {
                syncManager.enterCriticalSection();
                for (size_t i = 0; i < array.size(); ++i) {
                    if (array[i] == markerId) array[i] = 0;
                }
                syncManager.leaveCriticalSection();

                syncManager.markStopped(markerId - 1);
                break;
            }
            else {
                syncManager.signalMarkerWaiting(markerId - 1);
            }
        }
    }

    return 0;
}
