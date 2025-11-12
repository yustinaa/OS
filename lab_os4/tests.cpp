#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "sync_manager.h"
#include <windows.h>
#include <thread>
#include <chrono>

TEST_SUITE("S_Manager Tests") {

    TEST_CASE("Initialization and basic properties") {
        S_Manager manager("test_init.bin", 5);

        CHECK(manager.getNumRecords() == 5);
    }

    TEST_CASE("Single process write and read") {
        std::remove("test_single.bin");
        S_Manager manager("test_single.bin", 3);

        SUBCASE("Write message") {
            CHECK(manager.writeMessage("Hello") == true);
            CHECK(manager.writeMessage("World") == true);
            CHECK(manager.writeMessage("Test") == true);
        }

        SUBCASE("Read messages in order") {
            manager.writeMessage("First");
            manager.writeMessage("Second");

            std::string msg;
            CHECK(manager.readMessage(msg) == true);
            CHECK(msg == "First");

            CHECK(manager.readMessage(msg) == true);
            CHECK(msg == "Second");
        }
    }

    TEST_CASE("Message length limits") {
        std::remove("test_length.bin");
        S_Manager manager("test_length.bin", 2);

        SUBCASE("Short message") {
            CHECK(manager.writeMessage("Short") == true);
        }

    }

    TEST_CASE("Circular buffer behavior") {
        std::remove("test_circular.bin");
        S_Manager manager("test_circular.bin", 2);

        manager.writeMessage("Msg1");
        manager.writeMessage("Msg2");

        std::string msg;
        manager.readMessage(msg); 

        CHECK(manager.writeMessage("Msg3") == true);
    }
}
