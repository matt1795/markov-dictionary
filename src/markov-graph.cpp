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

#include <iostream>
#include <algorithm>
#include "../inc/markov-graph.hpp"

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
	std::cout << "inserting: " << token << std::endl;
	auto it = tokens.begin(), newEntry = tokens.begin();
	for (; it != tokens.end(); it++) {
		int result = alphabetic(token, it->getToken());
		if (result < 0) {
			std::cout << "next" << std::endl;
			continue;
		} else if (result == 0) {
			std::cout << "found a match" << std::endl;
			newEntry = it;
			it->count++;
			break;
		} else {
			std::cout << "making new insertion" << std::endl;
			newEntry = tokens.emplace(it, token);
			break;
		}
	}
	if (it == tokens.end()) {
		std::cout << "Adding to end" << std::endl;
		newEntry = tokens.emplace(it, token);
	}
	
	// if last is not null, then insert reference
	if (last != nullptr) {
		std::cout << "Last: " << last->getToken() << std::endl;
		auto j = last->refs.begin();
		for (;j != last->refs.end(); j++) {
			int result = alphabetic(newEntry->getToken(), j->getToken());
			if (result < 0) {
				std::cout << "TOKEN REF: next" << std::endl;
				continue;
			} else if (result == 0) {
				std::cout << "TOKEN REF: found a match" << std::endl;
				j->count++;
				break;
			} else {
				std::cout << "TOKEN REF: making new insertion" << std::endl;
				last->refs.emplace(j, *newEntry);
				break;
			}
		}
		if (j == last->refs.end()) {
			std::cout << "TOKEN REF: Adding to end" << std::endl;
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
	std::cout
		<< "BOP" << std::endl
		<< "BOS" << std::endl;
	
	
	for (auto it = text.begin(); it != text.end(); it++) {
		if (isWhiteSpace(*it)) {
			if (temp.empty()) {
				continue;		
			} else {
				insertToken(temp);
				std::cout << temp << std::endl;
				temp.clear();
			}
		} else if (*it == '.') {
			if (!temp.empty()) {
				insertToken(temp);
				std::cout << temp << std::endl;
				temp.clear();
			}
			insertToken(EOS);
			std::cout << "EOS" << std::endl;
			endedSentence = true;
		} else {
			if (endedSentence) {
				insertToken(BOS);
				std::cout << "BOS" << std::endl;
				endedSentence = false;
			}
			temp += *it;
		}

	}
	if (!temp.empty()) {
		insertToken(temp);
		std::cout << temp << std::endl;
	}
	if (!endedSentence) {
		std::cout << "EOS" << std::endl;
		insertToken(EOS);
	}
	std::cout << "EOP" << std::endl;
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

}
