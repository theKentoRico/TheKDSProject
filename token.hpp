#include <optional>
#include <string>

#pragma once

#ifndef _KDS_TOKEN_HPP_
#define _KDS_TOKEN_HPP_

enum TokenType
{
    errorc,
    semic,
    integer,
    _value,
    assign,
    openCurl,
    closeCurl,
    valtype,
    varname,
    _valref
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;
};

#endif