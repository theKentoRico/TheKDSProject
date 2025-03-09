#include "./generator.hpp"
#include "./lexer.hpp"
#include "./messages.hpp"
#include "./parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    std::string outFilename, inputFilename;
    outFilename = "out.ll";
    if (argc < 2)
    {
        std::cout << argv[0] << "\033[31m fatal error CLI001\033[0m: "
                                "No argument given.\n";
        return 1;
    }
    else
    {
        inputFilename = argv[1];
        if (argv[1][0] == '-')
        {
            switch (argv[1][1])
            {
            case 'h':
                std::cout << KDS_HELP_MESSAGE << "\n";
                break;
            case 'o':
                inputFilename = argv[3];
                if (argc <= 2)
                {
                    std::cerr << argv[0] << " \033[31mfatal error CLI002\033[0m: "
                                            "No argument given to '-o' flag.\n";
                    return 1;
                }
                outFilename = argv[2];
                break;
            default:
                std::cerr << argv[0] << " \033[31mfatal error CLI003\033[0m: "
                                        "Unknown option "
                          << argv[1]
                          << ".\n";
                return 1;
            }
        }
    }
    std::stringstream cnStream;
    std::fstream kds(inputFilename, std::ios::in);
    cnStream << kds.rdbuf();
    kds.close();
    Lexer tokenizer(cnStream.str());
    std::vector<Token> toks = tokenizer.Tokenize();
    std::cout << "ended tokenization\n";
    Parser parser(toks);
    std::vector<Node::Stmt> parseResult = parser.Parse();
    Generator errorcGen(parseResult);
    std::fstream assembly;
    assembly = std::fstream(outFilename, std::ios::out);
    assembly << "define dso_local i32 @main()\n{";
    assembly << errorcGen.Generate();
    assembly << "\n}";
    return 0;
}
