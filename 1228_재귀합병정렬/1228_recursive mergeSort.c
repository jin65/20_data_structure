#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_SIZE 100
typedef struct element {
	int key;
}element;

int rmergeSort(element a[], int link[], int left, int right, int dataNum);
int listMerge(element a[], int link[], int start1, int start2, int dataNum);
void listPrint(element a[], int link[], int dataNum);

int main() {
	int dataNum, start;
	element a[MAX_SIZE];
	int link[MAX_SIZE] = {0};
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &dataNum);
	for (int i = 1; i <= dataNum; i++) {
		fscanf(fp, "%d", &a[i].key);
	}
	//
	listPrint(a, link, dataNum);
	//

	start=rmergeSort(a, link, 1, dataNum, dataNum);

	//
	printf("<<Sorted List>>\n");
	while(start!=NULL){
		printf("%d ", a[start].key);
		start = link[start];
	}
	//
}
int rmergeSort(element a[], int link[], int left, int right, int dataNum) {
	printf("rmergeSort<a, link, %d, %d>\n", left, right);
	if (left >= right) return left;
	int mid = (left + right) / 2;
	return listMerge(a, link, rmergeSort(a, link, left, mid, dataNum), rmergeSort(a, link, mid+1, right, dataNum), dataNum);
}
int listMerge(element a[], int link[], int start1, int start2, int dataNum) {
	int last1, last2, lastResult;
	last1 = start1;
	last2 = start2;
	lastResult = 0;
	for (; last1&&last2;) {
		if (a[last1].key > a[last2].key) {
			link[lastResult] = last2;
			lastResult = last2;
			last2 = link[last2];
		}
		else {
			link[lastResult] = last1;
			lastResult = last1;
			last1 = link[last1];
		}
	}
	if (last1 == 0) link[lastResult] = last2;
	else link[lastResult] = last1;
	printf("listMerged<a, link, %d, %d>\n", start1, start2);
	listPrint(a, link, dataNum);
	return link[0];
}
void listPrint(element a[], int link[], int dataNum) {
	printf("       ");
	for (int i = 0; i <= dataNum; i++) {
		printf("[%2d]", i);
	}
	printf("\n");
	printf("%5s:", "link");
	for (int i = 0; i <= dataNum; i++) {
		printf("%4d", link[i]);
	}
	printf("\n");
	printf("%5c:", 'a');
	printf("%4c", '-');
	for (int i = 1; i <= dataNum; i++) {
		printf("%4d", a[i].key);
	}
	printf("\n");
}