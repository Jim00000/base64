#include "base64.hpp"
#include <gtest/gtest.h>

namespace
{

void assert_eq_wrapper(std::string source, std::string expected)
{
    ASSERT_EQ(Base64::encode(source), expected);
}

} // namespace

TEST(Base64, TrivialEncodingCase)
{
    assert_eq_wrapper("", "");
}

TEST(Base64, SimpleEncodingCase1)
{
    assert_eq_wrapper("1", "MQ==");
}

TEST(Base64, SimpleEncodingCase2)
{
    assert_eq_wrapper("12", "MTI=");
}

TEST(Base64, SimpleEncodingCase3)
{
    assert_eq_wrapper("123", "MTIz");
}
TEST(Base64, SimpleEncodingCase4)
{
    assert_eq_wrapper("1234", "MTIzNA==");
}

TEST(Base64, SimpleEncodingCase5)
{
    assert_eq_wrapper("12345", "MTIzNDU=");
}

TEST(Base64, TestEncodingCase1)
{
    assert_eq_wrapper("Man is distinguished, not only by his reason, but ...",
                      "TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24sIGJ1dCAuLi4=");
}