#include "./parser.hpp"
#include "./lexer.hpp"
#include <sstream>

#pragma once


class Generator
{
public:
	inline Generator(Node::Stmt errorcn) : mErrorcn(std::move(errorcn))
	{

	}
	[[nodiscard]] std::string GenerateErrorc() const
	{
		std::cout << "started generation\n";

		std::stringstream output;
		if (mErrorcn.expr.exprValue.value.has_value())
		{
			output << "    ret i32 " << mErrorcn.expr.exprValue.value.value();
		}
		else
		{
			std::cerr << "kds \033[31mfatal error GEN001\033[0m: Failed to generate.\n";
			exit(4);
		}
		std::cout << "ended generation\n";

		return output.str();
	}

private:
	Node::Stmt mErrorcn;
};