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
void push(element item, int *n) {//현재 히프사이즈 n, item을 히프에 삽입
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "heap is full.");
		exit(EXIT_FAILURE);//여기서 에러처리를 하지않고 히프사이즈를 더블링할수도 있다.(동적할당배열 사용)
	}
	i = ++(*n);//i는 n+1이 된다. 현재 히프의 element수(n)에서 하나 삽입하려면 n+1으로 변경시켜야 함.
	while ((i != 1) && (item.key < heap[i / 2].key)) {
		heap[i] = heap[i / 2];//현재 부모노드 값을 자식노드 값으로 위치변경
		i /= 2;//i는 계속 부모의 부모....이런식으로 인덱스 따라감
	}
	heap[i] = item;//while문 탈출시 heap[i]가 현재 item이 삽입될 위치
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
		child = parent * 2;//변경된 parent의 자식노드
	}
	heap[parent] = temp;//삭제한 후 가져온 노드의 위치가 정해짐
	return item;
}//heap는 전역으로 선언되어 있음