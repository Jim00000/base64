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

inline auto lookupTable(const uint8_t code) noexcept -> std::string
{
    return std::string(1, Base64::base64Table.at(code));
}

auto toBase64(const std::string &string) noexcept -> std::string
{
    std::string base64;
    uint8_t status = 0;
    /*
        A table shows how to encode a text into base64:

        ┌─────────────┬─────────────┬─────────────┬─────────────┐
        │    ASCII    │    M (77)   │    a (97)   │    n (110)  │
        ├─────────────┼─────────────┼─────────────┼─────────────┤
        │ bit pattern │ 010011   01 │ 0110   0001 │ 01   101110 │
        ├─────────────┼────────┬────┴──────┬──────┴────┬────────┤
        │    Index    │ 010011 │ 01   0110 │ 0001   01 │ 101110 │
        ├─────────────┼────────┼───────────┼───────────┼────────┤
        │    base64   │ T (19) │   W (22)  │   F (5)   │ u (46) │
        └─────────────┴────────┴───────────┴───────────┴────────┘
    */

    for (size_t i = 0; i < string.size(); i++)
    {
        status = i % 3;
        uint8_t code = 0;
        if (status == 0)
        {
            /*
                Status 0 handles (4n+1)th index.
                e.g. we take 6 leading bits 010011 from 'M'
                Index = ('M' >> 2)
            */
            code = string.at(i) >> 2;
            base64 += lookupTable(code);
        }
        else if (status == 1)
        {
            /*
                Status 1 handles (4n+2)th index.
                e.g. we take 2 last bits 01 from 'M' and 4 leading bits 0110 from 'a'
                Index = (('M' & 0b00000011) << 4) | ('a' >> 4)
            */
            code = string.at(i) >> 4;
            code |= (string.at(i - 1) & 0b00000011) << 4;
            base64 += lookupTable(code);
        }
        else if (status == 2)
        {
            /*
                Status 2 handles (4n+3)th and (4n+4)th index.
                e.g. we take 4 last bits 0001 from 'a' and 2 leading bits 01 from 'n' for (4n+3)th index
                     and take 6 last bits 101110 from 'n'
                (4n+3)-Index = (('a' & 0b00001111) << 2) | ('n' >> 6)
                (4n+4)-Index = ('n' & 0b00111111)
            */
            code = string.at(i) >> 6;
            code |= (string.at(i - 1) & 0b00001111) << 2;
            base64 += lookupTable(code);

            code = string.at(i) & 0b00111111;
            base64 += lookupTable(code);
        }
    }

    // Handle postfix
    if (status == 0)
    {
        /*
            ┌─────────────┬─────────────┬─────────────┬─────────────┐
            │    ASCII    │    M (77)   │     N/A     │     N/A     │
            ├─────────────┼─────────────┼─────────────┼─────────────┤
            │ bit pattern │ 010011   01 │ 0000   0000 │ 00   000000 │
            ├─────────────┼────────┬────┴──────┬──────┴────┬────────┤
            │    Index    │ 010011 │ 01   0000 │ 0000   00 │ 000000 │
            ├─────────────┼────────┼───────────┼───────────┼────────┤
            │    base64   │ T (19) │   Q (16)  │   = (0)   │ = (0)  │
            └─────────────┴────────┴───────────┴───────────┴────────┘
        */
        uint8_t code = (string.at(string.size() - 1) & 0b00000011) << 4;
        base64 += lookupTable(code) + "==";
    }
    else if (status == 1)
    {
        /*
            ┌─────────────┬─────────────┬─────────────┬─────────────┐
            │    ASCII    │    M (77)   │    a (97)   │     N/A     │
            ├─────────────┼─────────────┼─────────────┼─────────────┤
            │ bit pattern │ 010011   01 │ 0110   0001 │ 00   000000 │
            ├─────────────┼────────┬────┴──────┬──────┴────┬────────┤
            │    Index    │ 010011 │ 01   0110 │ 0001   00 │ 000000 │
            ├─────────────┼────────┼───────────┼───────────┼────────┤
            │    base64   │ T (19) │   W (22)  │   E (4)   │ = (0)  │
            └─────────────┴────────┴───────────┴───────────┴────────┘
        */
        uint8_t code = (string.at(string.size() - 1) & 0b00001111) << 2;
        base64 += lookupTable(code) + "=";
    }

    return base64;
}

} // namespace

auto Base64::encode(const std::string &text) noexcept -> std::string
{
    if (text.empty())
    {
        return "";
    }

    const std::string base64 = toBase64(text);
    return base64;
}
