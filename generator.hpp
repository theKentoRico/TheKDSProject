#include "./component.hpp"
#include "./lexer.hpp"
#include "./parser.hpp"
#include "./token.hpp"
#include <sstream>
#include <string>

#pragma once

#ifndef _KDS_GENERATOR_HPP_
#define _KDS_GENERATOR_HPP_

class Generator : public KdsComponent<Node::Stmt>
{
public:
    inline Generator(std::vector<Node::Stmt> src) : KdsComponent(src)
    {
    }
    [[nodiscard]] std::string Generate()
    {
        std::cout << "started generation\n";

        std::stringstream output;
        int tempNum = 2; // The number of the unnamed temporary variable
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
                    tempNum += 2;
                    break;
                }
                else
                {
                    output << "    ret i32 "
                           << Consume().expr.at(0).exprValue.value.value()
                           << "\n";
                    break;
                }

                break;
            case Node::StmtType::_value:
                std::cout << "Found _value\n";
                if (Peek(0).value().expr.at(2).exprValue.type == TokenType::_valref)
                {
                    output << "%" << tempNum
                           << " = load "
                           << kdsValtypes.at(Peek(0).value().expr.at(1).exprValue.value.value())
                           << ", ptr %"
                           << Peek(0).value().expr.at(0).exprValue.value.value()
                           << "\n";
                    mSrc.at(mIndex).expr.at(2).exprValue.value = "%" + std::to_string(tempNum);
                    tempNum += 2;
                }
                output << "    %" << Peek(0).value().expr.at(0).exprValue.value.value() << " = " << "alloca "
                       << kdsValtypes.at(Peek(0).value().expr.at(1).exprValue.value.value())
                       << "\n"
                          "    store "
                       << kdsValtypes.at(Peek(0).value().expr.at(1).exprValue.value.value())
                       << " "
                       << Peek(0).value().expr.at(2).exprValue.value.value()
                       << ", "
                       << kdsValtypes.at(Peek(0).value().expr.at(1).exprValue.value.value())
                       << "* %"
                       << Peek(0).value().expr.at(0).exprValue.value.value()
                       << '\n';
                Consume();
                break;
            }
        }
        std::cout << "ended generation\n";

        return output.str();
    }

private:
};

#endif