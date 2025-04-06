#include "token.hpp"

#pragma once

#ifndef _KDS_NODES_HPP_
#define _KDS_NODES_HPP_

namespace Node
{
    enum StmtType
    {
        _errorc,
        _value,
        _valref,
        _func
    };

    struct Expr
    {
        Token exprValue;
        Expr(Token cExprValue) : exprValue(std::move(cExprValue)) {}
        Expr() {}
        operator Token()
        {
            return this->exprValue;
        }
    };

    struct Stmt
    {
        std::vector<Expr> expr;
        StmtType type;
        std::optional<std::vector<Token>> params; // only required if the statement is a function
        Stmt(std::vector<Expr> cExpr, StmtType cType)
            : expr(std::move(cExpr)), type(std::move(cType))
        {
        }
        Stmt() {}
    };

} // namespace Node

#endif