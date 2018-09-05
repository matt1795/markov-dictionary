// Markov Graph Class
//
// Author: Matthew Knight
// File Name: markov-graph.cpp
// Date: 2018-08-31
//
// This class implements a graph data structure for representing markov chains.
// For simplicity's sake the insertion method assumes that a string is a
// multi-sentence structure. What this means is that it will insert tokens that
// not only record word use, but also sentence structure. All input text is
// converted to lower case text so that structural tokens can be recorded in
// upper case.

#include "markov-graph.hpp"

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

// Check for whitespace -- whitespace is defined as asci characters under the
// value 21 and above value 126
inline bool isWhiteSpace(char c) {
	if (c == ' ' || c == '\n' || c == '\t')
		return true;
	else
		return false;
}

// 0 strings are the same
// 1 a and b are alphabetic
// -1 a and b are not alphabetic
inline int alphabetic(std::string &a, std::string &b) {
	int aLen = a.length();
	int bLen = b.length();
	for (int i = 0; i < std::min(aLen, bLen); i++) {
		if (a[i] < b[i]) {
			return 1;
		}
		if (a[i] > b[i]) {
			return -1;
		}
	}
	if (aLen == bLen) {
		return 0;
		std::cout << "It's a match" << std::endl;
	} else if (aLen < bLen) {
		return 1;
	} else {
		return -1;
	}
}

MarkovGraph::MarkovGraph() : last(nullptr) {}
	
// Insert single token
void MarkovGraph::insertToken(std::string &token) {
	// TODO: refactor
	auto it = tokens.begin(), newEntry = tokens.begin();
	for (; it != tokens.end(); it++) {
		int result = alphabetic(token, it->getToken());
		if (result < 0) {
			continue;
		} else if (result == 0) {
			newEntry = it;
			it->count++;
			break;
		} else {
			newEntry = tokens.emplace(it, token);
			break;
		}
	}
	if (it == tokens.end())
		newEntry = tokens.emplace(it, token);
	
	// if last is not null, then insert reference
	if (last != nullptr) {
		auto j = last->refs.begin();
		for (;j != last->refs.end(); j++) {
			int result = alphabetic(newEntry->getToken(), j->getToken());
			if (result < 0) {
				continue;
			} else if (result == 0) {
				j->count++;
				break;
			} else {
				last->refs.emplace(j, *newEntry);
				break;
			}
		}
		if (j == last->refs.end()) {
			last->refs.emplace(j, *newEntry);
		}
	}
	
	last = &(*newEntry);
}

// Insert multi paragraph text into graph
void MarkovGraph::insertText(std::string &text) {
	std::transform(text.begin(), text.end(), text.begin(), ::tolower);
	std::string temp;
	bool endedSentence = false, parsingToken = false;
	insertToken(BOP);
	insertToken(BOS);
	
	for (auto it = text.begin(); it != text.end(); it++) {
		if (isWhiteSpace(*it)) {
			if (temp.empty()) {
				continue;		
			} else {
				insertToken(temp);
				temp.clear();
			}
		} else if (*it == '.') {
			if (!temp.empty()) {
				insertToken(temp);
				temp.clear();
			}
			insertToken(EOS);
			endedSentence = true;
		} else {
			if (endedSentence) {
				insertToken(BOS);
				endedSentence = false;
			}
			temp += *it;
		}

	}
	if (!temp.empty())
		insertToken(temp);
	if (!endedSentence)
		insertToken(EOS);
	insertToken(EOP);
	last = nullptr;
}

void MarkovGraph::print() {
	for (auto it = tokens.begin(); it != tokens.end(); it++) {
		std::cout << it->token << ' ' << it->count << std::endl;
		for (auto jt = it->refs.begin(); jt != it->refs.end(); jt++) {
			std::cout << '\t' << jt->getToken() << ' ' << jt->count << std::endl;
		}
	}
}

// Generate random text
std::unique_ptr<std::string> MarkovGraph::genText() {
	std::unique_ptr<std::string> text(new std::string);
	std::list<Token>::iterator start;
	bool beginSentence;
	Token *next;

	// seed the random generator
	srand(time(NULL));

	// find beginning token
	for (start = tokens.begin(); start != tokens.end(); start++)
		if (start->getToken() == BOP)
			break;
	// Did not find BOP token
	if (start == tokens.end())
		return text;

	// initialize to BOP
	next = &(*start);

	// iterate until we get to EOP
	while (next->getToken() != EOP) {
		std::string token = next->getToken();
		if (token == BOP || token == BOS) {
			// do nothing
		} else if (token == EOS) {
			(*text).back() = '.';
			*text += " ";
		} else {
			*text += token;
			*text += " ";
		}
		
		// Determine the next token to use.
		int randCount = rand() % next->count;
		int acc = 0;
		auto it = next->refs.begin();
		for (; it != next->refs.end(); it++) {
			acc += it->count;
			if (acc > randCount)
				break;
		}
		next = &(it->token);	
	}
	return text;
}
