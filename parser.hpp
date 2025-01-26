#include "./token.hpp"
#include <vector>
#include <string>
#include <iostream>

#pragma once
namespace Node
{
	struct Expr
	{
		Token exprValue;
		Expr(Token cExprValue) : exprValue(std::move(cExprValue))
		{

		}
		Expr()
		{

		}
	};

	struct Errorc
	{
		Expr expr;
		Errorc(Expr cExpr) : expr(std::move(cExpr))
		{

		}
		Errorc()
		{

		}
	};
}

class Parser
{
public:
	inline explicit Parser(std::vector<Token> src) : mSrc(std::move(src))
	{

	}
	std::optional<Node::Expr> ParseExprInt()
	{
		if (Peek(1).has_value() && Peek(1).value().type == TokenType::integer)
		{
			return Node::Expr(Consume());
		}
		return {};
	}
	std::optional<Node::Errorc> ParseErrorc()
	{
		Node::Errorc errorcn = Node::Errorc();
		while (Peek(0).has_value())
		{
			if (Peek(0).value().type == TokenType::errorc)
			{
				if (auto exprn = ParseExprInt())
				{
					if (exprn.has_value())
					{
						if (Peek(1).value().type == TokenType::semic)
						{
							errorcn.expr = Node::Expr(Consume());
							Consume();
						}
						else
						{
							std::cerr << "kds \033[31m fatal error LNG001\033[0m: Pre-defined keyword `errorc` expects integer right after it.\n";
							exit(255);
						}
					}
					else
					{
						std::cerr << "kds \033[31m fatal error PRS001\033[0m: Failed to parse expression.";
						exit(3);
					}
				}
			}
		}
		return errorcn;
	}
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
	Token Consume()
	{
		return mSrc.at(mIndex++);
	}
};