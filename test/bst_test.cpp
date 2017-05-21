//
// Created by ZachZhang on 2017/5/21.
//

#include <iostream>
#include <sstream>

#include "binary_search_tree.h.h"
#include "gtest/gtest.h"

class BSTTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        bst.insert(5, "5");
        bst.insert(4, "4");
        bst.insert(6, "6");
        bst.insert(8, "8");
        bst.insert(8, "8");
        bst.insert(7, "7");
        bst.insert(1, "1");
    }

    alg_club::BST<int, std::string> bst;
};

TEST_F(BSTTest, find_test) {
    ASSERT_EQ(bst.find(1), "1");
    ASSERT_EQ(bst.find(8), "8");
    ASSERT_EQ(bst.find(7), "7");
    ASSERT_EQ(bst.find(4), "4");
    ASSERT_EQ(bst.find(6), "6");
    ASSERT_EQ(bst.find(5), "5");

    bool catched_exception = false;
    try {
        bst.find(9);
    } catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        catched_exception = true;
    }
    ASSERT_TRUE(catched_exception);
}

TEST_F(BSTTest, print_test) {
    std::string expected = "[1: 1] [4: 4] [5: 5] [6: 6] [7: 7] [8: 8] [8: 8] ";
    std::ostringstream out;
    out << bst;
    ASSERT_EQ(expected, out.str());
}

TEST_F(BSTTest, delete_test) {
    ASSERT_FALSE(bst.deleteKey(10));
    ASSERT_TRUE(bst.deleteKey(1));
    bool catched_exception = false;
    try {
        bst.find(1);
    } catch (std::runtime_error err) {
        std::cout << err.what() << std::endl;
        catched_exception = true;
    }
    ASSERT_TRUE(catched_exception);
}