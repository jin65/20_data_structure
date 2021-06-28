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
	for (i = n / 2; i > 0; i--)//���� �� ����Ʈ������ ��Ʈ�� �ö󰡸鼭 Ȯ��, initial heap ����
		adjust(a, i, n);
	printf("\nafter initialization of max heap\n");
	printList(a, n);
	for (i = n - 1; i > 0; i--){//���� ũ�� ���
		SWAP(a[1],a[i + 1], temp);//���� ������ ��Ʈ�� ���� ����� ��ü
		adjust(a, 1, i);//�ٽ� ���� ������
		printList(a, n);
	}//��ȯ,����ũ�� ���,���� ������
	//��ƮŰ�� ���� ���������� ���� ū ���̴ϱ� �̰� ������ ���� ������ ������ ���ؼ� ������ ������ ��ü�ϴ°�
	//��ü�ؼ� adjust�� ���� �������� ������ ��ü�Ѱ��� ������ �Ϸ��
	//�״����� �̹� ��ȯ�ؼ� ������ ���� ���ʿ䰡 �����ϱ� ���� ũ�⸦ 1��ҽ��Ѽ� �ٽ� �� ���� �ݺ�
}
void printList(element a[], int n) {
	for (int i = 1; i <= n; i++)
		printf("%3d", a[i].key);
	printf("\n");
}