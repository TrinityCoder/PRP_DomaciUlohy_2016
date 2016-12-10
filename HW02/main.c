#include <stdio.h>
#include <stdbool.h>

bool check_bounds(int inp);

int main(int argc, char** argv) {
	int inp;
	int total_numbers, even_numbers, positive_numbers, negative_numbers,
		minimum, maximum, sum_of_all;
	if(scanf("%d", &inp) != 1)
		return 0;
	if(!check_bounds(inp)) {
		printf("Error: Vstup je mimo interval!\n");
		return 100;
	}

	total_numbers = 1;
	even_numbers = (inp % 2 == 0) ? 1 : 0;
	positive_numbers = (inp > 0) ? 1 : 0;
	negative_numbers = (inp < 0) ? 1 : 0;
	minimum = maximum = inp;
	sum_of_all = inp;

	while(scanf("%d", &inp) == 1) {
		if(!check_bounds(inp)) {
			printf("\nError: Vstup je mimo interval!\n");
			return 100;
		}

		++total_numbers;
		if(inp % 2 == 0)
			++even_numbers;
		if(inp > 0)
			++positive_numbers;
		else if(inp < 0)
			++negative_numbers;
		if(inp < minimum)
			minimum = inp;
		else if(inp > maximum)
			maximum = inp;
		sum_of_all += inp;
	}

	printf("Pocet cisel: %d\n", total_numbers);
	printf("Pocet kladnych: %d\n", positive_numbers);
	printf("Pocet zapornych: %d\n", negative_numbers);
	printf("Procento kladnych: %.2f\n", 100 * positive_numbers / (float)total_numbers);
	printf("Procento zapornych: %.2f\n", 100 * negative_numbers / (float)total_numbers);
	printf("Pocet sudych: %d\n", even_numbers);
	printf("Pocet lichych: %d\n", total_numbers - even_numbers);
	printf("Procento sudych: %.2f\n", 100 * even_numbers / (float)total_numbers);
	printf("Procento lichych: %.2f\n", 100 * (total_numbers - even_numbers) / (float)total_numbers);
	printf("Prumer: %.2f\n", sum_of_all / (float)total_numbers);
	printf("Maximum: %d\n", maximum);
	printf("Minimum: %d\n", minimum);

	return 0;
}

bool check_bounds(int inp) {
	if(inp >= -10000 && inp <= 10000)
		return true;

	return false;
}
