//modification of 1217_maxHeap.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int key;
}element;

void printHeap(int n);
void push(element item, int *n);
element pop(int *n);

element heap[MAX_ELEMENTS];
int n = 0;

int main() {
	element item;
	FILE *fp = fopen("input2.txt", "r");
	printf("insertion into a min heap\n");
	while (!feof(fp)) {
		fscanf(fp, "%d", &item.key);
		push(item, &n);
		printHeap(n);
	}
	printf("\ndeletion from a min heap\n");
	while (!HEAP_FULL(n)) {
		item = pop(&n);
		//printf("deleted item : %d\n", item.key);
		printHeap(n);
	}
}
void printHeap(int n) {
	int i = 1;
	while (i <= n) {
		printf("%3d", heap[i].key);
		i++;
	}
	printf("\n");
}
void push(element item, int *n) {//���� ���������� n, item�� ������ ����
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "heap is full.");
		exit(EXIT_FAILURE);//���⼭ ����ó���� �����ʰ� ��������� �����Ҽ��� �ִ�.(�����Ҵ�迭 ���)
	}
	i = ++(*n);//i�� n+1�� �ȴ�. ���� ������ element��(n)���� �ϳ� �����Ϸ��� n+1���� ������Ѿ� ��.
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];//���� �θ��� ���� �ڽĳ�� ������ ��ġ����
		i /= 2;//i�� ��� �θ��� �θ�....�̷������� �ε��� ����
	}
	heap[i] = item;//while�� Ż��� heap[i]�� ���� item�� ���Ե� ��ġ
}
element pop(int *n) {
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "heap is empty");
		exit(EXIT_FAILURE);
	}
	item = heap[1];
	temp = heap[(*n)--];
	parent = 1;
	child = 2;
	while (child <= (*n)) {
		if ((child < *n) && (heap[child].key > heap[child + 1].key))
			child++;
		if (temp.key <= heap[child].key) break;
		heap[parent] = heap[child];
		parent = child;
		child = parent * 2;//����� parent�� �ڽĳ��
	}
	heap[parent] = temp;//������ �� ������ ����� ��ġ�� ������
	return item;
}//heap�� �������� ����Ǿ� ����