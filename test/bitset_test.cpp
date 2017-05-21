//
// Created by ZachZhang on 2017/5/21.
//

#include "bitset.h"
#include "gtest/gtest.h"

TEST(BitSetTest, test_initialization) {
    alg_club::BitSet bitSet(12);
    ASSERT_EQ(bitSet.size(), 12);
    ASSERT_FALSE(bitSet.any());
    ASSERT_FALSE(bitSet.all());

    alg_club::BitSet bitSet2("100100100");
    ASSERT_EQ(bitSet2.size(), 9);
    ASSERT_TRUE(bitSet2.any());
    ASSERT_FALSE(bitSet2.all());
    ASSERT_FALSE(bitSet2.test(0));
    ASSERT_FALSE(bitSet2.test(1));
    ASSERT_TRUE(bitSet2.test(2));
    ASSERT_FALSE(bitSet2.test(3));
    ASSERT_FALSE(bitSet2.test(4));
    ASSERT_TRUE(bitSet2.test(5));
    ASSERT_FALSE(bitSet2.test(6));
    ASSERT_FALSE(bitSet2.test(7));
    ASSERT_TRUE(bitSet2.test(8));
}

TEST(BitSetTest, test_sets) {
    alg_club::BitSet bitSet("100000010");
    ASSERT_FALSE(bitSet.test(0));
    bitSet.set(0);
    ASSERT_TRUE(bitSet.test(0));
    ASSERT_FALSE(bitSet.test(4));
    bitSet.set(4);
    ASSERT_TRUE(bitSet.test(4));
    bitSet.unset(4);
    ASSERT_FALSE(bitSet.test(4));
    bitSet.unset(1);
    ASSERT_FALSE(bitSet.test(1));
}

