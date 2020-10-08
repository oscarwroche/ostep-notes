#include <stdlib.h>
#include <stdio.h>

int main() {
	int *x = malloc(10 * sizeof(int));
	printf("%d\n", sizeof(x));
	return 0;
}
