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
		insert(key, a, i - 1);//i��°���� �տ��ִ� a[]�� ������ ����ͼ� �� �� ���Ľ�Ų��.
	}
}
void insert(element e, element a[], int i) {
	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i+1] = e;//e�� ������ �ڸ��� �������� �Ǵϱ� i+1�� �ڸ��� �ű�ٰ� e.key�� a[i].key �̻��̸� ���� e�� �����ؾ� ��.
}