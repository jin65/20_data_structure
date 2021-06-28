#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define INF_NUM 100000

int initWinner(int cur, int k, int winTree[]);
void adjustWinner(int min, int k, int winTree[]);

int nums[MAX_SIZE + 1][11] = { 0 };
int winTree[2 * MAX_SIZE] = { NULL };
int sorted[MAX_SIZE * 10 + 1] = { 0 };
int sortedIdx[MAX_SIZE + 1] = { 0 };

int main() {
	int k, seed, cur, min;
	printf("<<sorting with winner tree>>\n");
	printf("the number of keys(8,16, or 32 as a power of 2)>>");
	scanf_s("%d", &k);
	printf("random numbers to use as key values(1~100)\nseed >> ");
	scanf_s("%d", &seed);
	srand(seed);
	for (int i = 1; i <= k; i++) {
		printf("%dth records\n", i);
		nums[i][1] = rand() % MAX_SIZE + 1;
		for (int j = 2; j <= 10; j++)
			nums[i][j] = nums[i][j - 1] + 1;
		for (int k = 1; k <= 10; k++)
			printf("%d ", nums[i][k]);
		printf("\n");
	}

	printf("initialization of min-winner tree\n");
	for (int idx = k, i = 1; i <= k; i++, idx++)
		winTree[idx] = i;
	for (int i = 1; i <= k; i++)
		sortedIdx[i] = 1;
	initWinner(1, k, winTree);

	printf("sorting the min-winner tree...\n\n");
	for (int i = 1; i <= k*10; i++) {
		int min = winTree[1];
		sorted[i] = nums[min][sortedIdx[min]];
		sortedIdx[min]++;
		if (sortedIdx[min] > 10) {//���ڵ� ���� ������
			sortedIdx[min]--;
			nums[min][sortedIdx[min]] = INF_NUM;//�ſ� ū ���ڷ� ġȯ������>>���ڵ� ���� ���� ǥ��
		}
		adjustWinner(min, k, winTree);
	}
	printf("\nsorted result\n");
	for (int i = 1; i <= k*10; i++) {
		printf("%3d", sorted[i]);
		if (i%k == 0)
			printf("\n");
	}


}
int initWinner(int cur, int k, int winTree[]) {//cur>>���� ����Ű���ε���
	int leftWinner, rightWinner;
	int leftChild = cur * 2;
	int rightChild = cur * 2 + 1;
	if (leftChild >= k * 2)//�ε����� Ʈ���� ���� �Ѿ����
		return winTree[cur];
	leftWinner = initWinner(leftChild, k, winTree);//left�� �� ������
	rightWinner = initWinner(rightChild, k, winTree);//right�� �� ������
	//���������� ���� ã�´�
	if (nums[leftWinner][sortedIdx[leftWinner]] < nums[rightWinner][sortedIdx[rightWinner]])
		winTree[cur] = winTree[leftChild];
	else
		winTree[cur] = winTree[rightChild];
	return winTree[cur];
}
void adjustWinner(int min, int k, int winTree[]) {
	int index;//ġȯ�� Ű>>���ڵ��� ���� ������ ġȯ�� Ű
	index = k + min - 1;
	int parent = index / 2;
	int sibling;
	while (parent >= 1) {
		if ((index % 2) == 0)
			sibling = parent * 2 + 1;
		else
			sibling = parent * 2;
		if (nums[winTree[sibling]][sortedIdx[winTree[sibling]]] < nums[winTree[index]][sortedIdx[winTree[index]]])
			//���� ��尡 ������ sibling �¸�
			winTree[parent] = winTree[sibling];
		else
			winTree[parent] = winTree[index];
		parent = parent / 2;
		index = index / 2;//�� ������ �ö󰡾���
	}
}