//난수배열 생성해서 선택정렬한 후 사용자입력된 정수 이진탐색
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SWAP(x,y,t) (((t)=(y)),((y)=(x)),((x)=(t)))
#define COMPARE(a,b) ((a>b)?1:((a==b)?0:-1))
int main() {
	int n, integer;
	int min = 0, temp = 0;
	int left, right, middle;
	int arr[101];

	scanf("%d", &n);
	srand((unsigned)time(NULL));
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % 1000;
	}

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	for (int i = 0; i < n - 1; i++) {
		min = i;
		for (int j = i; j < n; j++) {
			if (arr[j] < arr[min])
				min = j;
		}
		SWAP(arr[i], arr[min], temp);
	}
	printf("\nSorted array:\n");
	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	printf("\nEnter the number to search: ");
	scanf("%d", &integer);
	//SWAP매크로, 반복문으로 구현
	/*left = 0, right = n - 1;
	for (int i = 0; i < n; i++) {
		middle = (left + right) / 2;
		if (arr[middle] < integer)
			left = middle + 1;
		else if (arr[middle] > integer)
			right = middle - 1;
		else {
			printf("The searchnum is present in list[%d]", middle);
			exit(0);
		}
	}
	printf("The search number is not present.");
	*/

	//SWAP매크로,COMPARE매크로, 재귀함수로 구현
	
	return 0;
}
int binSearch(int arr[],int left,int middle,int searchNum) {
	
}