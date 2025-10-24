#include "pch.h"
#include"list.h"

vector<int> list_to_vec(const myList& lst) {
    vector<int> res;
    const Node* cur = lst.getHead();
    while (cur) {
        res.push_back(cur->info);
        cur = cur->next;
    }
    return res;
}

TEST(ListTest, Empty_list)
{
    myList lst;
    EXPECT_EQ(list_to_vec(lst), (vector<int>{}));

}

TEST(ListTest, Usual_list)
{
    myList lst;
    lst.add_el(10);
    lst.add_el(9);
    lst.add_el(3);
    EXPECT_EQ(list_to_vec(lst), (vector<int>{10, 9, 3}));
}

TEST(ListTest, Reverse_list)
{
    myList lst;
    lst.add_el(10);
    lst.add_el(9);
    lst.add_el(3);
    lst.reverse();
    EXPECT_EQ(list_to_vec(lst), (vector<int>{3,9,10}));
}
