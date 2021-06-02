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
#include <unordered_map>

namespace
{

auto base64Mapper = [&] {
    std::unordered_map<std::string, size_t> mapper;
    for (size_t i = 0; i < Base64::base64Table.size(); i++)
        mapper.insert(std::make_pair(Base64::base64Table[i], i));
    return mapper;
}();

inline const uint8_t toBit(const char c) noexcept
{
    return base64Mapper[std::string(1, c)];
}

std::string toASCII(const std::string &base64) noexcept
{
    std::string ascii = "";
    uint8_t code = 0;
    for (size_t i = 0; i < base64.size(); i++)
    {
        const uint8_t status = i % 4;
        if (status == 0)
        {
            code = (toBit(base64.at(i)) << 2);
            code |= (toBit(base64.at(i + 1)) >> 4);
            ascii += code;
        }
        else if (status == 1)
        {
            code = ((toBit(base64.at(i)) & 0b001111) << 4);
            code |= (toBit(base64.at(i + 1)) >> 2);
            ascii += code;
        }
        else if (status == 2)
        {
            code = ((toBit(base64.at(i)) & 0b000011) << 6);
        }
        else
        {
            code |= (toBit(base64.at(i)));
            ascii += code;
        }
    }

    /* Handle base64 postfix */
    const std::string postfix = base64.substr(base64.size() - 2, 2);
    size_t tailCut = 0;
    tailCut += (postfix.at(0) == '=');
    tailCut += (postfix.at(1) == '=');

    return ascii.substr(0, ascii.size() - tailCut);
}

} // namespace

const std::string Base64::decode(const std::string base64) noexcept
{
    if (base64.size() == 0)
        return "";

    const std::string ascii = toASCII(base64);
    return ascii;
}