// Test program for now
//
// Author: Matthew Knight
// File Name: main.cpp
// Date: 2018-08-31

#include "../inc/markov-graph.hpp"

int main() {
	MarkovGraph dict;
	std::string text = "This is  a sentence. This is another";	
	dict.insertText(text);	
	text = "not going to to \nthis";
	dict.insertText(text);	
	dict.print();
}
