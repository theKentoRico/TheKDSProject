${CXX} = g++
kds: kds.cpp lexer.hpp parser.hpp generator.hpp token.hpp messages.hpp
	${CXX} kds.cpp -o kds