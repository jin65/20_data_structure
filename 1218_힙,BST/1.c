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
	i = ++(*n);//�� ���ϳ��� �߰��ؾߵǴϱ� i=++(*n)�ϸ� ���� �� ��� �ڿ� �߰��� ��ġ �ε��� 
	while ((i != 1) && (item.key > heap[i / 2].key)) {//i�� ��Ʈ����&&������ ������Ű�� ���� ���Ű���� Ŭ������
													  //>>��Ʈ���� �ö󰡸鼭 ũ��üũ
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
	item = heap[1];//��Ʈ��带 ���� ����
	temp = heap[(*n)--];//���� �� ��� ���� ����
	parent = 1;//��Ʈ���� �����Ѵ�.
	child = 2;//��Ʈ�� �������ϵ�-2
	while (child <= *n) {
		if ((child < *n) && (heap[child].key < heap[child + 1].key))//���࿡ �������ϵ尡 ������ ���ϵ庸�� ������
			child++;//���ϵ带 ���������ϵ�� ����
		if (temp.key >= heap[child].key) break;//���࿡ temp-���� �����(��Ʈ�� ��ġ������ ���������ؾߵǴ�)�� ���ϵ� �̻��̶��
											   //
		heap[parent] = heap[child];
		parent = child;
		child *= 2;
	}
	heap[parent] = temp;
	return item;
}