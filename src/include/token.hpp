#include <optional>
#include <string>
#include <unordered_map>

#pragma once

#ifndef _KDS_TOKEN_HPP_
#define _KDS_TOKEN_HPP_

const std::unordered_map<std::string, std::string> kdsValtypes = std::unordered_map<std::string, std::string>({{"int", "i32"}, {"long", "i64"}, {"char", "i8"}, {"bool", "i1"}});

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
    _valref,
    _arith,
    _func,
    openParen,
    closeParen,
    _param
};

struct Token
{
    TokenType type;
    std::optional<std::string> value;
};

#endif