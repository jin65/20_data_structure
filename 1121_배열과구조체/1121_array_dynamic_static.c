//3차원배열을 동적할당, 정적할당으로 함수전달
#include <stdio.h>
#include <stdlib.h>

int sumAry3D_f1(int arr[2][3][4], int s, int r, int c);
int sumAry3D_f2(int arr[][3][4], int s, int r, int c);
int sumAry3D_f3(int(*arr)[3][4], int s, int r, int c);
int sumAry3D_f4(int*** arr, int s, int r, int c);
int sumAry3D_f5(int**** arr, int s, int r, int c);
void freeAry3D(int ***arr, int r, int c);

int main() {
	int r, c, s;
	int ary3D[][3][4] = { { {1,2,3,4}, {2,3,4,5}, {3,4,5,6} },{{1,2,3,4},{2,3,4,5},{3,4,5,6}} };
	int*** arr=(int***)malloc(sizeof(int**)*2);
	for (r = 0; r < 2; r++) {
		arr[r] = (int**)malloc(sizeof(int*) * 3);
		for (c = 0; c < 3; c++)
			arr[r][c] = (int*)malloc(sizeof(int) * 4);
	}

	for (s = 0; s < 2; s++)
		for (r = 0; r < 3; r++)
			for (c = 0; c < 4; c++)
				arr[s][r][c] = s + r + c;
	
	/*for (s = 0; s < 2; s++)
		for (r = 0; r < 3; r++)
			for (c = 0; c < 4; c++)
				printf("%d ", arr[s][r][c]);
	printf("\n");*/

	printf("sumAry2D_f1() %d\n", sumAry3D_f1(ary3D, 2, 3, 4));
	printf("sumAry2D_f2() %d\n", sumAry3D_f2(ary3D, 2, 3, 4));
	printf("sumAry2D_f3() %d\n", sumAry3D_f3(ary3D, 2, 3,4));

	printf("sumAry2D_f4() %d\n", sumAry3D_f4(arr, 2, 3, 4));
	printf("sumAry2D_f5() %d\n", sumAry3D_f5(&arr, 2, 3, 4));
	freeAry3D(arr, 2, 3);
	return 0;
}
int sumAry3D_f1(int arr[2][3][4], int s, int r, int c){
	int sum=0;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < c; k++)
				sum += arr[i][j][k];
	return sum;
}
int sumAry3D_f2(int arr[][3][4], int s, int r, int c) {
	int sum=0;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < c; k++)
				sum += arr[i][j][k];
	return sum;
}
int sumAry3D_f3(int (*arr)[3][4], int s, int r, int c) {
	int sum = 0;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < c; k++)
				sum += arr[i][j][k];
	return sum;
}
int sumAry3D_f4(int***arr, int s, int r, int c) {
	int sum = 0;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < c; k++)
				sum += arr[i][j][k];
	return sum;
}
int sumAry3D_f5(int****arr, int s, int r, int c) {
	int sum = 0;
	for (int i = 0; i < s; i++)
		for (int j = 0; j < r; j++)
			for (int k = 0; k < c; k++)
				sum += (*arr)[i][j][k];
	return sum;
}
void freeAry3D(int*** arr, int s, int r) {
	for (s; s == 0;s--) {//배열의 끝에서부터 해제해야 된다.
		for (r; r==0; r--)
			free(arr[s][r]);
		free(arr[s]);
	}
	free(arr);
	printf("3Darray-free!");
}