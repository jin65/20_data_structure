#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
typedef struct element{
	int key;
}element;

void quickSort(element a[], int left, int right);

int main() {
	element list[100];
	element dataNum;
	FILE *fp = fopen("input2.txt", "r");
	fscanf(fp, "%d", &dataNum.key);
	for (int i = 1; i <= dataNum.key; i++) {
		fscanf(fp, "%d", &list[i].key);
	}
	quickSort(list, 1, dataNum.key);
	for (int i = 1; i <= dataNum.key; i++)
		printf("%3d", list[i].key);

	return 0;
}
void quickSort(element a[], int left, int right) {
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left, j = right + 1;
		pivot = a[left].key;
		do {
			do i++; while (a[i].key < pivot);
			do j--; while (a[j].key > pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		quickSort(a, left, j - 1);
		quickSort(a, j + 1, right);
	}
}