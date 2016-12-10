#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERROR_100() do { fprintf(stderr, "Error: Chybny vstup!\n");\
					exit(100); } while(0)
#define ERROR_101() do { fprintf(stderr, "Error: Vstup mimo interval!\n");\
					exit(101); } while(0)
#define ERROR_102() do { fprintf(stderr, "Error: Sirka neni liche cislo!\n");\
 					exit(102); } while(0)
#define ERROR_103() do { fprintf(stderr, "Error: Neplatna velikost plotu!\n");\
					exit(103); } while(0)

bool check_bounds(int num) {
	return (num >= 3 && num <= 69) ? true : false;
}

void vykresli_strechu(int sirka);

void switch_char(char* ch) {
	*ch = (*ch == 'o') ? '*' : 'o';
}

int main(int argc, char** argv) {
	int sirka_domku, vyska_domku, rozmer_plotu;
	if(scanf("%d %d", &sirka_domku, &vyska_domku) != 2)
		ERROR_100();
	if(!check_bounds(sirka_domku) || !check_bounds(vyska_domku))
		ERROR_101();
	if(sirka_domku % 2 == 0)
		ERROR_102();

	if(sirka_domku == vyska_domku) {
		if(scanf("%d", &rozmer_plotu) != 1)
			ERROR_100();
		if(rozmer_plotu <= 0 || rozmer_plotu >= vyska_domku)
			ERROR_103();
	}

	vykresli_strechu(sirka_domku);

	if(sirka_domku == vyska_domku) {
		for(int i = vyska_domku - 1; i > 1; --i) {
			printf("X");
			for(int j = 1; j <= sirka_domku - 2; ++j) {
				if((i + j) % 2 == 0) {
					printf("*");
				} else {
					printf("o");
				}
			}
			printf("X");
			// Jsme jiz dost nizko na to, abychom vykreslovali plot vpravo?
			if(i == rozmer_plotu) {
				// (Horni "hrana" plotu.)
				if(rozmer_plotu % 2 == 1) {
					printf("|");
				}
				for(int j = 0; j < rozmer_plotu - 1; j += 2) {
					printf("-|");
				}
			} else if(i > 1 && i < rozmer_plotu) {
				// "Vnitrni cast plotu".
				if(rozmer_plotu % 2 == 1)
					printf("|");
				for(int j = 0; j < rozmer_plotu - 1; j += 2) {
					printf(" |");
				}
			}
			printf("\n");
		}
		for(int i = 1; i <= sirka_domku; ++i)
			printf("X");
		if(rozmer_plotu % 2 == 1)
			printf("|");
		for(int i = 0; i < rozmer_plotu - 1; i += 2)
			printf("-|");
		printf("\n");
	} else {
		for(int i = vyska_domku - 1; i > 1; --i) {
			printf("X");
			for(int j = 1; j <= sirka_domku - 2; ++j)
				printf(" ");
			printf("X\n");
		}
		for(int j = 1; j <= sirka_domku; ++j)
			printf("X");
		printf("\n");
	}

	return 0;
}

void vykresli_strechu(int sirka) {
	int i = (sirka + 1) / 2;
	int j = i;
	while(i > 1) {
		for(int k = 1; k <= j; ++k) {
			if(k == i || k == j)
				printf("X");
			else
				printf(" ");
		}
		printf("\n");
		++j;
		--i;
	}
	for(int k = 1; k <= sirka; ++k)
		printf("X");
	printf("\n");
}
