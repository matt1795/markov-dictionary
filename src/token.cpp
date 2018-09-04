// Token class
//
// Author: Matthew Knight
// File Name: token.cpp
// Date: 2018-08-31
//
// This class represents a text based token, normally it would represent a
// single word. It has a counter for how many times it has shown up, and has a
// list of reference tokens that point to other tokens that follow this one in
// text

#include <iostream>
#include "../inc/token.hpp"

Token::Token(std::string &token) : token(token), count(1) {}

std::string &Token::getToken() {
	return token;
}

void Token::addReference(Token &ref) {

}
