#define _CRT_SECURE_NO_WARNINGS
#define MAX_SIZE 100
#include <stdio.h>
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))
typedef struct element {
	int key;
}element;

void adjust(element a[], int root, int n);
void heapSort(element a[], int n);
void printList(element a[], int n);
int main() {
	int dataNum;
	element a[MAX_SIZE];
	FILE *fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &dataNum);
	for (int i = 1; i <= dataNum; i++)
		fscanf(fp, "%d", &a[i].key);
	printf("<Current List>\n");
	for (int i = 1; i <= dataNum; i++)
		printf("%3d", a[i].key);
	printf("\n");
	heapSort(a, dataNum);
	printf("<Sorted List>\n");
	for (int i = 1; i <= dataNum; i++)
		printf("%3d", a[i].key);
	printf("\n");
}
void adjust(element a[], int root, int n) {
	int child, rootkey;
	element temp;
	temp = a[root];
	rootkey = temp.key;
	child = 2 * root;
	while (child <= n) {
		if (child < n&&a[child].key < a[child + 1].key)
			child++;
		if (rootkey <= a[child].key) {
			a[child / 2] = a[child];
			child *= 2;
		}
		else
			break;
	}
	a[child / 2] = temp;
}
void heapSort(element a[], int n) {
	int i, j;
	element temp;
	for (i = n / 2; i > 0; i--)//제일 밑 서브트리부터 루트로 올라가면서 확인, initial heap 생성
		adjust(a, i, n);
	printf("\nafter initialization of max heap\n");
	printList(a, n);
	for (i = n - 1; i > 0; i--){//히프 크기 축소
		SWAP(a[1],a[i + 1], temp);//현재 히프의 루트와 제일 끝노드 교체
		adjust(a, 1, i);//다시 히프 재조정
		printList(a, n);
	}//교환,히프크기 축소,히프 재조정
	//루트키가 현재 히프에서는 제일 큰 값이니까 이걸 히프의 제일 끝으로 보내기 위해서 히프의 끝노드와 교체하는것
	//교체해서 adjust로 히프 재조정을 했으면 교체한값은 정렬이 완료됨
	//그다음은 이미 교환해서 정렬한 값은 할필요가 없으니까 히프 크기를 1축소시켜서 다시 위 과정 반복
}
void printList(element a[], int n) {
	for (int i = 1; i <= n; i++)
		printf("%3d", a[i].key);
	printf("\n");
}