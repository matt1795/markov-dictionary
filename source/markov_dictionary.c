// Markov Dictionary Implementation
//
// Author: Matthew Knight
// File Name: markov_dictionary.c
// Date: 2018-06-18
//
// This is the implementation of the "Markov Dictionary"

#include <string.h>
#include "markov_dictionary.h"

// Private functions (to this file)


// Initialize dictionary
markov_dict_t *init_dict(char *name) {
	markov_dict_t *dict = (markov_dict_t *)malloc(sizeof(markov_dict_t));
	dict->name = name;
	dict->list = NULL;
	dict->prev = NULL;
	dict->count = 0;
	return dict;
}

// Add text to dictionary
text_t *add_text(markov_dict_t *dict, char *str) {
	dict->count++;

	// First text entry
	if (dict->prev == NULL) {
		dict->list = init_text(str);
		dict->prev = dict->list;
	}

	text_ref_t *before = &dict->last->list;
	text_ref_t *cursor = dict->last->list;

	while (cursor != NULL) {
		int32_t diff = strcmp(str, cursor->ref->str);
		
		// New text does not precede current
		if (diff > 0) {
			before = cursor;
			cursor = cursor->next;
		}
		
		// strings match
		else if (diff == 0) {
			cursor->count++;
			cursor->ref->count++;
			dict->prev = cursor->ref;
		
		// New text precedes current, insert here
		} else {
			// TODO:
			// insert or find in dictionary
			// insert reference
		}
	
	}
}

// Print dictionary to file in yaml format
int print_dict(markov_dict_t *dict, FILE *f) {
	// TODO: finish print function
}

// Free dictionary from memory
int free_dict(markov_dict_t *dict) {
	// TODO: finish free function
}
