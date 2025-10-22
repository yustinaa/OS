#include <iostream>
#include <vector>
#include <stdexcept>
#include <windows.h>
#include "sync.h"
#include "marker_thread.h"

using namespace std;

int main() {
    try {
        int n, markerCount;
        cout << "Enter array size: ";
        if (!(cin >> n) || n <= 0) {
            throw runtime_error("Invalid array size!");
        }

        cout << "Enter number of markers: ";
        if (!(cin >> markerCount) || markerCount <= 0) {
            throw runtime_error("Invalid number of markers!");
        }

        vector<int> array(n, 0);
        SyncManager syncManager(markerCount);

        vector<HANDLE> threads(markerCount);
        vector<ThreadParams> params(markerCount);

        vector<char> stopValues(markerCount, false);
        vector<bool*> stopFlags(markerCount);

        for (int i = 0; i < markerCount; ++i) {
            stopFlags[i] = reinterpret_cast<bool*>(&stopValues[i]);
            params[i].markerId = i + 1;
            params[i].array = &array;
            params[i].syncManager = &syncManager;
            params[i].stopFlag = stopFlags[i];

            threads[i] = CreateThread(nullptr, 0, markerThread, &params[i], 0, nullptr);
            if (!threads[i]) {
                throw runtime_error("Error creating thread ");
            }
        }

        syncManager.signalStart();

        while (true) {
            syncManager.waitForAllMarkers(50);

            cout << "\nArray: ";
            for (int x : array) cout << x << " ";
            cout << endl;

            cout << "Choose marker to stop (1- " << markerCount << ", 0 - exit): ";
            int choice;
            if (!(cin >> choice)) {
                throw runtime_error("Invalid input (not a number)");
            }

            if (choice == 0) break;
            if (choice < 1 || choice > markerCount) {
                cout << "Invalid marker index!" << endl;
                continue;
            }

            *stopFlags[choice - 1] = true;
            syncManager.signalMarkerToContinue(choice - 1);
            syncManager.waitForMarkerStop(choice - 1);

            cout << "Marker " << choice << " stopped." << endl;

            for (int i = 0; i < markerCount; ++i) {
                if (!(*stopFlags[i])) {
                    syncManager.signalMarkerToContinue(i);
                }
            }

            syncManager.resetAllMarkerWaiting();
        }

        for (int i = 0; i < markerCount; ++i) {
            if (!(*stopFlags[i])) {
                *stopFlags[i] = true;
                syncManager.signalMarkerToContinue(i);
            }
        }

        for (HANDLE h : threads) {
            WaitForSingleObject(h, INFINITE);
            CloseHandle(h);
        }

        cout << "\nFinal array state:\n";
        for (int x : array) cout << x << " ";
        cout << "\nAll threads finished. Exiting." << endl;
        return 0;
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
}
