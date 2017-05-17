//
// Created by ZachZhang on 2017/5/17.
//

#ifndef ALGORITHM_CLUB_BASE64_H
#define ALGORITHM_CLUB_BASE64_H

#include <cstdint>
#include <cstring>
#include <string>

namespace alg_club {
    class CBase64 {
    public:
        static std::string decodeBase64(std::string input) {
            uint32_t output_num;
            uint8_t output[4];
            std::string decoded_str;
            uint32_t input_char[4];
            int cnt = 0;

            for (std::string::size_type i = 0; i < input.size(); i++) {
                input_char[cnt++] = indexOfCode(input[i]);

                if (cnt == 4) {
                    output_num = (static_cast<uint32_t>(input_char[0]) << 18) |
                                 (static_cast<uint32_t>(input_char[1]) << 12) |
                                 (static_cast<uint32_t>(input_char[2]) << 6) |
                                 static_cast<uint32_t>(input_char[3]);

                    output[0] = static_cast<uint8_t>((output_num & 0x00FF0000) >> 16);
                    output[1] = static_cast<uint8_t>((output_num & 0x0000FF00) >> 8);
                    output[2] = static_cast<uint8_t>(output_num & 0x000000FF);
                    output[3] = '\0';
                    decoded_str.append((char*)output);
                    cnt = 0;
                }
            }
            return decoded_str;
        }

        static std::string encodeBase64(uint8_t *input, int input_len) {
            const char *codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            uint8_t output[5];
            uint8_t tmp[3];
            uint32_t output_num;
            std::string encoded_str;
            int near = input_len % 3;

            for (int i = 0; i < input_len; i+=3) {
                memset(tmp, 0, 3);
                if (i + 3 <= input_len)
                    memcpy(tmp, input+i, 3);
                else {
                    memcpy(tmp, input+i, input_len - i);
                    output_num = (static_cast<uint32_t>(tmp[0]) << 16) |
                                 (static_cast<uint32_t>(tmp[1]) << 8) |
                                 (static_cast<uint32_t>(tmp[2]));

                    if (near == 1) {
                        output[0] = codes[(static_cast<uint8_t>(output_num >> 18) & 0x3F)];
                        output[1] = codes[(static_cast<uint8_t>(output_num >> 12) & 0x3F)];
                        output[2] = '=';
                        output[3] = '=';
                        output[4] = '\0';
                    }

                    if (near == 2) {
                        output[0] = codes[(static_cast<uint8_t>(output_num >> 18) & 0x3F)];
                        output[1] = codes[(static_cast<uint8_t>(output_num >> 12) & 0x3F)];
                        output[2] = codes[(static_cast<uint8_t>(output_num >> 6) & 0x3F)];
                        output[3] = '=';
                        output[4] = '\0';
                    }

                    encoded_str.append((char *)(output));
                    break;
                }
                output_num = (static_cast<uint32_t>(tmp[0]) << 16) |
                             (static_cast<uint32_t>(tmp[1]) << 8) |
                             (static_cast<uint32_t>(tmp[2]));
                output[0] = codes[(static_cast<uint8_t>(output_num >> 18) & 0xFF)];
                output[1] = codes[(static_cast<uint8_t>(output_num >> 12) & 0x3F)];
                output[2] = codes[(static_cast<uint8_t>(output_num >> 6) & 0x3F)];
                output[3] = codes[(static_cast<uint8_t>(output_num) & 0x3F)];
                output[4] = '\0';

                encoded_str.append((char *)(output));
            }
            return encoded_str;
        }

    private:
        static uint32_t indexOfCode(const char c) {
            const char *codes = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
            for (uint32_t i=0; i<64; i++)
                if (c == codes[i])
                    return i;
            return 0;
        }
    };
}

#endif //ALGORITHM_CLUB_BASE64_H
