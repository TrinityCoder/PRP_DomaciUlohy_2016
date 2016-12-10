#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define PRECOMPUTE_UP_TO 1000000LL // (= 10^6)

typedef long long llong;

llong* primes;
llong primes_count;

void atexit_cleanup();
void init_primes(); // Vygeneruje prvocisla pomoci Eratosthenova sita.
void factorize(char* num); // Rozlozi cislo reprezentovane retezcem 'num' na prvocinitele.
bool valid_string_number_repre(char* str);
void string_divided_by_llong(char* divident, llong divisor, char* result, llong* rem);

int main(int argc, char** argv) {
	atexit(atexit_cleanup);
	init_primes();
	char inp[102]; // 100 cifer + \n + \0

	while(fgets(inp, 102, stdin) != NULL && !feof(stdin)) {
		if(inp[0] == '0')
			return 0;

		if(!valid_string_number_repre(inp)) {
			fprintf(stderr, "Error: Chybny vstup!\n");
			return 100;
		}
		factorize(inp);
	}

	return 0;
}

/*
 * void atexit_cleanup()
 *
 * Tato funkce je zaregistrovana ve funkci main volanim
 *       atexit(atexit_cleanup);     (hned prvni prikaz v tele funkce main)
 * Diky tomu bude automaticky zavolana vzdy pri ukoncovani programu.
*/
void atexit_cleanup() {
	if(primes != NULL)
		free(primes);
}

/*
 * void init_primes()
 *
 * Vygeneruje pole vsech prvocisel od 2 do PRECOMPUTE_UP_TO (vcetne).
 * Ukazatel na toto pole ulozi do globalni promenne 'primes'.
 * Pocet prvocisel v poli 'primes' ulozi do globalni promenne 'primes_count'.
*/
void init_primes() {
	bool* is_prime = malloc(sizeof(bool) * (PRECOMPUTE_UP_TO + 1));
	for(llong i = 2LL; i <= PRECOMPUTE_UP_TO; ++i) {
		is_prime[i] = true;
	}
	primes_count = PRECOMPUTE_UP_TO - 1LL;
	is_prime[0] = is_prime[1] = false;
	llong algorithm_can_stop = sqrt(PRECOMPUTE_UP_TO) + 1LL;
	for(llong i = 2LL; i <= algorithm_can_stop; ++i) {
		if(is_prime[i]) {
			for(llong j = 2LL * i; j <= PRECOMPUTE_UP_TO; j += i) {
				if(is_prime[j]) {
					is_prime[j] = false;
					--primes_count;
				}
			}
		}
	}
	primes = malloc(sizeof(llong) * primes_count);
	llong* tmp = primes;
	for(llong i = 0LL; i <= PRECOMPUTE_UP_TO; ++i) {
		if(is_prime[i]) {
			*(tmp++) = i;
		}
	}
	free(is_prime);
}

/*
 * void factorize(char* num)
 *
 * Rozlozi cislo reprezentovane textovym retezcem 'num'
 * na soucin prvocinitelu.
*/
void factorize(char* num) {
	if(num[0] == '1' && num[1] == '\0') {
		printf("Prvociselny rozklad cisla 1 je:\n1\n");
		return;
	}
	printf("Prvociselny rozklad cisla %s je:\n", num);
	char temp_str[102];
	strcpy(temp_str, num);

	llong rem, multiplicity;
	bool first_factor = true;
	for(int i = 0; i < primes_count; ++i) {
		rem = 0LL;
		multiplicity = -1LL;
		while(rem == 0) {
			strcpy(num, temp_str);
			++multiplicity;
			string_divided_by_llong(temp_str, primes[i], temp_str, &rem);
		}

		strcpy(temp_str, num);
		if(multiplicity == 0)
			continue;

		if(first_factor) {
			first_factor = false;
			printf("%lld", primes[i]);
		} else {
			printf(" x %lld", primes[i]);
		}

		if(multiplicity > 1)
			printf("^%lld", multiplicity);
	}

	printf("\n");
}

/*
 * bool valid_string_number_repre(char* str)
 *
 * Vrati true, pokud 'str' je korektni null-terminated retezec reprezentujici
 * nejake nezaporne cislo.
*/
bool valid_string_number_repre(char* str) {
	if(!isdigit(str[0]))
		return false;

	size_t str_len = strlen(str);
	if(str_len > 1 && str[str_len - 1] == '\n')
		str[str_len-- - 1] = '\0';

	for(int i = 0; i < str_len; ++i) {
		if(!isdigit(str[i])) {
			return false;
		}
	}

	return true;
}

/*
 * void string_divided_by_llong(char* divident, llong divisor, char* result, llong* rem)
 *
 * Provede celociselne deleni se zbytkem, kde delenec je cislo reprezentovane
 * retezcem 'divident' a delitel je cislo v promenne 'divisor'.
 * Vysledek zapise do retezce 'result' (a korektne jej zakonci znakem '\0')
 * a zbytek po deleni zapise do promenne *rem.
*/
void string_divided_by_llong(char* divident, llong divisor, char* result, llong* rem) {
	llong temp_divident = *divident++ - '0';
	if(temp_divident >= divisor) {
		*result++ = (temp_divident / divisor) + '0';
		*rem = temp_divident % divisor;
		temp_divident = *rem;
	} else {
		*rem = temp_divident % divisor;
	}

	while(*divident != '\0') {
		temp_divident *= 10LL;
		temp_divident += *divident++ - '0';
		*rem = temp_divident % divisor;
		*result++ = (temp_divident / divisor) + '0';
		temp_divident = *rem;
	}

	*result = '\0';
}
