#pragma once

// STL
#include <unordered_map>
#include <string>
// PL0Compiler
#include <token.hpp>
#include <lexer/easytypes.hpp>

namespace PL0 {

class WordMap
{
public://function
	WordMap();
	~WordMap();
	
	WordMap(const WordMap & rhs) = delete;
	WordMap(WordMap && rhs) = delete;
	WordMap & operator=(const WordMap & rhs) = delete;
	WordMap & operator=(WordMap && rhs) = delete;

	inline bool get_word_token(const std::string & key, Token & tok) const
	{
		auto ret = m_word_map.find(key);
		if(ret != m_word_map.end()) {
			tok = ret->second;
			return true;
		}//if
		return false;
	}//get_word_token(key, tok)

	inline bool get_op_token(const std::string & key, Token & tok) const
	{
		auto ret = m_operator_map.find(key);
		if(ret != m_operator_map.end()) {
			tok = ret->second.first;
			return true;
		}//if
		return false;
	}//get_op_token(key, tok)

	inline bool is_operator(const char ch) const
	{ return m_operator_pool.find(ch) != std::string::npos; }

private://members
	const std::unordered_map<std::string, Token> m_word_map;
	const std::string m_operator_pool;
	const std::unordered_map<std::string, std::pair<Token, priority> > m_operator_map;
};//class WordMap

}//namespace PL0

