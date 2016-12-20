#include <stdio.h>
#include <stdbool.h>

bool check_bounds(int num);

int main(int argc, char** argv) {
	int inp1, inp2;
	scanf("%d %d", &inp1, &inp2);

	if(!check_bounds(inp1) || !check_bounds(inp2)) {
		printf("Vstup je mimo interval!\n");
		return 0;
	}

	printf("Desitkova soustava: %d %d\n", inp1, inp2);
	printf("Sestnactkova soustava: %x %x\n", inp1, inp2);
	printf("Soucet: %d + %d = %d\n", inp1, inp2, inp1 + inp2);
	printf("Rozdil: %d - %d = %d\n", inp1, inp2, inp1 - inp2);
	printf("Soucin: %d * %d = %d\n", inp1, inp2, inp1 * inp2);
	if(inp2 == 0)
		printf("Nedefinovany vysledek!\n");
	else
		printf("Podil: %d / %d = %d\n", inp1, inp2, inp1 / inp2);
	printf("Prumer: %.1f\n", (inp1 + inp2) / 2.0f);

	return 0;
}

/*
 * bool check_bounds(int num)
 *
 * Zkontroluje, zda se cislo 'num' nachazi v intervalu <-10 000, 10 000>
 * a vrati true, pokud ano; jinak false.
*/
bool check_bounds(int num) {
	if(num >= -10000 && num <= 10000)
		return true;
	
	return false;
}
