#pragma once

#include <string>

namespace Base64
{

const std::string encode(const std::string text) noexcept;

const std::string decode(const std::string base64) noexcept;

} // namespace Base64