#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
typedef struct {
	int key;
}element;

void merge(element initList[], element mergedList[], int i, int m, int n);
void mergePass(element initList[], element mergedList[], int n, int s);
void mergeSort(element a[], int n);
void printList(element a[], int n);

int main() {
	int num;
	FILE*fp;
	element initList[MAX_SIZE];
	fopen_s(&fp, "input_1.txt", "r");
	fscanf_s(fp, "%d", &num);
	for (int i = 1; i <= num; i++)
		fscanf_s(fp, "%d", &initList[i].key);
	printf("input List\n");
	printList(initList, num);

	printf("executing itterative merge sort\n");
	mergeSort(initList, num);
	
	printf("sorted List\n");
	printList(initList, num);
}
void merge(element initList[], element mergedList[], int i, int m, int n) {
	int j = m + 1;
	int k = i;
	int t;
	while (j <= n && i <= m) {
		if (initList[i].key <= initList[j].key)
			mergedList[k++] = initList[i++];
		else
			mergedList[k++] = initList[j++];
	}
	if (i > m)
		for (t = j; t <= n; t++)
			mergedList[t] = initList[t];
	else
		for (t = i; t <= m; t++)
			mergedList[k+t-i] = initList[t];
}
void mergePass(element initList[], element mergedList[], int n, int s) {
	int i, j;
	for (i = 1; i <= n - 2 * s + 1; i+=2*s)
		merge(initList, mergedList, i, i + s - 1, i + 2 * s - 1);
	if (i + s - 1 < n)
		merge(initList, mergedList, i, i + s - 1, n);
	else
		for (i; i <= n; i++)
			mergedList[i] = initList[i];
}
void mergeSort(element a[], int n) {
	int s = 1;
	element extra[MAX_SIZE];
	while (s < n) {
		mergePass(a, extra, n, s);
		printf("segment size : %d\n", s);
		printf("           a : "); printList(a, n);
		printf("       extra : "); printList(extra, n);
		s *= 2;
		mergePass(extra, a, n, s);
		printf("segment size : %3d\n", s);
		printf("       extra : "); printList(extra, n);
		printf("           a : "); printList(a, n);
		s *= 2;
	}
}
void printList(element a[], int n) {
	for (int i = 1; i <= n; i++)
		printf("%3d", a[i].key);
	printf("\n");
}