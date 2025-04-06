#include "./token.hpp"
#include "component.hpp"
#include "methods.hpp"
#include "nodes.hpp"
#include <iostream>
#include <string>
#include <vector>

#ifndef _KDS_PARSER_HPP_
#define _KDS_PARSER_HPP_

class Parser : public KdsComponent<Token, std::vector<Token>>
{
public:
    inline Parser(std::vector<Token> src) : KdsComponent(src)
    {
    }
    std::optional<Node::Expr> ParseExprInt()
    {
        if (Peek(1).has_value() && (Peek(1).value().type == TokenType::integer || Peek(1).value().type == TokenType::_valref))
        {
            return Node::Expr(Consume());
        }
        return {};
    }
    Node::Stmt ParseErrorc()
    {
        std::cout << mSrc.size() << "\n";
        std::cout << "began parse\n";
        // for (int i = 0; i < mSrc.size(); i++)
        // {
        //     std::cout << mSrc.at(i).type << "\n";
        // }
        Node::Stmt errorcn = Node::Stmt();
        errorcn.type = Node::StmtType::_errorc;

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
                        errorcn.expr.push_back(Node::Expr(Consume()));
                        Consume();
                    }
                    else
                    {
                        std::cerr << "kds \033[31m fatal error "
                                     "LNG006\033[0m: Expected semicolon"
                                     "\n";
                        exit(-1);
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
            else
            {
                std::cerr << "kds \033[31m fatal error "
                             "LNG001\033[0m: Pre-defined "
                             "keyword `errorc` expects integer "
                             "right after it.\n";
                exit(-1);
            }
        }
        // code is unrefactorable. don't 'fix' it if it works.
        double hoursWasted = 0.75; // if you wasted some time here, increment this counter
        return errorcn;
    }
    Node::Stmt ParseValue()
    {
        Node::Stmt valuen = Node::Stmt();
        valuen.type = Node::StmtType::_value;
        if (Peek(0).value().type == TokenType::_value)
        {
            Consume();
            if (Peek(0).value().type != TokenType::varname)
            {
                std::cerr << "kds \033[31m fatal error LNG002\033[0m: "
                             "A variable name must be given to a variable."
                             "\n";
                exit(-1);
            }
            std::cout << "found name\n";
            valuen.expr.push_back(Node::Expr(Consume()));
            if (Peek(0).value().type != TokenType::openCurl)
            {
                std::cerr << "kds \033[31m fatal error LNG003\033[0m: "
                             "A variable type must be wrapped by brackets {}."
                             "\n";
                exit(-1);
            }
            Consume();
            if (Peek(0).value().type != TokenType::valtype)
            {
                std::cerr << "kds \033[31m fatal error LNG007\033[0m: "
                             "A variable type must be given to all variables."
                             "\n";
                exit(-1);
            }
            std::cout << "found type\n";
            valuen.expr.push_back(Node::Expr(Consume()));
            if (Peek(0).value().type != TokenType::closeCurl)
            {
                std::cerr << "kds \033[31m fatal error LNG004\033[0m: "
                             "Each bracket must have a corrresponding closing "
                             "bracket."
                             "\n";
                exit(-1);
            }
            Consume();
            if (Peek(0).value().type != TokenType::assign)
            {
                std::cerr << "kds \033[31m fatal error LNG005\033[0m: "
                             "A variable must be assigned with a '=' operator"
                             "\n";
                exit(-1);
            }
            Consume();
            std::cout << "found =\n";
            if (Peek(0).value().type == _valref)
                mSrc.at(mIndex).value = "%" + mSrc.at(mIndex).value.value();
            valuen.expr.push_back(Node::Expr(Consume()));
            if (Peek(0).value().type != TokenType::semic)
            {
                std::cerr << "kds \033[31m fatal error LNG006\033[0m: "
                             "Expected semicolon."
                             "\n";
                exit(-1);
            }
            Consume();
        }
        std::cout << valuen.expr.size() << "\n";
        return valuen;
    }
    Node::Stmt ParseFunc()
    {
        Node::Stmt funcn = Node::Stmt();
        funcn.type = Node::StmtType::_func;
        if (Peek(0).value().type == TokenType::_func)
        {
            Consume();
            if (Peek(0).value().type != TokenType::varname)
            {
                std::cerr << "kds \033[31mfatal error LNG009\033[0m: "
                             "A function name must be given to"
                             " a function.\n";
                exit(-1);
            }
            funcn.expr.push_back(Consume());
            if (Peek(0).value().type != TokenType::valtype)
            {
                std::cerr << "kds \033[31mfatal error LNG011\033[0m: "
                             "A function type must be given to"
                             " a function.\n";
                exit(-1);
            }
            funcn.expr.push_back(Consume());
            if (Peek(0).value().type != TokenType::openParen)
            {
                std::cerr << "kds \033[31mfatal error LNG010\033[0m: "
                             "Expected '('.\n";
                exit(-1);
            }
            Consume();
            while (Peek(0).has_value() && Peek(0).value().type == TokenType::_param)
            {
                funcn.expr.push_back(Consume());
            }
            Consume();

        }
    }
    std::vector<Node::Stmt> Parse()
    {
        std::cout << "begin parse\n";
        std::vector<Node::Stmt> nodes;
        while (Peek(0).has_value())
        {
            switch (Peek(0).value().type)
            {
            case TokenType::_value:
                std::cout << "found _value\n";
                nodes.push_back(ParseValue());
                break;
            case TokenType::errorc:
                std::cout << "found errorc\n";
                nodes.push_back(ParseErrorc());
                break;
            default:
                std::cerr << "kds \033[31m fatal error PRS002\033[0m: Parsing not implemented for token."
                          << Peek(0).value().type << "\n";
                exit(3);
            }
        }
        return nodes;
    }

private:
};

#endif