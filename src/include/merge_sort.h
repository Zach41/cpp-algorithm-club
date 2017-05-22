//
// Created by ZachZhang on 2017/5/22.
//

#ifndef ALGORITHM_CLUB_MERGE_SORT_H
#define ALGORITHM_CLUB_MERGE_SORT_H

#include <cstddef>

namespace alg_club {
    using std::size_t;
    template <typename T>
    static void merge_(T *array, size_t left, size_t mid, size_t right) {
        T tmpArray[right - left + 1];
        size_t lpos = left, rpos = mid+1, idx = 0;
        while (lpos <= mid && rpos <= right) {
            if (array[lpos] < array[rpos])
                tmpArray[idx++] = array[lpos++];
            else
                tmpArray[idx++] = array[rpos++];
        }
        while (lpos <= mid)
            tmpArray[idx++] = array[lpos++];
        while (rpos <= right)
            tmpArray[idx++] = array[rpos++];

        for (size_t iter = 0; iter <right - left + 1; iter++)
            array[left + iter] = tmpArray[iter];
    }

    template <typename T>
    static void merge_sort(T *array, size_t left, size_t right) {
        size_t mid = left + (right - left) / 2;
        if (left < right) {
            merge_sort(array, left, mid);
            merge_sort(array, mid+1, right);
            merge_(array, left, mid, right);
        }
    }
}

#endif //ALGORITHM_CLUB_MERGE_SORT_H
