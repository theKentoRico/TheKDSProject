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
        _valref
    };

    struct Expr
    {
        Token exprValue;
        Expr(Token cExprValue) : exprValue(std::move(cExprValue)) {}
        Expr() {}
    };

    struct Stmt
    {
        std::vector<Expr> expr;
        StmtType type;
        Stmt(std::vector<Expr> cExpr, StmtType cType)
            : expr(std::move(cExpr)), type(std::move(cType))
        {
        }
        Stmt() {}
    };

} // namespace Node

#endif