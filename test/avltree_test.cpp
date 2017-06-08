#include "avl_tree.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <cmath>
#include <vector>

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

// template <typename T>
// void test_height(alg_club::AVLTreeNode<T> *root) {
//     int left_h = root -> left ? root -> left -> height : 0;
//     int right_h = root -> right ? root -> right -> height : 0;
//     ASSERT_TRUE(std::abs((right_h - left_h)) <= 1);
//     if (root -> left != nullptr)
//         test_height(root -> left);
//     if (root -> right != nullptr)
//         test_height(root -> right);
// }

TEST_F(AVLTreeTest, height_test) {
    ASSERT_EQ(avlTree.height(), 4);
    // test_height(avlTree.root);
}

TEST_F(AVLTreeTest, pre_order_test) {
    std::vector<int> preorder_vec;
    avlTree.preOrder(preorder_vec);
    ASSERT_THAT(preorder_vec, ::testing::ElementsAre(3, 1, 2, 6, 4, 5, 7, 8));
}

TEST_F(AVLTreeTest, in_order_test) {
    std::vector<int> inorder_vec;
    avlTree.inOrder(inorder_vec);
    ASSERT_THAT(inorder_vec, ::testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));    
}

TEST_F(AVLTreeTest, post_order_test) {
    std::vector<int> postorder_vec;
    avlTree.postOrder(postorder_vec);
    ASSERT_THAT(postorder_vec, ::testing::ElementsAre(2, 1, 5, 4, 8, 7, 6, 3));
}

TEST_F(AVLTreeTest, search_test) {
    auto node9 = avlTree.search(9);
    ASSERT_FALSE(node9);

    auto node1 = avlTree.search(1);
    ASSERT_TRUE(node1);
    ASSERT_EQ(node1 -> key, 1);
    ASSERT_TRUE(node1 -> right);
    ASSERT_EQ(node1 -> right -> key, 2);

    auto node6 = avlTree.search(6);
    ASSERT_TRUE(node6);
    ASSERT_EQ(node6 -> key, 6);
    ASSERT_TRUE(node6 -> left);
    ASSERT_TRUE(node6 -> right);
    ASSERT_EQ(node6 -> left -> key, 4);
    ASSERT_EQ(node6 -> right -> key, 7);
}

TEST_F(AVLTreeTest, minimum_test) {
    ASSERT_EQ(avlTree.minimum(), 1);
    alg_club::AVLTree<int> empty_tree;
    ASSERT_THROW(empty_tree.minimum(), std::runtime_error);
}

TEST_F(AVLTreeTest, maximum_test) {
    ASSERT_EQ(avlTree.maximum(), 8);
    alg_club::AVLTree<int> empty_tree;
    ASSERT_THROW(empty_tree.maximum(), std::runtime_error);
}

TEST_F(AVLTreeTest, insert_test) {
    ASSERT_THROW(avlTree.insert(3), std::runtime_error);
    ASSERT_NO_THROW(avlTree.insert(9));
    ASSERT_THROW(avlTree.insert(9), std::runtime_error);
    ASSERT_EQ(avlTree.height(), 4);

    std::vector<int> preorder_vec;
    std::vector<int> postorder_vec;
    avlTree.preOrder(preorder_vec);
    avlTree.postOrder(postorder_vec);
    ASSERT_THAT(preorder_vec, ::testing::ElementsAre(3, 1, 2, 6, 4, 5, 8, 7, 9));
    ASSERT_THAT(postorder_vec, ::testing::ElementsAre(2, 1, 5, 4, 7, 9, 8, 6, 3));
}

TEST_F(AVLTreeTest, remove_test) {
    ASSERT_THROW(avlTree.remove(0), std::runtime_error);
    ASSERT_NO_THROW(avlTree.remove(2));
    std::vector<int> preorder_vec;
    std::vector<int> postorder_vec;
    avlTree.preOrder(preorder_vec);
    avlTree.postOrder(postorder_vec);
    ASSERT_THAT(preorder_vec, ::testing::ElementsAre(4, 3, 1, 6, 5, 7, 8));
    ASSERT_THAT(postorder_vec, ::testing::ElementsAre(1, 3, 5, 8, 7, 6, 4));

    ASSERT_THROW(avlTree.remove(2), std::runtime_error);

    ASSERT_NO_THROW(avlTree.remove(6));
    preorder_vec.clear();
    postorder_vec.clear();
    avlTree.preOrder(preorder_vec);
    avlTree.postOrder(postorder_vec);
    ASSERT_THAT(preorder_vec, ::testing::ElementsAre(4, 3, 1, 7, 5, 8));
    ASSERT_THAT(postorder_vec, ::testing::ElementsAre(1, 3, 5, 8, 7, 4));
}