#include <iostream>
#include <vector>
#include <stdexcept>
#include <windows.h>
#include "sync.h"
#include "marker_thread.h"

using namespace std;

int main()
{
    try {
        int n, markerCount;
        cout << "Enter array size: ";
        if (!(cin >> n) || n <= 0) throw runtime_error("Invalid array size!");

        cout << "Enter number of markers: ";
        if (!(cin >> markerCount) || markerCount <= 0) throw runtime_error("Invalid number of markers!");

        vector<int> array(n, 0);
        HANDLE arrayMutex = CreateMutex(NULL, FALSE, NULL);

        CRITICAL_SECTION cs;
        InitializeCriticalSection(&cs);

        vector<ThreadParams> params(markerCount);
        vector<HANDLE> threads(markerCount);
        vector<bool> alive(markerCount, true);

        for (int i = 0; i < markerCount; ++i) {
            params[i].markerId = i + 1;
            params[i].array = &array;
            params[i].cs = &cs;

            params[i].startEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
            params[i].continueEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
            params[i].stopEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
            params[i].finishedEvent = CreateEvent(NULL, TRUE, FALSE, NULL);

            params[i].arrayMutex = arrayMutex;

            threads[i] = CreateThread(NULL, 0, markerThread, &params[i], 0, NULL);
        }

        for (int i = 0; i < markerCount; ++i)
            SetEvent(params[i].startEvent);

        while (true) 
        {
            vector<HANDLE> doneEvents;
            for (int i = 0; i < markerCount; ++i)
                if (alive[i])
                    doneEvents.push_back(params[i].finishedEvent);

            if (!doneEvents.empty())
                WaitForMultipleObjects(doneEvents.size(), doneEvents.data(), TRUE, INFINITE);


            for (int i = 0; i < markerCount; ++i) {
                if (alive[i]) {
                    for (const auto& msg : params[i].messages)
                        std::cout << msg << "\n";
                    params[i].messages.clear();
                }
            }

            EnterCriticalSection(&cs);
            cout << "Array: ";
            for (int x : array) cout << x << " ";
            cout << "\n";
            LeaveCriticalSection(&cs);

            cout << "Choose marker to stop (1-" << markerCount << ", 0 to exit): ";
            int choice;
            cin >> choice;
            if (choice == 0) break;

            if (choice < 1 || choice > markerCount || !alive[choice - 1]) {
                cout << "Invalid marker.\n";
                continue;
            }

            int idx = choice - 1;
            SetEvent(params[idx].stopEvent);
            alive[idx] = false;
            WaitForSingleObject(threads[idx], INFINITE);
            cout << "Marker " << choice << " stopped.\n";

            for (int i = 0; i < markerCount; ++i)
                if (alive[i])
                    SetEvent(params[i].continueEvent);

            for (int i = 0; i < markerCount; ++i)
                if (alive[i])
                    ResetEvent(params[i].finishedEvent);
        }

        for (int i = 0; i < markerCount; ++i) {
            if (alive[i]) {
                SetEvent(params[i].stopEvent);
                SetEvent(params[i].continueEvent);
            }
        }

        for (int i = 0; i < markerCount; ++i) {
            WaitForSingleObject(threads[i], INFINITE);
            CloseHandle(threads[i]);
        }

        DeleteCriticalSection(&cs);
        CloseHandle(arrayMutex);

        cout << "All threads stopped.\n";

        cout << "Array: ";
        for (int x : array) cout << x << " ";
        cout << "\n";

        return 0;
    }
    catch (const exception& ex) {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
}
