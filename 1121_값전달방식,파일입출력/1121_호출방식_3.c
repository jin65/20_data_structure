#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
//동적할당한 포인터배열로 파일 입출력해보기
int* alloc(int num);
void input(int* pNum, int num, FILE* fpIn);
void increase(int* pNum, int num);
void output(int* pNum, int num, FILE* fpOut);

int main() {
	int num, *pNum;
	FILE* fpIn = fopen("input.txt", "r");
	FILE* fpOut = fopen("output.txt", "w");
	fscanf(fpIn, "%d", &num);
	pNum = alloc(num);
	input(pNum, num, fpIn);
	increase(pNum, num);
	output(pNum, num, fpOut);

	free(pNum);
	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
int* alloc(int num) {
	int* pNum;
	pNum = (int*)malloc(sizeof(int) * num);
	return pNum;
}
void input(int* pNum, int num, FILE* fpIn) {
	for (int i = 0; i < num; i++) {
		fscanf(fpIn, "%d", pNum+i);
	}
}
void increase(int* pNum, int num) {
	for (int i = 0; i < num; i++)
		*(pNum + i) = *pNum + 1;
}
void output(int* pNum, int num, FILE* fpOut) {
	for (int i = 0; i < num; i++)
		fprintf(fpOut, "%d ", *(pNum)+i);
}