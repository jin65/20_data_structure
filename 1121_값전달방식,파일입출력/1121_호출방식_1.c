#include <stdio.h>

void swap1(int, int);
void swap2(int*, int*);
void swap3(int**, int**);
int main() {
	int a, b;
	int *pa = &a;
	int **ppa = &pa;
	int *pb = &b;
	int** ppb = &pb;

	a = 1; b = 2; swap1(a, b);//call by value;
	printf("After calling swap1(a,b), a: %d, b: %d\n", a, b);
	
	a = 1; b = 2; swap2(&a, &b);//call by addressvalue;
	printf("After calling swap2(a,b), a: %d, b: %d\n", a, b);
	
	a = 1; b = 2; swap2(pa, pb);//call by addressvalue;
	printf("After calling swap2(a,b), a: %d, b: %d\n", a, b);
	
	a = 1; b = 2; swap3(&pa, &pb);//call by addressvalue;
	printf("After calling swap3(a,b), a: %d, b: %d\n", a, b);
	
	a = 1; b = 2; swap3(ppa, ppb);//call by addressvalue;
	printf("After calling swap3(a,b), a: %d, b: %d\n", a, b);

}
void swap1(int a, int b) {
	int t;
	t = a;
	a = b;
	b = t;
}
void swap2(int* a, int* b) {
	int t;
	t = *a;
	*a = *b;
	*b = t;
}
void swap3(int** a, int** b) {
	int t;
	t = **a;
	**a = **b;
	**b = t;
}