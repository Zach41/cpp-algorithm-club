//
// Created by ZachZhang on 2017/5/21.
//

#ifndef ALGORITHM_CLUB_BITSET_H
#define ALGORITHM_CLUB_BITSET_H

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <vector>

namespace alg_club {
    struct BitSet {
        friend std::ostream &operator<<(std::ostream &os, const BitSet& bitset);
    public:
        BitSet(size_t num_bits) {
            m_size = num_bits;
            m_bytes = m_size / 8 + 1;
            m_bits = std::vector<uint8_t >(m_bytes, 0);
        }

        BitSet(const std::string &bits, char zero = '0', char one = '1'):
                BitSet(bits.size()) {
            uint8_t num = 0;
            size_t cnt = 0, idx = 0;

            for (size_t i = bits.size() - 1; ; i--) {
                if (bits[i] == zero) {
                    num <<= 1U;
                } else if (bits[i] == one) {
                    num = (num << 1U) | 1U;
                } else {
                    throw std::runtime_error("invalid argument.");
                }
                cnt += 1;
                if (cnt == 8) {
                    m_bits[idx] = num;
                    idx += 1;
                    cnt = 0, num = 0;
                }
                if (i == 0)
                    break;
            }
            if (num != 0) {
                num = num << static_cast<uint8_t >(8 - cnt);
                m_bits[idx] = num;
            }
        }

        BitSet(const char* bits, char zero = '0', char one = '1'):
                BitSet(std::string(bits), zero, one) {}

        BitSet(const BitSet&) = delete;
        BitSet(BitSet&&) = delete;
        BitSet &operator=(const BitSet&) = delete;

        void set(size_t bit) {
            if (bit >= m_size)
                return;;
            size_t idx = bit / 8;
            uint8_t off = static_cast<uint8_t >(bit % 8);
            m_bits[idx] |= (128U >> off);
        }

        void unset(size_t bit) {
            if (bit >= m_size)
                return;
            size_t idx = bit / 8;
            uint8_t off = static_cast<uint8_t >(bit % 8);
            m_bits[idx] &= ~(128U >> off);
        }

        bool test(size_t bit) {
            if (bit >= m_size)
                return false;
            size_t idx = bit / 8;
            uint8_t off = static_cast<uint8_t >(bit % 8);
            return (m_bits[idx] & (128U >> off)) != 0U;
        }

        size_t size() const {
            return m_size;
        }

        bool any() const {
            for (int8_t num: m_bits)
                if (num != 0)
                    return true;
            return false;
        }

        bool all() const {
            for (size_t i = 0; i < m_bytes - 1; i++) {
                if (m_bits[i] != 255U)
                    return false;
            }
            uint8_t num = 0;
            for (uint8_t off = 0; off <= static_cast<uint8_t >(m_size % 8); off++) {
                num |= 128U >> off;
            }
            if (m_bits[m_bytes - 1] != num)
                return false;
            return true;
        }

    private:
        size_t m_size;
        size_t m_bytes;
        std::vector<uint8_t> m_bits;
    };

    std::ostream& operator<<(std::ostream &os, const BitSet& bitset) {
        for (size_t i = bitset.m_bytes-1; ; i--) {
            uint8_t num = bitset.m_bits[i];
            for (uint8_t off = 0; off < 8; off++) {
                if ((num & (1U << off)) != 0U)
                    os << '1';
                else
                    os << '0';
            }
            if (i == 0)
                break;
        }
        return os;
    }
}
#endif //ALGORITHM_CLUB_BITSET_H
