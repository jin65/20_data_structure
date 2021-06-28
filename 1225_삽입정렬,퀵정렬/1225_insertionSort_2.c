#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct element{
	int key;
	char name[20];
	int grade;
}element;

void insertionSort(element list[], int n);
void insert(element e, element list[], int i);
void fileOut(char filename[], element list[], int n);

int main() {
	element list[30];
	int dataNum;
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &dataNum);
	for (int i = 1; i <= dataNum; i++) {
		fscanf(fp, "%d%s%d", &list[i].key, list[i].name, &list[i].grade);
	}
	insertionSort(list, dataNum);

	for (int i = 1; i <= dataNum; i++)
		printf("(%d%7s%3d)\n", list[i].key, list[i].name, list[i].grade);

	fileOut("output.txt", list, dataNum);
}
void insertionSort(element list[], int n) {
	for (int i = 2; i <= n; i++) {
		element key = list[i];
		insert(key, list, i - 1);
	}
}
void insert(element e, element list[], int i) {
	list[0] = e;
	while (e.key < list[i].key) {
		list[i + 1] = list[i];
		i--;
	}
	list[i + 1] = e;
}
void fileOut(char filename[], element list[], int n) {
	FILE *fp = fopen(filename, "w");
	for (int i = 1; i <= n; i++)
		fprintf(fp, "(%d%7s%3d)\n", list[i].key, list[i].name, list[i].grade);
	fclose(fp);
}