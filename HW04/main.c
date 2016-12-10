#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define PRECOMPUTE_UP_TO 1000000LL // (= 10^6)

typedef long long llong;

llong* primes; // Ukazatel na pole prvocisel.
llong primes_count; // Pocet prvku (cisel) v poli 'primes'.

void atexit_cleanup();
void init_primes(); // Vygeneruje pole prvocisel pomoci Eratosthenova sita.
void factorize(llong num); // Rozlozi 'num' na prvocinitele.

int main(int argc, char** argv) {
	atexit(atexit_cleanup);
	init_primes();

	llong inp;
	while(scanf("%lld", &inp) == 1) {
		if(inp >= 1LL) {
			factorize(inp);
		} else if(inp == 0LL) {
			break;
		} else {
			fprintf(stderr, "Error: Chybny vstup!\n");
			exit(100);
		}
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
 * void factorize(llong num)
 *
 * Rozlozi 'num' na soucin prvocinitelu a rozklad vypise na stdout.
 * K vypoctu rozkladu pouziva prvocisla z globalniho pole 'primes'.
*/
void factorize(llong num) {
	printf("Prvociselny rozklad cisla %lld je:\n", num);
	if(num == 1LL) {
		printf("1\n");
		return;
	}
	llong multiplicity;
	bool is_first_factor = true;
	for(llong i = 0LL; i < primes_count; ++i) {
		multiplicity = 0LL;
		while(num % primes[i] == 0LL) {
			++multiplicity;
			num /= primes[i];
		}
		if(multiplicity != 0LL) {
			if(is_first_factor) {
				is_first_factor = false;
				printf("%lld", primes[i]);

			} else {
				printf(" x %lld", primes[i]);
			}
			if(multiplicity > 1LL) {
				printf("^%lld", multiplicity);
			}
		}
		if(num == 1LL)
			break;
	}
	printf("\n");
}
