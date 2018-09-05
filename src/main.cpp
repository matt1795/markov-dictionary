// Test program for now
//
// Author: Matthew Knight
// File Name: main.cpp
// Date: 2018-08-31

#include <iostream>

#include "markov-graph.hpp"

int main() {
	MarkovGraph dict;
	std::string text = "This is  a sentence. Here is someone";	
	dict.insertText(text);	
	text = "This is  another sentence.";	
	dict.insertText(text);	
	std::unique_ptr<std::string> newText = dict.genText();
	std::cout << *newText << std::endl;
}
