#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "./lexer.hpp"
#include "./parser.hpp"
#include "./generator.hpp"
#include "./messages.hpp"

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << argv[0] << "\033[31m fatal error CLI001\033[0m: " << "No argument given.\n";
		return 1;
	}
	else if(argv[1][0] == '-')
	{
		switch (argv[1][1])
		{
		case 'h':
			std::cout << KDS_HELP_MESSAGE << "\n";
			break;
		}
		return 0;
	}
	std::stringstream cnStream;
	std::fstream kds(argv[1], std::ios::in);
	cnStream << kds.rdbuf();
	kds.close();
	Lexer tokenizer(cnStream.str());
	std::vector<Token> toks = tokenizer.Tokenize();
	Parser errorcParser(toks);
	Node::Errorc errorcParseResult = errorcParser.ParseErrorc().value();
	Generator errorcGen(errorcParseResult);
	std::fstream assembly;
	assembly = std::fstream("out.asm", std::ios::out);
	assembly << errorcGen.GenerateErrorc();
	return 0;
}