#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT_SIZE 100
typedef struct {
	int key;
	char name[20];
	int grade;
}element;

void insert(element e, element a[], int i);
void insertionSort(element a[], int n);

element list[MAX_ELEMENT_SIZE];
int main() {
	int num;
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	fscanf_s(fp, "%d", &num);
	printf("<<input list>>\n");
	for (int i = 1; i <= num; i++) {
		fscanf_s(fp, "%d%s%d", &list[i].key, list[i].name, sizeof(list[i].name),&list[i].grade);
		printf("<%2d,%2s,%2d>\n", list[i].key, list[i].name, list[i].grade);
	}
	insertionSort(list, num);
	printf("\n<<sorted list>>\n");
	for (int i = 1; i <= num; i++)
		printf("<%2d,%2s,%2d>\n", list[i].key, list[i].name, list[i].grade);
}
void insert(element e, element a[], int i) {//i::element 들어가있는 끝의 인덱스
	a[0] = e;
	while (e.key < a[i].key) {
		a[i + 1] = a[i];
		i--;
	}
	a[i + 1] = e;
}
void insertionSort(element a[], int n) {
	int j;
	for (j = 2; j <= n; j++) {//n-1번
		element temp = a[j];
		insert(temp, a, j - 1);
	}
}