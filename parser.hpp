#include "./token.hpp"
#include <iostream>
#include <string>
#include <vector>

#pragma once
namespace Node
{
enum StmtType
{
    _errorc,
    _value
};

struct Expr
{
    Token exprValue;
    Expr(Token cExprValue) : exprValue(std::move(cExprValue)) {}
    Expr() {}
};

struct Stmt
{
    Expr expr;
    StmtType type;
    Stmt(Expr cExpr, StmtType cType)
        : expr(std::move(cExpr)), type(std::move(cType))
    {
    }
    Stmt() {}
};

} // namespace Node

class Parser
{
  public:
    inline explicit Parser(std::vector<Token> src) : mSrc(std::move(src)) {}
    std::optional<Node::Expr> ParseExprInt()
    {
        if (Peek(1).has_value() && Peek(1).value().type == TokenType::integer)
        {
            return Node::Expr(Consume());
        }
        return {};
    }
    std::optional<Node::Stmt> ParseErrorc()
    {
        std::cout << mSrc.size() << "\n";
        std::cout << "began parse\n";
        for (int i = 0; i < mSrc.size(); i++)
        {
            std::cout << mSrc.at(i).type << "\n";
        }
        Node::Stmt errorcn = Node::Stmt();
        errorcn.type = Node::StmtType::_errorc;
        while (Peek(0).has_value())
        {
            if (Peek(0).value().type == TokenType::errorc)
            {
                std::cout << "found errrorc\n";
                if (auto exprn = ParseExprInt())
                {
                    if (exprn.has_value())
                    {
                        std::cout << "node has value\n";
                        if (Peek(1).value().type == TokenType::semic)
                        {
                            std::cout << "found semicolon\n";
                            errorcn.expr = Node::Expr(Consume());
                            Consume();
                        }
                        else
                        {
                            std::cerr << "kds \033[31m fatal error "
                                         "LNG001\033[0m: Pre-defined "
                                         "keyword `errorc` expects integer "
                                         "right after it.\n";
                            exit(255);
                        }
                    }
                    else
                    {
                        std::cerr << "kds \033[31m fatal error PRS001\033[0m: "
                                     "Failed to "
                                     "parse expression.";
                        exit(3);
                    }
                }
            }
        }
        std::cout << "end parse\n";

        return errorcn;
    }
    Node::Stmt ParseValue() {}

  private:
    std::vector<Token> mSrc;
    unsigned long long mIndex = 0;
    std::optional<Token> Peek(int ahead = 1)
    {
        if ((mIndex + ahead) >= mSrc.size())
        {
            return {};
        }
        else
        {
            return mSrc.at(mIndex + ahead);
        }
    }
    Token Consume() { return mSrc.at(mIndex++); }
};