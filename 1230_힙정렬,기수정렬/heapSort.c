#include <stdio.h>
#include <stdlib.h>
#define SWAP(x,y,t) (((t)=(x)),((x)=(y)),((y)=(t)))
#define MAX_SIZE 100
typedef struct {
	int key;
}element;

void heapSort(element a[], int n);
void adjust(element a[], int root, int n);
void printList(element a[], int num);

int num, count;
element list[MAX_SIZE];
int main() {
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	fscanf_s(fp, "%d", &num);
	for (int i = 1; i <= num; i++)
		fscanf_s(fp, "%d", &list[i].key);
	printf("input list\n");
	printList(list, num);
	printf("executing heapsort\n");
	heapSort(list, num);
	printf("sorted list\n");
	printList(list, num);

}
void heapSort(element a[], int n) {
	int i, j;
	element temp;
	for (i = n / 2; i > 0; i--) {
		adjust(a, i, n);
	}
	printf("after initialization of max heap\n");
	printList(a, num);
	for (i = n - 1; i > 0; i--) {
		SWAP(a[1], a[i + 1], temp);
		adjust(a, 1, i);
		count++;
		printf("step %3d:", count);
		printList(a, num);
	}
}
void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp = a[root];
	rootkey = a[root].key;
	child = 2 * root;//��Ʈ �������ϵ�
	while (child <= n) {
		if ((child < n) && (a[child].key < a[child + 1].key))//���ϵ尡 �ٸ� ���ϵ��庸�� ������ child++
			//�� �� ū child���̶� parentŰ ���ؾߵǱ⶧����
			child++;
		if (rootkey > a[child].key)
			break;
		else {//child�θ� child ����(�ڸ�ü����)
			a[child / 2] = a[child];
			child *= 2;
		}
	}
	a[child / 2] = temp;
}
void printList(element a[], int num) {
	for (int i = 1; i <= num; i++)
		printf("%3d", a[i].key);
	printf("\n");
}