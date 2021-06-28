#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(a,b) ((a>b)?1:((a==b)? 0:-1))
#define MAX_TERMS 100

typedef struct {
	float coef;
	int expon;
}term;

void padd(int startA, int finishA, int startB, int finishB,
	int* startD, int* finishD);
void attach(float coef, int expon);
void printTerm(term terms[MAX_TERMS], int start, int finish);

term terms[MAX_TERMS];
int avail = 0;

int main() {
	int aNum, bNum;
	int startA, finishA, startB, finishB, startD, finishD;
	printf("two input polynomials...\n");
	FILE* fpa = fopen("input.txt", "r");
	fscanf(fpa, "%d", &aNum);
	fscanf(fpa, "%d", &bNum);
	for (int i = 0; i < aNum + bNum; i++)
		fscanf(fpa, "%f %d", &terms[i].coef, &terms[i].expon);

	startA = 0;
	finishA = aNum-1;
	startB = aNum;
	finishB = aNum + bNum - 1;
	avail = finishB + 1;
	printf("A(x) : ");
	printTerm(terms, startA, finishA);
	printf("B(x) : ");
	printTerm(terms, startB, finishB);
	padd(startA, finishA, startB, finishB, &startD, &finishD);
	printf("\nThe result of polynomial addition...\n");
	printf("D(x)=A(x)+B(x) =\n");
	printTerm(terms, startD, finishD);
}
void padd(int startA, int finishA, int startB, int finishB, 
	int*startD, int*finishD) 
{
	float coefficient;
	*startD = avail;
	while (startA <= finishA && startB <= finishB) {
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
		case 0:
			coefficient = terms[startA].coef + terms[startB].coef;
			if (coefficient != 0)
				attach(coefficient, terms[startA].expon);
			startA++;
			startB++;
			break;
		case -1:
			attach(terms[startB].coef, terms[startB].expon);
			startB++;
			break;
		case 1:
			attach(terms[startA].coef, terms[startA].expon);
			startA++;
			break;
		}
	}
	//만약에 한쪽 다항식이 먼저 끝난다면?
	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].expon);
	for (; startB <= finishB; startB++)
		attach(terms[startB].coef, terms[startB].expon);
	*finishD = avail - 1;
}
void attach(float coef, int expon) {
	if (avail > MAX_TERMS) {
		fprintf(stderr, "too many terms in polynomial");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coef;
	terms[avail++].expon = expon;
}
void printTerm(term terms[MAX_TERMS], int start, int finish) {
	for (start; start <= finish; start++) {
		if (terms[start].expon == 0)
			printf("%.1f", terms[start].coef);
		else
			printf("%.1fx^%d + ", terms[start].coef, terms[start].expon);
	}
	printf("\n");
}