//���� �� ������Է� ���,
//�ʱ�ȭ�ؼ� a���+b���=c������� �����Ҵ��ؼ� ���ϱ� �� ���
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

void add(int** a, int** b, int** c, int rows, int cols);
int** make2dArray(int rows, int cols);
void init2dArray(int** a, int rows, int cols, int num);
void print2dArray(int** a, int rows, int cols);
void free2dArray(int** a, int rows);

int main() {
	int** a, ** b, ** c;
	int rows, cols;
	printf("Enter row size and column size(ex) 3 4 : ");
	scanf("%d %d", &rows, &cols);
	a = make2dArray(rows, cols);
	init2dArray(a, rows, cols,1);
	printf("matrixA\n");
	print2dArray(a, rows, cols);
	b = make2dArray(rows, cols);
	init2dArray(b, rows, cols,2);
	printf("matrixB\n");
	print2dArray(b, rows, cols);
	
	c = make2dArray(rows, cols);
	add(a, b, c, rows, cols);
	printf("matrixC\n");
	print2dArray(c, rows, cols);

	free2dArray(a, rows);
	free2dArray(b, rows);
	free2dArray(c, rows);
	return 0;
}
void add(int** a, int** b, int** c, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			c[i][j] = a[i][j] + b[i][j];
}
int** make2dArray(int rows, int cols) {
	int** a = (int**)malloc(sizeof(int*) * rows);
	for (int i = 0; i < rows; i++)
		a[i] = (int*)malloc(sizeof(int) * cols);

	return a;
}
void init2dArray(int** a, int rows, int cols, int num) {
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < cols; j++)
			a[i][j] = i + j+num;
}
void print2dArray(int** a, int rows, int cols) {
	for (int i = 0; i < rows; i++){
		for (int j = 0; j < cols; j++) {
			printf("%3d", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
void free2dArray(int** a, int rows) {
	for (rows; rows == 0; rows--)
		free(a[rows]);
	free(a);
	printf("2d array-free!\n");
}