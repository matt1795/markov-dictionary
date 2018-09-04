// Token Reference Class
//
// Author: Matthew Knight
// File Name: token-reference.cpp
// Date: 2018-08-31
//
// This class is meant to reference an existing token in the markov graph and to
// keep track how many times it follows the owner of the token reference list

#include <iostream>
#include "../inc/token-reference.hpp"

TokenReference::TokenReference(Token &token) : token(token), count(1) {}

// Get the token string refered to
std::string &TokenReference::getToken() {
	return token.getToken();
}
