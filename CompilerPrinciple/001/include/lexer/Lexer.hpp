#pragma once

// STL
#include <fstream>
#include <memory>
// PL0Compiler
#include <token.hpp>
#include <lexer/WordMap.hpp>

namespace PL0 {

class Lexer
{
public://functions
	Lexer(const std::shared_ptr<std::string> pfilestr);
	~Lexer();

	Lexer(const Lexer & rhs) = delete;
	Lexer(Lexer && rhs) = delete;
	Lexer & operator=(const Lexer & rhs) = delete;
	Lexer & operator=(Lexer && rhs) = delete;

	bool getNextToken();

	/**
	 * @brief get current token
	 */
	inline Token token() const { return m_token; }

	/**
	 * @brief get current word corresponding to the token
	 */
	inline std::string word() const { return m_word; }

#ifndef NDEBUG
public://functions
#else
private://functions
#endif//!NDEBUG
	char getNextChar();
	char peekNextChar();
	void putBackLastChar();

	Token charAlpha();
	Token charDigit();

private://members
	/// @brief the code file read-in
	std::shared_ptr<std::string> m_pfile;
	/// @brief the position at the next one of the extracted characters.
	std::size_t m_file_pos;	
	/// @brief the line number
	std::size_t m_line;
	/// @brief the position of current line
	std::size_t m_line_pos;
	/// @brief the last extracted character
	char m_last_char;
	/// @brief the current token
	Token m_token;
	/// @brief the current word
	std::string m_word;
	/// @brief the WordMap to get token mapped from string
	WordMap m_wordmap;
};//class Lexer

}//namespace PL0

