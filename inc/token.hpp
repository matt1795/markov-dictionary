// Token class
//
// Author: Matthew Knight
// File Name: token.hpp
// Date: 2018-08-31
//
// This class represents a text based token, normally it would represent a
// single word. It has a counter for how many times it has shown up, and has a
// list of reference tokens that point to other tokens that follow this one in
// text

#ifndef TOKEN_HPP_
#define TOKEN_HPP_

#include "token-base.hpp"
#include "markov-graph.hpp"
#include "token-reference.hpp"

class TokenReference;

class Token : public TokenBase{
	friend class MarkovGraph;
	std::list<TokenReference> refs;
	int count;
	std::string token;

public:
	Token(std::string &token);
	std::string &getToken();	
	void addReference(Token &ref);
};

#endif
