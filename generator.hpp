#include "./lexer.hpp"
#include "./parser.hpp"
#include "component.hpp"
#include <sstream>

#pragma once

#ifndef _KDS_GENERATOR_HPP_
#define _KDS_GENERATOR_HPP_

class Generator : public KdsComponent<Node::Stmt>
{
public:
    inline Generator(std::vector<Node::Stmt> src) : KdsComponent(src),
                                                    mSrc(std::move(src))
    {
    }
    [[nodiscard]] std::string Generate()
    {
        std::cout << "started generation\n";

        std::stringstream output;
        int tempNum = 1; // The number of the unnamed temporary
        while (Peek(0).has_value())
        {
            switch (Peek(0).value().type)
            {
            case Node::StmtType::_errorc:
                if (!Peek(0).value().expr.at(0).exprValue.value.has_value())
                {
                    std::cerr
                        << "kds \033[31mfatal error GEN001\033[0m: Failed to "
                           "generate.\n";
                    exit(4);
                }
                std::cout << "Found errorc.\n";
                if (Peek(0).value().expr.at(0).exprValue.type == TokenType::_valref)
                {
                    output << "    %"
                           << tempNum << " = load i32 , ptr %" << Consume().expr.at(0).exprValue.value.value()
                           << "\n    ret i32 %"
                           << tempNum << "\n";
                    tempNum++;
                    break;
                }
                else
                {
                    output << "    ret i32 "
                           << Consume().expr.at(0).exprValue.value.value();
                    break;
                }

                break;
            case Node::StmtType::_value:
                std::cout << "Found _value\n";
                output << "    %" << Peek(0).value().expr.at(0).exprValue.value.value() << " = " << "alloca ";
                std::cout << Peek(0).value().expr.size() << "\n";
                if (Peek(0).value().expr.at(1).exprValue.value.value() == "int")
                {
                    std::cout << "valtype int\n";

                    output << "i32, align 8\n"
                              "    store "
                           << "i32 "
                           << Peek(0).value().expr.at(2).exprValue.value.value()
                           << ", i32* "
                              "%"
                           << Peek(0).value().expr.at(0).exprValue.value.value() << "\n";
                    Consume();
                    continue;
                }
                if (Peek(0).value().expr.at(1).exprValue.value.value() == "long")
                {
                    std::cout << "valtype long\n";

                    output << "i64, align 8\n"
                              "    store "
                           << "i64 "
                           << Peek(0).value().expr.at(2).exprValue.value.value()
                           << ", i64* "
                              "%"
                           << Peek(0).value().expr.at(0).exprValue.value.value() << "\n";
                    Consume();
                    continue;
                }
                if (Peek(0).value().expr.at(1).exprValue.value.value() == "char")
                {
                    std::cout << "valtype long\n";

                    output << "i8, align 1\n"
                              "    store "
                           << "i8 "
                           << Peek(0).value().expr.at(2).exprValue.value.value()
                           << ", i8* "
                              "%"
                           << Peek(0).value().expr.at(0).exprValue.value.value() << "\n";
                    Consume();
                    continue;
                }
                if (Peek(0).value().expr.at(1).exprValue.value.value() == "bool")
                {
                    std::cout << "valtype long\n";

                    output << "i1, align 1\n"
                              "    store "
                           << "i1 "
                           << Peek(0).value().expr.at(2).exprValue.value.value()
                           << ", i1* "
                              "%"
                           << Peek(0).value().expr.at(0).exprValue.value.value() << "\n";
                    Consume();
                    continue;
                }
                break;
            }
        }
        std::cout << "ended generation\n";

        return output.str();
    }

private:
    std::vector<Node::Stmt> mSrc;
};

#endif