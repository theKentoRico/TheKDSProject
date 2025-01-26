#include "./parser.hpp"
#include "./lexer.hpp"
#include <sstream>

#pragma once


class Generator
{
public:
	inline Generator(Node::Errorc errorcn) : mErrorcn(std::move(errorcn))
	{

	}
	[[nodiscard]] std::string GenerateErrorc() const
	{
		std::stringstream output;
		output << "global _start\n_start:\n";
		if (mErrorcn.expr.exprValue.value.has_value())
		{
			output << "mov rax, 60\nmov rdi, " << mErrorcn.expr.exprValue.value.value() << "\nsyscall";
		}
		else
		{
			std::cerr << "kds \033[31mfatal error GEN001\033[0m: Failed to generate.\n";
			exit(4);
		}
		return output.str();
	}
private:
	Node::Errorc mErrorcn;
};