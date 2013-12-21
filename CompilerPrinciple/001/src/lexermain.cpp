// STL
#include <iostream>
#include <fstream>
#include <memory>
#include <string>
#include <algorithm>

// PL0Compiler
#include <token.hpp>
#include <lexer/all.hpp>

using namespace PL0;

void test0(std::shared_ptr<std::string> codestr) 
{
	std::cout << "Lexer get: " << std::endl;
	Lexer lexer(codestr);
	char next = lexer.getNextChar();
	while(next != std::char_traits<char>::eof()) {
		std::cout << next;
		next = lexer.getNextChar();
	}//while
}//test0()

void test1(std::shared_ptr<std::string> codestr)
{
	Lexer lexer(codestr);
	
	while(true) {
		lexer.getNextToken();

		std::cout << "Tok: " << lexer.token()
			<< ", str: '" << lexer.word()
			<< "'" << std::endl;
	}//while
}//test1()

int main(int argc, char * argv[])
{
	std::ifstream ifs("../test/test01.pl0");
	auto codestr = std::make_shared<std::string>(
			(std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));

	if(!ifs.is_open())
		std::cout << "File not found!" << std::endl;

	std::cout << "Code: " << std::endl;
	std::cout << *codestr << std::endl;

	std::cout << std::endl;
	std::cout << "--------------------------------------------------" << std::endl;

	test0(codestr);

	std::cout << "--------------------------------------------------" << std::endl;

	test1(codestr);
	
	return 0;
}//main

