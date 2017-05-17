//
// Created by ZachZhang on 2017/5/17.
//

#include "base64.h"
#include "gtest/gtest.h"

TEST(Base64Test, simple_test) {
    const char *s = "Matthew 7:24-27 Therefore everyone who hears these words of mine\
 and puts them into practice is like a wise man who built his house on the\
 rock. 25 The rain came down, the streams rose, and the winds blew and beat\
 against that house; yet it did not fall, because it had its foundation on\
 the rock. 26 But everyone who hears these words of mine and does not put them\
 into practice is like a foolish man who built his house on sand. 27 The raincame\
 down, the streams rose, and the winds blew and beat against that house, and it fell\
 with a great crash.";
//    const char *s = "hello, world";

    std::cout << "INPUT: " << std::endl;
    std::cout << s << std::endl;

    std::string encodes_str = alg_club::CBase64::encodeBase64((uint8_t *)(s), strlen(s));
    std::cout << "ENCODED: " << std::endl;
    std::cout << encodes_str << std::endl;

    std::string decoded_str = alg_club::CBase64::decodeBase64(encodes_str);
    std::cout << alg_club::CBase64::decodeBase64(encodes_str) << std::endl;
    ASSERT_STRCASEEQ(s, decoded_str.c_str());
}
