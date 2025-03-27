#include "component.hpp"
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#ifndef _KDS_PREPROCESSOR_HPP_
#define _KDS_PREPROCESSOR_HPP_

class Preprocessor : public KdsComponent<char, std::string>
{
public:
    Preprocessor(std::string src) : KdsComponent(src)
    {
    }
    std::string Preprocess()
    {
        std::string rtstr = mSrc;                            // a copy of the source string
        std::string buf;                                     // a temporary buffer
        std::unordered_map<std::string, std::string> macDec; // the macros declared
        std::vector<std::string> included;                   // the included files
        while (Peek(0).has_value())
        {
            if (Peek(0).value() == '@')
            {
                buf.clear();
                Consume();
                while (std::isalpha(Peek(0).value()))
                    buf.push_back(Consume());
                if (buf == "define")
                {
                    std::string buf2;
                    buf.clear();
                    while (Peek(0).value() == ' ')
                        Consume();

                    while (std::isalpha(Peek(0).value()))
                        buf.push_back(Consume());

                    macDec[buf] = "";

                    while (Peek(0).value() == ' ')
                        Consume();

                    while (Peek(0).value() != '\\' && Peek(1).value() != '@')
                        buf2.push_back(Consume());

                    Consume();
                    Consume();
                    macDec[buf] = buf2;
                    buf.clear();
                    continue;
                }
                /*else if (buf == "pack")
                {
                    std::cout << "found @pack\n";
                    std::string buf2;
                    while (Peek(0).value() == ' ')
                        buf2.push_back(Consume());
                    while (Peek(0).value() != '\\' && Peek(1).value() != '@')
                    {
                        buf.push_back(Consume());
                        buf2.push_back(Peek(-1).value());
                    }
                    buf2.push_back(Consume());
                    buf2.push_back(Consume());
                    std::cout << buf << "\n";
                    included.push_back(buf);
                    buf.clear();
                    for (std::string header : included)
                    {
                        std::fstream filestr(header, std::ios::in);
                        std::stringstream tempstrm;
                        tempstrm << filestr.rdbuf() << "\n";
                        rtstr.replace(mIndex - buf2.size(), mIndex, tempstrm.str());
                    }
                }*/
                else if (buf != "")
                {
                    std::cerr << "kds \033[31mfatal error\033[0m: Unrecognized preprocessor directive '"
                              << buf << "'";
                    exit(-1);
                }
                continue;
            }
            else if (std::isalpha(Peek(0).value()))
            {
                buf.push_back(Consume());
                while (std::isalpha(Peek(0).value()))
                {
                    buf.push_back(Consume());
                }
                continue;
            }
            else if (macDec.find(buf) != macDec.end())
            {
                std::cout << "found defined macro\n";
                rtstr = rtstr.replace(mIndex - buf.size(), buf.size(), macDec[buf]);
                buf.clear();
                std::cout << rtstr << "\n";
                continue;
            }
            else
            {
                buf.clear();
                Consume();
                continue;
            }
            // if (std::isdigit(Peek(0).value()))
            //     Consume();
            // if (Peek(0).value() == '\r')
            //     Consume();
            // if (Peek(0).value() == '\n')
            //     Consume();
            // if (Peek(0).value() == ' ')
            //     Consume();
        }
        return rtstr;
    }
    ~Preprocessor()
    {
    }

private:
protected:
};

#endif