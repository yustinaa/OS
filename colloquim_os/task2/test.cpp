#include "pch.h"

#include <gtest/gtest.h>
#include "palindrom.h"

TEST(PalindTest, EmptyVector)
{
    vector<int> a = {};
    EXPECT_TRUE(is_palind(a));
}

TEST(PalindTest, Single_el)
{
    vector<int> a = {8};
    EXPECT_TRUE(is_palind(a));
}

TEST(PalindTest, Coorect_even_palindrome)
{
    vector<int> a = {4,5,7,7,5,4};
    EXPECT_TRUE(is_palind(a));
}

TEST(PalindTest, Coorect_odd_palindrome)
{
    vector<int> a = {9,8,7,8,9};
    EXPECT_TRUE(is_palind(a));
}

TEST(PalindTest, Not_palindrome) {
    vector<int> a = {4,7,8,9,4,5};
    EXPECT_FALSE(is_palind(a));
}