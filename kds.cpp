#include "./generator.hpp"
#include "./lexer.hpp"
#include "./messages.hpp"
#include "./module_reader.hpp"
#include "./parser.hpp"
#include "./preprocessor.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[])
{
    std::string outFilename, inputFilename;
    outFilename = "out";
    if (argc < 2)
    {
        if (!std::filesystem::exists("./kds.module"))
        {
            std::cerr << argv[0] << " \033[31m fatal error CLI001\033[0m: "
                                    "No argument given and no 'kds.module' was found\n";
            return 1;
        }
        std::stringstream strs;
        strs << std::fstream("kds.module", std::ios::in).rdbuf();
        std::cout << strs.str() << "\n";
        ModfileReader moduleRd = ModfileReader(strs.str(), &outFilename, &inputFilename);
        moduleRd.ReadMod();
        outFilename.append(".ll");
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
    std::cout << inputFilename << "\n"
              << outFilename << "\n";
    std::stringstream cnStream;
    std::fstream kds(inputFilename, std::ios::in);
    cnStream << kds.rdbuf();
    kds.close();
    Preprocessor pre(cnStream.str());
    cnStream = std::stringstream(pre.Preprocess());
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
