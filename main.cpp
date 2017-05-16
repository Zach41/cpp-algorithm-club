#include <iostream>

#include "array2d.h"

using namespace alg_club;

int main() {
    Array2D<int> arr(3, 4);
    arr.clear();
    assert(arr(0, 0) == 0);
    arr(1, 1) = 1;
    assert(arr(1, 1) == 1);
    assert(*(arr[1] + 1) == 1);
    *(arr[1] + 2) = 2;
    assert(arr(1, 2) == 2);
    return 0;
}