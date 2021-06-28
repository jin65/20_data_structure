#include <stdio.h>
#include <stdlib.h>
#define MAX_ELEMENTS 200
#define HEAP_FULL(n) (n==MAX_ELEMENTS-1)
#define HEAP_EMPTY(n) (!n)
typedef struct {
	int key;
}element;

void push(element item, int *n);
element pop(int *n);

element heap[MAX_ELEMENTS];
int n = 0;

int main() {
	element item;
	FILE *fp;
	printf("*****insertion into a max heap*****\n");
	fopen_s(&fp, "input.txt", "r");
	while (!feof(fp)) {
		fscanf_s(fp, "%d", &item.key);
		push(item, &n);
		for (int i = 1; i <= n; i++)
			printf("%3d", heap[i].key);
		printf("\n");
	}
}
void push(element item, int *n) {
	int i;
	if (HEAP_FULL(*n)) {
		fprintf(stderr, "heap full\n");
		exit(EXIT_FAILURE);
	}
	i = ++(*n);//힙 제일끝에 추가해야되니까 i=++(*n)하면 현재 끝 노드 뒤에 추가할 위치 인덱스 
	while ((i != 1) && (item.key > heap[i / 2].key)) {//i가 루트까지&&삽입할 아이템키가 기존 노드키보다 클떄까지
													  //>>루트따라 올라가면서 크기체크
		heap[i] = heap[i / 2];
		i /= 2;
	}
	heap[i] = item;
}
element pop(int *n) {
	int parent, child;
	element item, temp;
	if (HEAP_EMPTY(*n)) {
		fprintf(stderr, "heap empty\n");
		exit(EXIT_FAILURE);
	}
	item = heap[1];//루트노드를 따로 저장
	temp = heap[(*n)--];//가장 끝 노드 따로 저장
	parent = 1;//루트에서 시작한다.
	child = 2;//루트의 왼쪽차일드-2
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))//만약에 왼쪽차일드가 오른쪽 차일드보다 작으면
			child++;//차일드를 오른쪽차일드로 변경
		if (temp.key >= heap[child].key) break;//만약에 temp-가장 끝노드(루트로 위치조정후 힙재조정해야되는)가 차일드 이상이라면
											   //
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}