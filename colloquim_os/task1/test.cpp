#include "pch.h"
#include "fibonacci.h"

TEST(FibTest, Inv_arg) 
{
    EXPECT_THROW(fibonacci(-100), std::invalid_argument);
    EXPECT_THROW(fibonacci(0), std::invalid_argument);
    
}

TEST(FibTest, All_is_correct)
{
    vector<long long> a = {0, 1, 1, 2, 3};
    vector<long long> res = fibonacci(5);
    EXPECT_EQ(res, a);
}

TEST(FibTest, Single_el) {
    vector<long long> a = {0};
    EXPECT_EQ(fibonacci(1), a);
}

