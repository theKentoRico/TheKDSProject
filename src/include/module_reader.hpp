#include "component.hpp"
#include <string>

#ifndef _KDS_MODULE_READER_HPP_
#define _KDS_MODULE_READER_HPP

class ModfileReader : public KdsComponent<char, std::string>
{
public:
    ModfileReader(std::string src, std::string *moduleName, std::string *sourceFile) : KdsComponent(src),
                                                                                       mModuleName(*moduleName),
                                                                                       mSourceFile(*sourceFile)
    {
    }
    void ReadMod()
    {
        std::string buf;
        std::cout << mSrc << "\n";
        while (Peek(0).has_value())
        {
            if (std::isalpha(Peek(0).value()) && Peek(0).value() != ' ')
            {
                std::cout << Peek(0).value();
                buf.push_back(Consume());
                while (Peek(0).has_value() && std::isalpha(Peek(0).value()) && Peek(0).value() != ' ')
                {
                    std::cout << Peek(0).value() << "\n";
                    std::cout << buf;
                    buf.push_back(Consume());
                }
            }
            if (buf == "module")
            {
                buf.clear();
                while (Peek(0).has_value() && Peek(0).value() == ' ')
                {
                    Consume();
                }
                while (Peek(0).has_value() && std::isalpha(Peek(0).value()))
                {
                    buf.push_back(Consume());
                }
                mModuleName = buf;
                buf.clear();
                continue;
            }
            if (buf == "sources")
            {
                buf.clear();
                Consume();
                while (Peek(0).has_value() && Peek(0).value() == ' ')
                {
                    Consume();
                }
                while (Peek(0).has_value() && (std::isalpha(Peek(0).value()) || Peek(0).value() == '.'))
                {
                    buf.push_back(Consume());
                }
                mSourceFile = buf;
                buf.clear();
                continue;
            }
            if (Peek(0).value() == '\n')
                Consume();
            if (Peek(0).value() == '\0')
                break;
            if (Peek(0).value() == '\r')
                Consume();
        }
    }

private:
    std::string &mModuleName;
    std::string &mSourceFile;
};

#endif