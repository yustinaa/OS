#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "sync.h"
#include "marker_thread.h"
#include <vector>
#include <windows.h>

TEST_CASE("array initialization", "[array]") {
    int n = 10;
    std::vector<int> array(n, 0);
    for (int val : array) {
        REQUIRE(val == 0);
    }
}


TEST_CASE("single marker", "[marker]") {
    int n = 5;
    std::vector<int> array(n, 0);
    int markers = 1;
    SyncManager sync(markers);

    char stopVal = 0;
    bool* stopFlag = reinterpret_cast<bool*>(&stopVal);

    ThreadParams param;
    param.markerId = 1;
    param.array = &array;
    param.syncManager = &sync;
    param.stopFlag = stopFlag;

    HANDLE hThread = CreateThread(nullptr, 0, markerThread, &param, 0, nullptr);
    REQUIRE(hThread != nullptr);

    sync.signalStart();

    Sleep(50);

    *stopFlag = true;
    sync.signalMarkerToContinue(0); 
    WaitForSingleObject(hThread, INFINITE);
    CloseHandle(hThread);

    bool marked = false;
    for (int val : array) {
        if (val == 1) {
            marked = true;
            break;
        }
    }
    REQUIRE(marked);
}

TEST_CASE("multiple markers", "[marker]") {
    int n = 10;
    std::vector<int> array(n, 0);
    int markers = 3;
    SyncManager sync(markers);

    for (int m = 1; m <= markers; ++m) {
        bool stopFlag = false;
        ThreadParams param;
        param.markerId = m;
        param.array = &array;
        param.syncManager = &sync;
        param.stopFlag = &stopFlag;

        bool found = false;
        for (int i = 0; i < n; ++i) {
            if ((*param.array)[i] == 0) {
                (*param.array)[i] = param.markerId;
                found = true;
                break;
            }
        }

        REQUIRE(found); 
    }
}

