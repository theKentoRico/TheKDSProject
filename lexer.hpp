#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include "./token.hpp"
#include <limits.h>

#pragma once
class Lexer
{
public:
	inline Lexer(std::string src) : mSrc(std::move(src))
	{
		
	}
	std::vector<Token> Tokenize()
	{
		int whitespaceCount = 0;
		std::cout << "reached tokenization\n";
		std::string buf = "";
		std::vector<Token> toks;
		Token pushTok;
		while (Peek(0).has_value())
		{
			std::cout << Peek(0).value();
			if (std::isalpha(Peek(0).value()))
			{
				std::cout << Peek(0).value();
				buf.push_back(Consume());
				while (Peek(0).has_value() && std::isalpha(Peek(0).value()))
				{
					std::cout << Peek(0).value();
					buf.push_back(Consume());
					if (buf == "errorc")
					{
						std::cout << "found errorc\n";
						toks.push_back(Token{ .type = TokenType::errorc });
						buf.clear();
						continue;
					}
				}
				if (buf == "errorc")
				{
					whitespaceCount = 0;
					std::cout << Peek(0).value();
					std::cout << "found errorc\n";
					toks.push_back(Token{ .type = TokenType::errorc });
					buf.clear();
					continue;
				}
			}
			if (buf == "errorc")
			{
				whitespaceCount = 0;
				std::cout << Peek(0).value();
				std::cout << "found errorc\n";
				toks.push_back(Token{ .type = TokenType::errorc });
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
				toks.push_back(Token{ .type = TokenType::integer, .value = std::optional<std::string>(buf) });
				buf.clear();
				continue;
			}
			else if (Peek(0).value() == ';')
			{
				whitespaceCount = 0;
				std::cout << Peek(0).value();
				std::cout << "semic\n";
				toks.push_back(Token{ .type = TokenType::semic });
				Consume();
				continue;
			}
			else if (!Peek().has_value())
			{
				whitespaceCount = 0;
				break;
			}
		}
		std::cout << "ended tokenization\n";

		mIndex = 0;
		return toks;
	}
private:
	std::string mSrc;
	int mIndex = 0;
	std::optional<char> Peek(int ahead = 1)
	{
		// std::cout << mIndex << "\n";
		std::cout << mIndex + ahead << " " << (int) mSrc.at(mIndex + ahead) << "\n";
		if ((mIndex + ahead) >= mSrc.length() || mSrc.at(mIndex + ahead) == '\r')
		{
			return std::optional<char>();
		}
		else
		{
			// std::cout << (int) mSrc.at(mIndex + ahead);
			return mSrc.at(mIndex + ahead);
		}
	}
	char Consume()
	{
		return mSrc.at(mIndex++);
	}
};