#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct _matrix_t {
	long* array;
	long rows, cols;
};
typedef struct _matrix_t matrix_t;

#define ERROR_100() do { fprintf(stderr, "Error: Chybny vstup!\n"); exit(100); } while(0)

// Prototypy:
matrix_t* create_matrix(long rows, long cols);
void free_matrix(matrix_t* matrix);
void resize_matrix(matrix_t* matrix, long rows_new, long cols_new);
long matrix_getval(matrix_t* matrix, long row, long col);
void matrix_setval(matrix_t* matrix, long row, long col, long val);
bool matrix_product(matrix_t* result, matrix_t* left, matrix_t* right);
void matrix_dump(matrix_t* matrix);
bool load_matrix_stdin(matrix_t* matrix);
void negate_matrix(matrix_t* matrix);

// Globalni promenne:
matrix_t* master;
matrix_t* product_buffer;
matrix_t* product_temp;
matrix_t* inp_buffer;

void atexit_do() {
	free_matrix(master);
	free_matrix(product_buffer);
	free_matrix(product_temp);
	free_matrix(inp_buffer);
}

int main(int argc, char** argv) {
	master = create_matrix(1, 1);
	product_buffer = create_matrix(1, 1);
	inp_buffer = create_matrix(1, 1);
	product_temp = create_matrix(1, 1);
	atexit(atexit_do);
	char operator_prev = '\0', operator_curr = '\0';

	bool last_iteration = false;
	while(1) {
		if((operator_curr == '+' || operator_curr == '-')
			&& (operator_prev == '+' || operator_prev == '-' )) {
				// Pricteme/odecteme inp_buffer k master.
				if(operator_prev == '-')
					negate_matrix(inp_buffer);
				if(inp_buffer->rows != master->rows
					|| inp_buffer->cols != master->cols)
					ERROR_100();
				for(int i = 0; i < master->rows * master->cols; ++i) {
					master->array[i] += inp_buffer->array[i];
				}
		} else if(operator_prev == '*' &&
			(operator_curr == '+' || operator_curr == '-')) {
				// Konec nasobeni- udelame posledni soucin
				// product_temp * inp_buffer -> product_buffer
				// a master += product_buffer.
				if(master->rows == -1 && master->cols == -1) {
					// HACK - pokud vstup zacina nasobenim, prizpusobime
					// rozmery mastera vyslednemu soucinu, aby nasledujici
					// podminka fungovala.
					resize_matrix(master, product_temp->rows, inp_buffer->cols);
				}
				if(!matrix_product(product_buffer, product_temp, inp_buffer)
					|| master->rows != product_buffer->rows
					|| master->cols != product_buffer->cols)
					ERROR_100();
				for(int i = 0; i < master->rows * master->cols; ++i) {
					master->array[i] += product_buffer->array[i];
				}
		} else if(operator_prev == '*' && operator_curr == '*') {
			if(!matrix_product(product_buffer, product_temp, inp_buffer))
				ERROR_100();
			matrix_t* temp = product_buffer;
			product_buffer = product_temp;
			product_temp = temp;
		} else if((operator_prev == '+' || operator_prev == '-')
			&& operator_curr == '*') {
				if(operator_prev == '-')
					negate_matrix(inp_buffer);
				// Prohodime ukazatele inp_buffer a product_temp, aby
				// product_temp ukazoval na prvni cinitel soucinu.
				matrix_t* temp = inp_buffer;
				inp_buffer = product_temp;
				product_temp = temp;
		} else {
			if(operator_prev == '\0') {
				matrix_t* temp;
				switch (operator_curr) {
					case '+':
					case '-':
						temp = inp_buffer;
						inp_buffer = master;
						master = temp;
						break;
					case '*':
						temp = product_temp;
						product_temp = inp_buffer;
						inp_buffer = temp;
						master->rows = master->cols = -1;
						break;
					default:
						break;
				}
			}
		}

		if(last_iteration)
			break;

		if(!load_matrix_stdin(inp_buffer))
			ERROR_100();

		operator_prev = operator_curr;
		if(scanf(" %c", &operator_curr) != 1) {
			operator_curr = '+';
			last_iteration = true;
		}
	}

	// Vypsat vysledek:
	matrix_dump(master);

	return 0;
}

matrix_t* create_matrix(long rows, long cols) {
	matrix_t* new_m = malloc(sizeof(matrix_t));
	new_m->rows = rows;
	new_m->cols = cols;
	new_m->array = calloc(new_m->rows * new_m->cols, sizeof(long));
	return new_m;
}

void free_matrix(matrix_t* matrix) {
	if(matrix == NULL)
		return;
	free(matrix->array);
	free(matrix);
}

void resize_matrix(matrix_t* matrix, long rows_new, long cols_new) {
	matrix->rows = rows_new;
	matrix->cols = cols_new;
	matrix->array = realloc(matrix->array, sizeof(long) * matrix->rows * matrix->cols);
	memset(matrix->array, 0, matrix->rows * matrix->cols * sizeof(long));
}

long matrix_getval(matrix_t* matrix, long row, long col) {
	return matrix->array[(row * matrix->cols) + col];
}

void matrix_setval(matrix_t* matrix, long row, long col, long val) {
	matrix->array[(row * matrix->cols) + col] = val;
}

bool matrix_product(matrix_t* result, matrix_t* left, matrix_t* right) {
	if(left->cols != right->rows || result == NULL)
		return false;

	resize_matrix(result, left->rows, right->cols);
	long temp;
	for(int i = 0; i < result->rows; ++i) {
		for(int j = 0; j < result->cols; ++j) {
			temp = 0;
			for(int k = 0; k < left->cols; ++k) {
				temp += matrix_getval(left, i, k) * matrix_getval(right, k, j);
			}
			matrix_setval(result, i, j, temp);
		}
	}
	return true;
}

void matrix_dump(matrix_t* matrix) {
	printf("%ld %ld\n", matrix->rows, matrix->cols);
	for(int i = 0; i < matrix->rows; ++i) {
		printf("%ld", matrix_getval(matrix, i, 0));
		for(int j = 1; j < matrix->cols; ++j) {
			printf(" %ld", matrix_getval(matrix, i, j));
		}
		printf("\n");
	}
}

bool load_matrix_stdin(matrix_t* matrix) {
	long rows, cols;
	if(scanf("%ld %ld", &rows, &cols) != 2)
		return false;
	resize_matrix(matrix, rows, cols);
	long inp_val;
	for(int i = 0; i < matrix->rows * matrix->cols; ++i) {
		if(scanf("%ld", &inp_val) != 1) {
			return false;
		}
		matrix->array[i] = inp_val;
	}
	return true;
}

void negate_matrix(matrix_t* matrix) {
	for(int i = 0; i < matrix->rows * matrix->cols; ++i) {
		matrix->array[i] *= -1;
	}
}
