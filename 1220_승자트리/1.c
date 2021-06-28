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
		if (sortedIdx[min] > 10) {//레코드 정렬 끝났음
			sortedIdx[min]--;
			nums[min][sortedIdx[min]] = INF_NUM;//매우 큰 숫자로 치환시켜줌>>레코드 정렬 끝남 표시
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
int initWinner(int cur, int k, int winTree[]) {//cur>>현재 가리키는인덱스
	int leftWinner, rightWinner;
	int leftChild = cur * 2;
	int rightChild = cur * 2 + 1;
	if (leftChild >= k * 2)//인덱스가 트리의 끝을 넘어버림
		return winTree[cur];
	leftWinner = initWinner(leftChild, k, winTree);//left로 쭉 내려감
	rightWinner = initWinner(rightChild, k, winTree);//right로 쭉 내려감
	//리프노드까지 끝을 찾는다
	if (nums[leftWinner][sortedIdx[leftWinner]] < nums[rightWinner][sortedIdx[rightWinner]])
		winTree[cur] = winTree[leftChild];
	else
		winTree[cur] = winTree[rightChild];
	return winTree[cur];
}
void adjustWinner(int min, int k, int winTree[]) {
	int index;//치환된 키>>레코드의 다음 값으로 치환된 키
	index = k + min - 1;
	int parent = index / 2;
	int sibling;
	while (parent >= 1) {
		if ((index % 2) == 0)
			sibling = parent * 2 + 1;
		else
			sibling = parent * 2;
		if (nums[winTree[sibling]][sortedIdx[winTree[sibling]]] < nums[winTree[index]][sortedIdx[winTree[index]]])
			//형제 노드가 작으면 sibling 승리
			winTree[parent] = winTree[sibling];
		else
			winTree[parent] = winTree[index];
		parent = parent / 2;
		index = index / 2;//위 레벨로 올라가야함
	}
}