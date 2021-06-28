//승자트리를 이용한 merge Sorting
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_SIZE 100
#define INF_NUM 10000
#define MALLOC(p, s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory allocation");\
		exit(EXIT_FAILURE);\
	}\
}
int initWinner(int cur, int k, int winTree[]);
void adjustWinner(int min, int k, int winTree[]);

int nums[MAX_SIZE + 1][11] = { 0 };
int winTree[2 * MAX_SIZE] = { NULL };//최소값을 가지는 런이 몇번째 런인지 트리로 확인
int sorted[MAX_SIZE * 10 + 1] = { 0 };
int sortedIdx[MAX_SIZE + 1] = { 0 };
int main() {
	int seed, k;
	int i, j;
	printf("input seed : "); scanf("%d", &seed);
	printf("input k : "); scanf("%d", &k);
	srand(seed);
	for (i = 1; i <= k; i++) {
		printf("%dth record\n", i);
		nums[i][1] = rand() % 100 + 1;
		for (j = 2; j <= 10; j++)
			nums[i][j] = nums[i][j - 1] + 1;
		for(int k=1; k<=10;k++)
			printf("%4d", nums[i][k]);
		printf("\n");
	}//record values

	for (i = 1; i <= k; i++)
		sortedIdx[i] = 1;
	for (i = k, j = 1; j <= k; i++, j++)
		winTree[i] = j;
	initWinner(1, k, winTree);//initialize winnertree

	for (i = 1; i <= k*10; i++) {
		int min = winTree[1];//트리의 루트가 최소값을 가지는 런
		sorted[i] = nums[min][sortedIdx[min]];//sorted에는 해당 런마다 각각 어떤 인덱스가 최소값인지 나타내고있음
		sortedIdx[min]++;
		if (sortedIdx[min] > 10) {
			sortedIdx[min]--;
			nums[min][sortedIdx[min]] = INF_NUM;
		}
		adjustWinner(min, k, winTree);
	}
	printf("\nsorted results\n");
	for (i = 1; i <= k*10; i++) {
		printf("%3d", sorted[i]);
		if (i%k == 0)
			printf("\n");
	}

	return 0;
}
int initWinner(int cur, int k, int winTree[]) {
	int leftWinner, rightWinner;
	int leftChild = cur * 2;
	int rightChild = cur * 2 + 1;
	if (leftChild >= k * 2)
		return winTree[cur];
	leftWinner = initWinner(leftChild, k, winTree);
	rightWinner = initWinner(rightChild, k, winTree);
	if (nums[leftWinner][sortedIdx[leftWinner]] < nums[rightWinner][sortedIdx[rightWinner]])
		winTree[cur] = winTree[leftChild];
	else
		winTree[cur] = winTree[rightChild];
	return winTree[cur];
}
//int initwinner(int cur, int k, int winTree[]) {
//	//
//	int leftWintree, rightWintree;
//	int leftChild = cur * 2;
//	int rightChild = cur * 2 + 1;
//	if (leftChild >= 2 * k)
//		return winTree[cur];
//	leftWintree = initWinner(leftChild, k, winTree);
//	rightWintree = initWinner(rightChild, k, winTree);
//	if (nums[leftWintree][sorted[leftWintree]] > nums[rightWintree][sorted[rightWintree]])
//		winTree[cur] = winTree[rightChild];
//	else
//		winTree[cur] = winTree[leftChild];
//	return winTree[cur];
//	/*for (int i = k; i < 2 * k - 1; i++) {
//		winTree[i] = i - (k - 1);
//	}
//	int temp = winTree[k + (k - 1)];
//	while (temp > 2) {
//		if (temp % 2 == 0) {
//			winTree[temp / 2] = temp;
//			temp = temp - 1;
//		}
//		if (nums[temp] > nums[temp - 1])
//			winTree[temp / 2] = temp - 1;
//		temp = temp - 2;
//	}
//	return winTree[temp];*/
//}
 void adjustWinner(int min, int k, int winTree[]) {
	 int index;//index는 최소값을 정렬하고 그다음 치환된 레코드의 값(키)
	 index = k + min - 1;//
	 int parent = index / 2;//index의 부모노드
	 int sibling;
	 while (parent >= 1) {
		 if ((index % 2) == 0)
			 sibling = parent * 2 + 1;
		 else
			 sibling = parent * 2;
		 if (nums[winTree[sibling]][sortedIdx[winTree[sibling]]] < nums[winTree[index]][sortedIdx[winTree[index]]])
			 winTree[parent] = winTree[sibling];
		 else
			 winTree[parent] = winTree[index];
		 parent = parent / 2;
		 index = index / 2;
	 }
}