// Markov Graph Class
//
// Author: Matthew Knight
// File Name: markov-graph.hpp
// Date: 2018-08-31
//
// This class implements a graph data structure for representing markov chains.
// For simplicity's sake the insertion method assumes that a string is a
// multi-sentence structure. What this means is that it will insert tokens that
// not only record word use, but also sentence structure. All input text is
// converted to lower case text so that structural tokens can be recorded in
// upper case.

#ifndef MARKOV_GRAPH_HPP_
#define MARKOV_GRAPH_HPP_

#include <list>
#include "token.hpp"

class MarkovGraph {
	std::list<Token> tokens;

public:
	MarkovGraph();

	// Insert multi paragraph text into graph
	void insertText(string &text);

	// Generate random text
	unique_ptr<std::string> genText();
};

#endif
