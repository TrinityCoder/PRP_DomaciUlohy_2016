#include "lock.h"

#include <string.h>

bool unlock(char *password) {
	return strcmp(password, "superh") == 0;
}
