#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct element {
	int key;
}element;

void insertionSort(element a[], int n);
void insert(element e, element a[], int n);
int main() {
	element a[100];
	for (int i = 1; i <= 20; i++)
		a[i].key = rand() % 100;
	for (int i = 1; i <= 20; i++)
		printf("%3d", a[i].key);
	printf("\n");
	
	insertionSort(a, 20);

	for (int i = 1; i <= 20; i++)
		printf("%3d", a[i].key);
}
void insertionSort(element a[], int n) {
	int i;
	for (i = 2; i <= n; i++) {
		element key = a[i];
		insert(key, a, i - 1);//i번째보다 앞에있는 a[]의 값들을 갖고와서 비교 후 정렬시킨다.
	}
}
void insert(element e, element a[], int i) {
	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i+1] = e;//e를 삽입할 자리를 만들어줘야 되니까 i+1로 자리를 옮기다가 e.key가 a[i].key 이상이면 이제 e를 삽입해야 함.
}