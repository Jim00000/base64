/* MIT License

Copyright (c) 2021 Jim00000

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

*/

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