#include <optional>
#include <string>

#pragma once

enum TokenType
{
    errorc,
    semic,
    integer
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;
};