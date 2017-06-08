#include "avl_tree.h"

#include "gtest/gtest.h"

#include <cmath>

class AVLTreeTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        avlTree.insert(3);
        avlTree.insert(4);
        avlTree.insert(1);
        avlTree.insert(2);
        avlTree.insert(7);
        avlTree.insert(6);
        avlTree.insert(8);
        avlTree.insert(5);
    }

    alg_club::AVLTree<int> avlTree;
};

template <typename T>
void test_height(alg_club::AVLTreeNode<T> *root) {
    int left_h = root -> left ? root -> left -> height : 0;
    int right_h = root -> right ? root -> right -> height : 0;
    ASSERT_TRUE(std::abs((right_h - left_h)) <= 1);
    if (root -> left != nullptr)
        test_height(root -> left);
    if (root -> right != nullptr)
        test_height(root -> right);
}

TEST_F(AVLTreeTest, height_test) {
    test_height(avlTree.root);
}