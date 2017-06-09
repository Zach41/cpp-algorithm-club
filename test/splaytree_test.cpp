#include "splay_tree.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <vector>

class SplayTreeTest: public ::testing::Test {
protected:
    virtual void SetUp() {
        splayTree.insert(3);
        splayTree.insert(4);
        splayTree.insert(1);
        splayTree.insert(2);
        splayTree.insert(7);
        splayTree.insert(6);
        splayTree.insert(8);
        splayTree.insert(5);
    }

    alg_club::SplayTree<int> splayTree;
};

TEST_F(SplayTreeTest, test_orders) {
    std::vector<int> preorder_vec;
    std::vector<int> inorder_vec;
    std::vector<int> postorder_vec;

    splayTree.preOrder(preorder_vec);
    splayTree.inOrder(inorder_vec);
    splayTree.postOrder(postorder_vec);

    ASSERT_THAT(inorder_vec, ::testing::ElementsAre(1, 2, 3, 4, 5, 6, 7, 8));
    ASSERT_THAT(preorder_vec, ::testing::ElementsAre(5, 4, 3, 2, 1, 7, 6, 8));
    ASSERT_THAT(postorder_vec, ::testing::ElementsAre(1, 2, 3, 4, 6, 8, 7, 5));
}