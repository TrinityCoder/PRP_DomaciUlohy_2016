#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

// Pro aktivati DPRINTF debugovaci funkce prohodte komentare na nasledujicich dvou radcich:
// #define DPRINTF(...) fprintf(stderr, __VA_ARGS__)
#define DPRINTF(...) do { } while(0);

static const char* PRP_OPTIONAL = "-prp-optional";

struct _dynstr_t {
	char* str;
	size_t capacity;
	size_t used;
};
typedef struct _dynstr_t dynstr_t;

#define DYNSTR_INITIAL_CAPACITY 100
#define FULL_ROUND_SHIFT_COUNT 52 /* Pocet posuvu, nez se pres
			malou a velkou abecedu dostanu na vychozi pozici (= 2 * 26).
			Tj. tolikrat posunou retezec Caesarovou sifrou o jedno misto
			je to same, jako jej neposunout vubec. */

static dynstr_t encrypted; /* Bude obsahovat prvni radek vstupu - zasifrovanou
			 komunikaci, ktera byla odposlechnuta dobre. */
static dynstr_t eavesdrop; /* Bude obsahovat druhy radek vstupu - desifrovanou
			 komunikaci, ktera muze obsahovat chyby. */
static dynstr_t result; // Vysledek bude uchovan zde.

// Bezpecne uvolneni pameti behem konceni programu:
void atexit_cleanup() {
	free(encrypted.str);
	free(eavesdrop.str);
	free(result.str);
}

// Pripravi 'encrypted' i 'eavesdrop' k praci:
void dynstr_init() {
	encrypted.capacity = eavesdrop.capacity = DYNSTR_INITIAL_CAPACITY;
	encrypted.str = calloc(encrypted.capacity, sizeof(char));
	eavesdrop.str = calloc(eavesdrop.capacity, sizeof(char));
}

// Funkce pro praci s dynstr_t strukturou:
void dynstr_double_realloc(dynstr_t* const ptr); // Zdvojnasobi kapacitu retezce ptr->str.
void dynstr_append_char(dynstr_t* const ptr, const char ch); /* Prida 'ch' na konec ptr->str
							a inkrementuje ptr->used. */
// Udela z 'dest' zcela totoznou kopii 'orig'.
void dynstr_clone(dynstr_t* const dest, const dynstr_t* const orig);

/* Implementuje "naivni vypocet" vzdalenosti dvou textovych retezcu. */
size_t naive_distance(const dynstr_t* const first, const dynstr_t* const second);
/* Implementuje vypocet Levenshteinovy vzdalenosti dvou retezcu. */
size_t levenshtein_distance(const dynstr_t* const first, const dynstr_t* const second);

/* Do retezce result->str zapise retezec z mnoziny "Caesarovskych posunuti",
   ktery je ze vsech nejblize. (Zadani je vzdy jednoznacne, pripominam.)
   TATO FUNKCE OCEKAVA JAKO PRVNI ARGUMENT KLON STRUKTURY 'second', tj.
   jiny objekt, ktery je ve vsem totozny! ('str', capacity, used, ...)
   Dostane-li retezce ruzne delky (nebo oba nulove delky), nebo nejsou splneny
   uvedene podminky, vrati false, jinak true.*/
bool find_closest_naive(dynstr_t* const result, const dynstr_t* const first,
								const dynstr_t* const second);

/* Tato funkce je ZCELA TOTOZNA S FUNKCI find_closest_naive, pouze pocita
   Levenshteinovy vzdalenosti a tudiz muze vzit i retezce ruzne/nulove delky. */
bool find_closest_levenshtein(dynstr_t* const result, const dynstr_t* const first,
								const dynstr_t* const second);

/* Nacte jeden radek ze vstupu. Radek muze obsahovat POUZE znaky [a-zA-Z].
   * \n musi ukoncovat kazdy radek krome posledniho, jinak se vstup nenacte korektne.
   * Funkce vzdy zahazuje \n (tj. nepouziva ungetc).
   * Prvni znak nesmi byt \n, druhy a dalsi muzou -> zahodi se a povazuje se to za
     ukonceny radek.
   */
bool parse_inp_line(dynstr_t* dest) {
	char temp;
	if(scanf("%c", &temp) != 0 && isalpha(temp)) {
		dynstr_append_char(dest, temp);
	} else {
		return false;
	}
	while(scanf("%c", &temp) != 0 && isalpha(temp)) {
		dynstr_append_char(dest, temp);
	}
	if(temp == '\n' || feof(stdin))
		return true;
	else {
		return false;
	}
}

// Vrati true, jestlize je mezi argumenty prikazove radky predan PRP_OPTIONAL.
bool prp_optional(int argc, char** argv) {
	for(int i = 0; i < argc; ++i)
		if(strcmp(argv[i], PRP_OPTIONAL) == 0)
			return true;
	return false;
}

#define ERROR_100() do { fprintf(stderr, "Error: Chybny vstup!\n"); exit(100); } while(0)
#define ERROR_101() do { fprintf(stderr, "Error: Chybna delka vstupu!\n"); exit(101); } while(0)

int main(int argc, char** argv) {
	dynstr_init();
	atexit(atexit_cleanup);

	if(parse_inp_line(&encrypted) == false || parse_inp_line(&eavesdrop) == false)
		ERROR_100();

	if(prp_optional(argc, argv) == false) {
		// Pouzivame naivni vzdalenost.
		DPRINTF("NAIVNI verze...\n");
		if(encrypted.used != eavesdrop.used)
			ERROR_101();

		dynstr_clone(&result, &encrypted);
		assert(find_closest_naive(&result, &encrypted, &eavesdrop) == true);
	} else {
		// Pouzivame Levenshteinovu vzdalenost.
		DPRINTF("Levenshteinova verze...\n");
		dynstr_clone(&result, &encrypted);
		assert(find_closest_levenshtein(&result, &encrypted, &eavesdrop) == true);
	}

	printf("%s\n", result.str);

	return 0;
}

void dynstr_double_realloc(dynstr_t* const ptr) {
	/* Prodlouzime ptr->str na dvojnasobek - nejprve zvetsime na dvojnasobek
	   str->capacity, na tuto velikost ptr->str realokujeme a nakonec
	   nastavime znaky ptr->str[ptr->used] ... az ptr->str[ptr->capacity - 1]
	   na nulu.   */
	ptr->capacity *= 2;
	ptr->str = realloc(ptr->str, ptr->capacity);
	memset(ptr->str + ptr->used, 0, sizeof(char) * ptr->used);
}

void dynstr_append_char(dynstr_t* const ptr, const char ch) {
	/* Dbame na to, aby aspon posledni pismeno retezce ptr->str VZDY zustalo
	nezmenene, tedy 0 (tedy '\0'). */
	if(ptr->used + 1 >= ptr->capacity)
		dynstr_double_realloc(ptr);
	ptr->str[ptr->used++] = ch;
}

void dynstr_clone(dynstr_t* const dest, const dynstr_t* const orig) {
	free(dest->str);
	dest->used = orig->used;
	dest->capacity = orig->capacity;
	dest->str = malloc(sizeof(char) * orig->capacity);
	strcpy(dest->str, orig->str);
	dest->str[dest->used] = '\0';
}

size_t naive_distance(const dynstr_t* const first, const dynstr_t* const second) {
	/* "Naivni vzdalenost" dvou STEJNE DLOUHYCH textovych retezcu
	    neni nic jineho, nez pocet odpovidajcich si znaku. */
	    if(first->used != second->used)
	    	return -1; // Nam se to nestane, ale jen tak pro jistotu...
	    size_t ret = 0;
	    for(size_t i = 0; i < first->used; ++i)
	    		if(first->str[i] == second->str[i])
				++ret;
		return ret;
}

// Vrati minimum ze tri cisel typu size_t ( = unsigned long, vetsinou).
static inline size_t minimum_of_triple(size_t a, size_t b, size_t c) {
	if(b < a)
		a = b;
	return (a < c) ? a : c;
}

size_t levenshtein_distance(const dynstr_t* const first, const dynstr_t* const second) {
	/* 	Pro vypocet Levenshteinovy vzdalenosti retezcu se pouziva napr. 2D matice;
	algoritmus je krasne popsany na wikipedii:
	     https://en.wikipedia.org/wiki/Levenshtein_distance
	Tento kod pouziva variantu "iterative with two matrix rows", tj.
	iterativni (nerekurzivni) metoda potrebujici k vypoctu jen dve pole
	integeru o velikosti (first->used + 1) a (second->used + 1).*/

	// Nejprve specialni podminky:
	if(first->used == 0)
		return second->used;
	if(second->used == 0)
		return first->used;
	if(strcmp(first->str, second->str) == 0)
		return 0;

	// A samotny vypocet:
	size_t* vec1 = malloc(sizeof(size_t) * (1 + second->used));
	size_t* vec2 = malloc(sizeof(size_t) * (1 + second->used));
	for(size_t i = 0; i <= second->used; ++i)
		vec1[i] = i;
	for(size_t i = 0; i < first->used; ++i) {
		vec2[0] = i + 1;
		size_t cost;
		for(size_t j = 0; j < second->used; ++j) {
			cost = (first->str[i] == second->str[j]) ? 0 : 1;
			vec2[j + 1] = minimum_of_triple(vec2[j] + 1,
								vec1[j + 1] + 1, vec1[j] + cost);
		}
		for(size_t j = 0; j < second->used; ++j) {
			vec1[j] = vec2[j];
		}
	}
	size_t res = vec2[second->used];
	free(vec1);
	free(vec2);
	return res;
}

// Provede "Caesarovske posunuti" o 'by' znaku nahoru (smerem od A k Z/a k z)
// retezce what->str.
static void shift(dynstr_t* const what, unsigned char by) {
	by %= FULL_ROUND_SHIFT_COUNT; // nebude potreba, jen pro ukazku...
/* CHMAP makro - zobrazi znak 'ch' na cislo <0, FULL_ROUND_SHIFT_COUNT), kde
   toto cislo neni nic nez cislo znaku v systemu 0->A, 1->B, 2->C, ...,
   kde po velke abecede ihned nasleduje mala.
   Makro INVERSE_CHMAP to dela obracene. */
#define CHMAP(ch) (isupper(ch) ? (ch - 'A') : (ch - 'a' + 'Z' - 'A' + 1))
#define INVERSE_CHMAP(i) (isupper(i + 'A') ? (i + 'A') : (i - ('Z' - 'A' + 1) + 'a'))
	for(int i = 0; i < what->used; ++i) {
		what->str[i] = INVERSE_CHMAP(((CHMAP(what->str[i]) + by) % FULL_ROUND_SHIFT_COUNT));
	}
#undef INVERSE_CHMAP
#undef CHMAP
}

bool find_closest_naive(dynstr_t* const result, const dynstr_t* const first,
								const dynstr_t* const second) {
	unsigned char shift_by_matches[FULL_ROUND_SHIFT_COUNT] = { 0 }; /* Na i-te pozici je cislo
	     vyjadrujici, jaka bude naivni vzdalenost mezi 'result' a 'first' v situaci,
		kdy 'result' posunu z vychozi pozice o 'i' znaku.
		Funkce tedy musi skoncit, az je 'result' posunuty o 'y' znaku oproti
		'first', kde y je index maxima pole shift_by_matches.  */
	if(strcmp(result->str, first->str) != 0)
		return false;
	signed char distance;
	for(int i = 0; i < first->used; ++i) {
		if(isupper(first->str[i]) ^ (isupper(second->str[i]))) { // ^ je xor
			if(first->str[i] < second->str[i]) {
				// tedy first->str[i] je upper case, second->str[i] je lower case
				distance = second->str[i] - 'a' + 1 + 'Z' - first->str[i];
			}
			else { // first->str[i] je lower case, second->str[i] je upper case.
				distance = first->str[i] - 'a' + 1 + 'Z' - second->str[i];
			}
	    } else { // budto jsou first->str[i] i second->str[i] oba upper case, nebo lower case.
			distance = second->str[i] - first->str[i];
			if(distance < 0) // "spletli" jsme si poradi
				distance += 'Z' - 'A' + 1 + 'z' - 'a' + 1;
	    }
	    ++shift_by_matches[distance];
	}
#if MIREK_DBG == 1
	DPRINTF("first->used == %5lu     second->used == %5lu\n", first->used, second->used);
	DPRINTF("shift_by_matches[] == {\n");
	int sum = 0;
	for(int i = 0; i < FULL_ROUND_SHIFT_COUNT; ++i) {
		sum += shift_by_matches[i];
		DPRINTF("[%3d] = %3u   ", i, shift_by_matches[i]);
		if((i + 1) % 6 == 0) {
			DPRINTF("\n");
		}
	}
	DPRINTF("}, sum = %d\n", sum);
#endif
	unsigned char best_shift_index = 0;
	for(int i = 1; i < FULL_ROUND_SHIFT_COUNT; ++i) { // hledame index maxima
		if(shift_by_matches[i] > shift_by_matches[best_shift_index])
			best_shift_index = i;
	}
	DPRINTF("best_shift_index == %u\n", best_shift_index);
	shift(result, best_shift_index);
	return true;
}

bool find_closest_levenshtein(dynstr_t* const result, const dynstr_t* const first,
								const dynstr_t* const second){
	int best_distance = levenshtein_distance(result, second),
	    best_distance_shift = 0;
	int temp = -1;
	for(int i = 1; i < FULL_ROUND_SHIFT_COUNT; ++i) {
		if((temp = levenshtein_distance(result, second)) < best_distance) {
			best_distance = temp;
			best_distance_shift = i;
		}
		shift(result, 1);
	}
	DPRINTF("best_distance_shift = %d, best_distance = %d\n",
				best_distance, best_distance_shift);
	shift(result, best_distance_shift);
	return true;
}
