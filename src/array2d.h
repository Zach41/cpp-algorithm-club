//
// Created by ZachZhang on 2017/5/16.
//

#ifndef ALGORITHM_CLUB_ARRAY2D_H
#define ALGORITHM_CLUB_ARRAY2D_H

#include <cstdint>
#include <cassert>
#include <type_traits>

namespace alg_club {
    template <typename T = char>
    struct Array2D {
        Array2D(uint32_t row, uint32_t col):
                NR(row), NC(col), array_data(new T[row * col]) {}
        Array2D(const Array2D& arr) = delete;
        Array2D(Array2D &&arr) = delete;
        Array2D &operator=(const Array2D &arr) = delete;

        ~Array2D() {
            delete[] array_data;
        }

        const uint32_t row() const {
            return NR;
        }
        const uint32_t col() const {
            return NC;
        }

        T& operator() (uint32_t row, uint32_t col) {
            assert(row < NR && col < NC);
            return array_data[NC * row + col];
        }
        const T &operator() (uint32_t row, uint32_t col) const {
            assert(row < NR && col < NC);
            return array_data[NC * row + col];
        }
        T* operator[] (uint32_t row) {
            assert(row < NR);
            return &(array_data[row*NC]);
        }
        const T* operator[] (uint32_t row) const {
            assert(row < NR);
            return &(array_data[row * NC]);
        }

        void clear(const T &value) {
            for (uint32_t idx = 0; idx < NR*NC; idx++)
                array_data[idx] = value;
        }

        template <typename std::enable_if<std::is_default_constructible<T>::value, int>::type = 0>
        void clear() {
            for (uint32_t idx = 0; idx < NR * NC; idx++)
                array_data[idx] = T();
        };

    private:
        uint32_t NR;
        uint32_t NC;
        T* array_data;
    };
}


#endif //ALGORITHM_CLUB_ARRAY2D_H
