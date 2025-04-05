#include "./token.hpp"
#include "component.hpp"
#include <algorithm>
#include <iostream>
#include <limits.h>
#include <optional>
#include <string>
#include <vector>

#ifndef _KDS_LEXER_HPP_
#define _KDS_LEXER_HPP_

class Lexer : public KdsComponent<char, std::string>
{
public:
    inline Lexer(std::string src) : KdsComponent(src)
    {
    }
    std::vector<Token> Tokenize()
    {
        int whitespaceCount = 0;
        std::cout << "reached tokenization\n";
        std::string buf = "";    // a temporary buffer
        std::vector<Token> toks; // the vector to be returned
        Token pushTok;
        std::vector<std::string> valuesDeclared;
        std::cout << mSrc << "\n";
        while (Peek(0).has_value())
        {
            if (std::isalpha(Peek(0).value()))
            {
                std::cout << Peek(0).value();
                buf.push_back(Consume());
                while (Peek(0).has_value() && std::isalpha(Peek(0).value()))
                {
                    std::cout << Peek(0).value() << "\n";
                    std::cout << buf;
                    buf.push_back(Consume());
                }
            }
            std::cout << buf;
            if (buf == "value")
            {
                toks.push_back(Token{.type = TokenType::_value});
                buf.clear();
                std::cout << "pushed value\n";
                while (Peek(0).has_value() && Peek(0).value() != '{')
                {
                    if (Peek(0).value() == ' ')
                        Consume();
                    else
                        buf.push_back(Consume());
                }
                std::cout << "found open curl.\n";
                Consume();
                valuesDeclared.push_back(buf);
                toks.push_back(Token{.type = TokenType::varname, .value = buf});
                std::cout << "found varname.\n";
                buf.clear();
                toks.push_back(Token{.type = TokenType::openCurl});
                while (Peek(0).has_value() && Peek(0).value() != '}')
                {
                    switch (Peek(0).value())
                    {
                    case ' ':
                        Consume();
                        break;
                    default:
                        buf.push_back(Consume());
                        break;
                    }
                }
                Consume();
                std::cout << "found variable type.\n";
                toks.push_back(Token{.type = TokenType::valtype, .value = buf});
                buf.clear();
                toks.push_back(Token{.type = TokenType::closeCurl});
                std::cout << "found close curl\n";
                continue;
            }
            else if (buf == "errorc")
            {
                whitespaceCount = 0;
                std::cout << Peek(0).value();
                std::cout << "found errorc\n";
                toks.push_back(Token{.type = TokenType::errorc});
                buf.clear();
                continue;
            }
            else if (buf == "func")
            {
                toks.push_back(Token{.type = TokenType::_func});
                while (Peek(0).has_value() && Peek(0).value() == ' ')
                    Consume();
                while (Peek(0).value() != '(')
                {
                    if (Peek(0).value() == ' ')
                    {
                        Consume();
                        continue;
                    }
                    buf.push_back(Consume());
                    continue;
                }
                toks.push_back(Token{.type = TokenType::varname, .value = buf});
                toks.push_back(Token{.type = TokenType::openParen});
                Consume();
                buf.clear();
                while (Peek(0).value() != ')')
                {
                    while (Peek(0).value() != ',')
                    {
                        if (Peek(0).value() == ' ')
                        {
                            Consume();
                            continue;
                        }
                        buf.push_back(Consume());
                        continue;
                    }
                    toks.push_back(Token{.type = TokenType::_param, .value = buf});
                    buf.clear();
                    continue;
                }
                continue;
            }
            else if (buf != "")
            {
                if (!std::count(valuesDeclared.begin(), valuesDeclared.end(), buf))
                {
                    std::cerr << "\nkds \033[31mfatal error LNG008\033[0m: "
                                 "Unrecognized identifier "
                              << buf;
                    exit(-1);
                }
                toks.push_back(Token{.type = TokenType::_valref, .value = buf});
                buf.clear();
                continue;
            }
            else if (Peek(0).value() == ' ')
            {
                whitespaceCount++;
                std::cout << Peek(0).value();
                std::cout << "found whitespace\n";
                if (whitespaceCount > 4)
                {
                    break;
                }
                Consume();
                continue;
            }
            else if (std::isdigit(Peek(0).value()))
            {
                whitespaceCount = 0;
                std::cout << Peek(0).value();
                std::cout << "found int\n";

                buf.push_back(Consume());
                while (Peek(0).has_value() && std::isdigit(Peek(0).value()))
                {
                    whitespaceCount = 0;
                    std::cout << Peek(0).value();
                    buf.push_back(Consume());
                }
                std::cout << buf << "\n";
                toks.push_back(Token{.type = TokenType::integer,
                                     .value = std::optional<std::string>(buf)});
                buf.clear();
                continue;
            }
            else if (Peek(0).value() == ';')
            {
                whitespaceCount = 0;
                std::cout << Peek(0).value();
                std::cout << "semic\n";
                toks.push_back(Token{.type = TokenType::semic});
                Consume();
                continue;
            }
            else if (Peek(0).value() == '=')
            {
                toks.push_back(Token{.type = TokenType::assign});
                Consume();
                continue;
            }
            else if (!Peek(1).has_value())
            {
                whitespaceCount = 0;
                break;
            }
            else if (Peek(0).value() == '@')
            {
                while (Peek(0).value() != '\\' && Peek(1).value() != '@')
                    Consume();
                Consume();
                Consume();
                continue;
            }
            else if (Peek(0).value() == '+' || Peek(0).value() == '-' || Peek(0).value() == '*' || Peek(0).value() == '/')
            {
                buf.push_back(Consume());
                toks.push_back(Token{.type = TokenType::_arith,
                                     .value = buf});
                buf.clear();
                continue;
            }
            else if (Peek(0).value() == '\r')
                Consume();
            else if (Peek(0).value() == '\n')
                Consume();
        }
        std::cout << "ended tokenization\n";

        mIndex = 0;
        return toks;
    }

private:
    std::string mSrc;
};

#endif