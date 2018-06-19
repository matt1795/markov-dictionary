// Markov Dictionary Interface
//
// Author: Matthew Knight
// File Name: markov_dictionary.h
// Date: 2018-06-18
//
// This module defines the types and interfaces of what I'm calling a "Markov
// Dictionary" which is a method I thought up for recording markov chains.

#include <stdio.h>
#include <stdint.h>

// Markov dictionary header type
typedef struct {
	char *name;
	text_t *list;
	text_t *prev;
	uint32_t count;
} markov_dict_t;

// Text entry type
typedef struct {
	text_t *next;
	text_ref_t *list;
	uint32_t count;
	char *str;
} text_t;

// Text reference type
typedef struct {
	text_ref_t *next;
	text_t *ref;
	uint32_t count;
} text_ref_t;

// Initialize dictionary
markov_dict_t *init_dict(char *name);

// Add text to dictionary
text_t *add_text(markov_dict_t *dict, char *str);

// Print dictionary to file in yaml format
int print_dict(markov_dict_t *dict, FILE *f);

// Free dictionary from memory
int free_dict(markov_dict_t *dict);
