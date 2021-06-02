#include "base64.hpp"
#include <gtest/gtest.h>

namespace
{

void assert_eq_wrapper(std::string source, std::string expected)
{
    ASSERT_EQ(Base64::decode(source), expected);
}

} // namespace

TEST(Base64, TrivialDecodingCase)
{
    assert_eq_wrapper("", "");
}

TEST(Base64, SimpleDecodingCase1)
{
    assert_eq_wrapper("MQ==", "1");
}

TEST(Base64, SimpleDecodingCase2)
{
    assert_eq_wrapper("MTI=", "12");
}

TEST(Base64, SimpleDecodingCase3)
{
    assert_eq_wrapper("MTIz", "123");
}

TEST(Base64, TestDecodingCase)
{
    assert_eq_wrapper("TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCAuLi4=",
                      "Man is distinguished, not only by his reason, but ...");
}