#include <stdio.h>
#include <stdlib.h>
#define MAX_TERMS 100
#define COMPARE(x,y) (((x)<(y))?-1:(((x)==(y))?0:1))
typedef struct {
	float coef;
	int expon;
}poly;

void padd(int startA, int startB, int finishA, int finishB, int *startD, int *finishD);
void attach(float coefficient, int exponent);
void printPoly(int startA, int finishA);

poly terms[MAX_TERMS];
int avail = 0;

int main() {
	int termA, termB;
	int startA, startB, finishA, finishB;
	int startD=avail, finishD=avail;
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	fscanf_s(fp, "%d %d", &termA, &termB);
	
	startA = 0;
	finishA = termA - 1;
	startB = finishA + 1;
	finishB = startB + termB - 1;
	avail = finishB + 1;

	for (int i = startA; i <= finishA; i++) {
		fscanf_s(fp, "%f", &terms[i].coef);
		fscanf_s(fp, "%d", &terms[i].expon);
	}
	for (int i = startB; i <= finishB; i++) {
		fscanf_s(fp, "%f", &terms[i].coef);
		fscanf_s(fp, "%d", &terms[i].expon);
	}

	printf("two input poly\n");
	printf("A(x)=");
	printPoly(startA, finishA);
	printf("B(x)=");
	printPoly(startB, finishB);
	printf("poly addition\n");
	padd(startA, startB, finishA, finishB, &startD, &finishD);
	printf("D(x)=A(x)+B(x) =\n");
	printPoly(startD, finishD);
	
}
void printPoly(int startA, int finishA) {
	for (int i = startA; i < finishA; i++)
		printf("%.1fx^%d + ", terms[i].coef, terms[i].expon);
	printf("%.1f", terms[finishA].coef);
	printf("\n");
}
void padd(int startA, int startB, int finishA, int finishB, int *startD, int *finishD) {
	float coefficient;
	*startD = avail;//startD를 finishB 바로다음(avail)에 위치시킨다.
	while(startA<=finishA&&startB<=finishB)
		switch (COMPARE(terms[startA].expon, terms[startB].expon)) {
			//coef, expon으로 항 하나를 다항식 D에 입력>>attach 함수에서 처리
			case -1: //a x지수 < b x지수
				attach(terms[startB].coef, terms[startB].expon);
				startB++;
				break;
			case 0://a x지수 == b x지수
				coefficient = terms[startA].coef+terms[startB].coef;
				if(coefficient)//계수가 있어야 항 처리 실행
					attach(coefficient, terms[startA].expon);
				startA++;
				startB++;
				break;
			case 1:// a x지수 > b x지수
				attach(terms[startA].coef, terms[startA].expon);
				startA++;
		}
	for (; startA <= finishA; startA++)
		attach(terms[startA].coef, terms[startA].expon);
	for (; startB <= finishB; startB++)
		attach(terms[startB].coef, terms[startB].expon);
	*finishD = avail - 1;
}
void attach(float coefficient, int exponent) {//D 처리
	if (avail >= MAX_TERMS) {
		fprintf(stderr, "too many terms\n");
		exit(EXIT_FAILURE);
	}
	terms[avail].coef = coefficient;//avail 이후>>합산된 다항식 D의 영역(A~~B~~avail(D)~~)
	terms[avail++].expon = exponent;//avail(x), avail++해야함. avail의 이동 필요
}