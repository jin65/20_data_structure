#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENT_SIZE 100
#define SWAP(x,y,t) (((t)=(x)),((x)=(y)),((y)=(t)))

typedef struct {
	int key;
}element;

void quickSort(element a[], int left, int right);
void printList(element a[], int num);

int num;
int count;
element list[MAX_ELEMENT_SIZE];
int main() {
	FILE *fp;
	fopen_s(&fp, "input_2.txt", "r");
	fscanf_s(fp, "%d", &num);
	printf("input list\n");
	for (int i = 1; i <= num; i++) {
		fscanf_s(fp, "%d", &list[i].key);
		printf("%3d", list[i].key);
	}
	printf("\nexecution of quick sort...\n");
	quickSort(list, 1, num);
	printf("call quicksort: %d\n", count);
	printf("\nsorted list\n");
	printList(list, num);
}
void quickSort(element a[], int left, int right) {
	count++;
	int pivot, i, j;
	element temp;
	if (left < right) {
		i = left, j = right+1;
		pivot = a[left].key;
		printList(list, num);
		do {
			do i++; while (a[i].key < pivot);
			do j--; while (a[j].key>pivot);
			if (i < j) SWAP(a[i], a[j], temp);
		} while (i < j);
		SWAP(a[left], a[j], temp);
		//printList(a, num);
		quickSort(a, left, j - 1);//j-1가 새로운 right가 된다
		quickSort(a, j + 1, right);//j+1가 새로운 left가 된다`
	}
}
void printList(element a[], int num) {
	for (int i = 1; i <= num; i++)
		printf("%3d%s", a[i].key, (i!=num)?" ":"\n");
	printf("\n");
}