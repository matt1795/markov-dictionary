// Token Reference Class
//
// Author: Matthew Knight
// File Name: token-reference.cpp
// Date: 2018-08-31
//
// This class is meant to reference an existing token in the markov graph and to
// keep track how many times it follows the owner of the token reference list

#ifndef TOKEN_REFERENCE_HPP_
#define TOKEN_REFERENCE_HPP_

#include "./markov-graph.hpp"
#include "./token-base.hpp"
#include "./token.hpp"

class Token;

class TokenReference : public TokenBase {
	friend class MarkovGraph;
	Token &token;
	int count;

public:
	TokenReference(Token &token);
	std::string &getToken();
};

#endif
