#include <lexer/Lexer.hpp>

// STL
#include <iostream>
#include <memory>
#include <string>
// C-STL
#include <cstdio>
#include <cctype>
// PL0
#include <token.hpp>

namespace PL0 {

Lexer::Lexer(const std::shared_ptr<std::string> filestr) :
	m_pfile(filestr),
	m_file_pos(0),
	m_line(1),
	m_line_pos(0),
	m_last_char(' '),
	m_token(),
	m_word(),
	m_wordmap()
{}

Lexer::~Lexer()
{}

bool Lexer::getNextToken() {
	// eat spaces
	while(isblank(m_last_char))
		m_last_char = this->getNextChar();

	if(m_last_char == std::char_traits<char>::eof()) {
		m_token = Token::tk_eof;
		// m_word does not change for optimization
	} else if(m_last_char == '\n') {
		m_token = Token::tk_linebreak;
		// m_word does not change for optimization
		return true;
	} else if(isalpha(m_last_char)) {
		m_token = this->charAlpha();
		return true;
	} else if(isdigit(m_last_char)) {
		m_token = this->charDigit();
		return true;
	} else {

	}//if-else

	throw std::runtime_error(
			"Unqualified token at ("
			+ std::to_string(m_line)
			+ ", "
			+ std::to_string(m_line_pos)
			+ ")"
			);
	return false;
}//getNextToken()

char Lexer::getNextChar() {
	if(m_file_pos >= m_pfile->length())
		return std::char_traits<char>::eof();

	char ret = (*m_pfile)[m_file_pos];

	if(ret == '\n' || ret == '\r') {
		char peek = (*m_pfile)[m_file_pos+1];
		if((ret == '\n' && peek == '\r') || (ret == '\r' && peek == '\n')) {
			++m_file_pos;
		}//if

		++m_line;
		m_line_pos = 0;
		ret = '\n';
	}//if-else

	++m_file_pos;
	++m_line_pos;
	return ret;
}//getNextChar()

char Lexer::peekNextChar() {
	if(m_file_pos >= m_pfile->length())
		return std::char_traits<char>::eof();
	return (*m_pfile)[m_file_pos];
}//peekNextChar()

void Lexer::putBackLastChar()
{ --m_file_pos; }

Token Lexer::charAlpha() {
	m_word = "";
	while(isalnum(m_last_char)) {
		if(m_wordmap.is_operator(m_last_char)) {
			this->putBackLastChar();
			break;
		}//if
		m_word += m_last_char;
		m_last_char = getNextChar();
	}//while

	Token tok;
	if(m_wordmap.get_word_token(m_word, tok))
		return tok;

	throw std::runtime_error(
			"Unqualified token at ("
			+ std::to_string(m_line)
			+ ", "
			+ std::to_string(m_line_pos)
			+ ")"
			);
}//tokenAlpha()

Token Lexer::charDigit() {
	return Token::tk_eof;
}//charDigit()

}//namespace PL0


