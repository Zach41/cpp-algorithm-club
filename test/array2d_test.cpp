//
// Created by ZachZhang on 2017/5/17.
//

#include "array2d.h"
#include "gtest/gtest.h"

TEST(Array2dTest, simple_test) {
    alg_club::Array2D<int> arr(3, 4);

    arr.clear();
    ASSERT_EQ(arr(0, 0), 0);
    arr(1, 1) = 1;
    ASSERT_EQ(arr(1, 1), 1);
    ASSERT_EQ(*(arr[1] + 1), 1);
    *(arr[1] + 2) = 2;
    ASSERT_EQ(arr(1, 2), 2);
}