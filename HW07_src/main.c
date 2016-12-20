/*
 * HW07 - Lamani hesla
 *
 * Tento program implementuje ulohu lamani hesla.
 * Jazyk: C99
 * Autor: Miroslav Mares
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#include "lock.h"	// pro volitelnou cast.

#define INPUT_LENGTH 9    // Vcetne zaverecneho '\0' charu.

#define ERROR_STDIN_READ_ERROR() fprintf(stderr,\
		"Error 666: Doslo k CHYBE (ferror) pri cteni ze stdin!!!\n"); exit(666);
#define ERROR_WRONG_INPUT() fprintf(stderr, "Error: Chybny vstup!\n"); exit(100);
#define SWAP_CHAR(x, y) do{ char temp = x; x = y; y = temp; } while(0)

#if MIREK_DEBUG
#define DEBUG_PRINTF(format, ...) printf("[DEBUG_PRINTF]: " format "\n", __VA_ARGS__ );
#else
#define DEBUG_PRINTF(...) ;
#endif

static const char* PRP_OPTIONAL = "-prp-optional";
static bool prp_optional = false;

void permutation_generator(char* alphabet, int i, int last_index);

void swap_char(char* first, char* second) {
	char tmp = *first;
	*first = *second;
	*second = tmp;
}

void alphabet_sort(char* first, char* last) {
	if (last <= first) {
		return;
	}

	bool sort_completed;
	do {
		sort_completed = true;
		for(char* iter = first; iter < last; ++iter) {
			if(*iter > *(iter + 1)) {
				swap_char(iter, iter + 1);
				sort_completed = false;
			}
		}
	} while(sort_completed == false);
}

int main(int argc, char** argv) {
	char input[INPUT_LENGTH];

	for(int i = 0; i < argc; ++i) {
		if(strcmp(argv[i], PRP_OPTIONAL) == 0) {
			prp_optional = true;
			break;
		}
	}

	// Nacteme vstup pomoci funkce fgets.
	if(fgets(input, INPUT_LENGTH, stdin) == NULL) {
		// fgets() vraci NULL prave ve dvou pripadech:
		// 1) EOF jiz pred nactenim prvniho znaku (feof(stdin) == TRUE) nebo
		// 2) Doslo k chybe pri cteni (ferror(stdin) == TRUE).
		if(ferror(stdin)) {
			ERROR_STDIN_READ_ERROR();
		}
		if(feof(stdin)) {
			ERROR_WRONG_INPUT();
		}
	}

	size_t input_len = strlen(input);

	// Odstraneni pripadneho \n tesne pred \0.
	if(input[input_len - 1] == '\n') {
		input[--input_len] = '\0';
	}

	for(int i = 0; i < input_len; ++i) {
		if(!isalpha(input[i]) && !isdigit(input[i])) {
			// Znak v input[i] neni ani pismeno, ani cislo
			// - tj. je nevalidni.
			ERROR_WRONG_INPUT();
		}
	}

	// Pripadne dalsi kontroly vstupu zadejte sem...
	DEBUG_PRINTF("input po osetreni pripadneho \\n pred \\0: %s", input);

	// Tak, vstup je validni, zacneme generovat permutace.
	permutation_generator(input, 0, input_len - 1);

	if(prp_optional) {
		fprintf(stderr, "Error: Heslo nebylo nalezeno!\n");
		return 101;
	}

	return 0;
}

void permutation_generator(char* str, int i, int last_index) {
	static int passwords_tried = 0;
	if(i == last_index) {
		++passwords_tried;
		if(prp_optional) {
			if(unlock(str)) {
				printf("%s - %dx\n", str, passwords_tried);
				exit(0);	// MUHAHAHAHAHAHAHAHAAAA...
			}
		} else {
			printf("%s\n", str);
			return;
		}
	}

	for(int j = i; j <= last_index; ++j) {
		swap_char(&(str[j]), &(str[i]));
		alphabet_sort(&(str[i + 1]), &(str[last_index]));
		permutation_generator(str, i + 1, last_index);
		alphabet_sort(&(str[i + 1]), &(str[last_index]));
		swap_char(&(str[j]), &(str[i]));
	}
}
