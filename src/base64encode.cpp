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
#include "base64table.hpp"
#include <string>

namespace
{

std::string toBase64(const std::string &string) noexcept
{
    std::string base64 = "";
    uint8_t status;

    for (size_t i = 0; i < string.size(); i++)
    {
        status = i % 3;
        uint8_t code;
        if (status == 0)
        {
            code = string.at(i) >> 2;
            base64 += Base64::base64Table.at(code);
        }
        else if (status == 1)
        {
            code = string.at(i) >> 4;
            code |= (string.at(i - 1) & 0b00000011) << 4;
            base64 += Base64::base64Table.at(code);
        }
        else if (status == 2)
        {
            code = string.at(i) >> 6;
            code |= (string.at(i - 1) & 0b00001111) << 2;
            base64 += Base64::base64Table.at(code);

            code = string.at(i) & 0b00111111;
            base64 += Base64::base64Table.at(code);
        }
    }

    // Handle postfix
    if (status == 0)
    {
        uint8_t code = (string.at(string.size() - 1) & 0b00000011) << 4;
        base64 += Base64::base64Table.at(code) + "==";
    }
    else if (status == 1)
    {
        uint8_t code = (string.at(string.size() - 1) & 0b00001111) << 2;
        base64 += Base64::base64Table.at(code) + "=";
    }

    return base64;
}

} // namespace

auto Base64::encode(const std::string& text) noexcept -> std::string
{
    if (text.size() == 0)
        return "";

    const std::string base64 = toBase64(text);
    return base64;
}
