#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include "./token.hpp"
#include <stdio.h>

#pragma once
class Lexer
{
public:
	inline Lexer(std::string src) : mSrc(std::move(src))
	{
		
	}
	std::vector<Token> Tokenize()
	{
		std::string buf = "";
		std::vector<Token> toks;
		Token pushTok;
		while (Peek().has_value())
		{
			if (std::isalpha(Peek().value()))
			{
				while (Peek().has_value() && std::isalpha(Peek(0).value()))
				{
					buf.push_back(Consume());
				}
			}
			if (buf == "errorc")
			{
				toks.push_back(Token{ .type = TokenType::errorc });
				buf.clear();
				continue;
			}
			if (Peek().value() == ' ')
			{
				Consume();
				continue;
			}
			if (std::isdigit(Peek().value()))
			{
				buf.push_back(Consume());
				while (Peek(0).has_value() && std::isdigit(Peek(0).value()))
				{
					buf.push_back(Consume());
				}
				toks.push_back(Token{ .type = TokenType::integer, .value = std::optional<std::string>(buf) });
				buf.clear();
				continue;
			}
			if (Peek(0).value() == ';')
			{
				Consume();
				toks.push_back(Token{ .type = TokenType::semic });
				continue;
			}
		}
		mIndex = 0;
		return toks;
	}
private:
	std::string mSrc;
	int mIndex = 0;
	std::optional<char> Peek(int ahead = 1)
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
	char Consume()
	{
		return mSrc.at(mIndex++);
	}
};