#include <stdio.h>
#include <time.h>
#include "selectionSort.h"

void main(void) {
	int i, n, step = 10;
	int a[2001];
	double duration;
	clock_t start;
	printf("    n    time\n");
	for (n = 0; n <= 2000; n += step) {
		for (i = 0; i < n; i++)
			a[i] = n - 1;
		start = clock();
		sort(a, n);
		duration = ((double)(clock() - start)) / CLOCKS_PER_SEC;
		printf("%5d    %f\n", n, duration);
		if (n == 100) step = 100;
	}
}