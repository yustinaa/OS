#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest/doctest.h"
#include "core.h"

TEST_CASE("empty array") {
    std::vector<int> data;

    CHECK(find_min(data) == 0);
    CHECK(find_max(data) == 0);
    CHECK(count_average(data) == 0.0);
}

TEST_CASE("all elements are equal") {
    std::vector<int> data = { 5, 5, 5, 5, 5 };

    CHECK(find_min(data) == 5);
    CHECK(find_max(data) == 5);
    CHECK(count_average(data) == doctest::Approx(5.0));
}

TEST_CASE("negative numbers") {
    std::vector<int> data = { -3, -7, -1, -9 };

    CHECK(find_min(data) == -9);
    CHECK(find_max(data) == -1);
    CHECK(count_average(data) == doctest::Approx(-5.0));
}

TEST_CASE("replace min and max with average") {
    std::vector<int> data = { 1, 5, 10 };
    double avg = count_average(data);
    replace_min_max_av(data, avg);

    CHECK(data[0] == 5); // min заменён
    CHECK(data[2] == 5); // max заменён
    CHECK(data[1] == 5); 
}

TEST_CASE("multiple min and max") {
    std::vector<int> data = { 3, 9, 3, 5, 9 };
    double avg = count_average(data); 
    replace_min_max_av(data, avg);

    CHECK(data[0] == 5);
    CHECK(data[2] == 5);
    CHECK(data[1] == 5);
    CHECK(data[4] == 5);
    CHECK(data[3] == 5);
}
