#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define TRUE 1
#define FALSE 0
#define MAX_ROW_SIZE 10
#define MAX_COL_SIZE 10

typedef struct {
	short int vert;
	short int horiz;
}offsets;//위치 이동 방향
offsets move[8] = { {-1, 0}, {-1, 1}, {0,1}, {1,1}, {1,0}, {1, -1}, {0, -1}, {-1,-1} };
//총 8방향이므로 offsets move[8]로 선언, 북쪽이 0째방향으로 시계방향으로 증가

typedef struct {
	short int row;
	short int col;
	short int dir;
}element;//위치정보

void path();
void push(element item);
element pop();
element stackEmpty();
void stackFull();

element stack[MAX_STACK_SIZE];
int top = -1;
int EXIT_ROW, EXIT_COL;
int maze[MAX_ROW_SIZE+2][MAX_COL_SIZE+2];//각 테두리에 1로 감싸야함
int mark[MAX_ROW_SIZE + 2][MAX_COL_SIZE + 2] = { 0 };
int EXIT_ROW, EXIT_COL;

int main() {
	int rNum, cNum;
	FILE *fp;
	fopen_s(&fp, "input2.txt", "r");
	fscanf_s(fp, "%d%d", &rNum, &cNum);
	for (int i = 0; i < rNum + 2; i++)
		for (int j = 0; j < cNum + 2; j++) {
			if (j == 0 || j == cNum + 1 || i == 0 || i == rNum + 1)
				maze[i][j] = 1;
			else
				fscanf_s(fp, "%d", &maze[i][j]);
		}
	EXIT_COL = cNum, EXIT_ROW = rNum;
	
	path();

}
void path() {
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;
	while (top > -1 && !found) {
		position = pop();
		row = position.row; col = position.col; dir = position.dir;
		while (dir < 8 && !found) {
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;
			
			if (nextRow == EXIT_ROW && nextCol == EXIT_COL)
				found = TRUE;
			else if (!maze[nextRow][nextCol] && !mark[nextRow][nextCol]) {
				mark[nextRow][nextCol] = 1;
				position.row = row;
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("the path is:\n");
		printf("row   col\n");
		for (i = 0; i <= top; i++)
			printf("%2d%5d\n", stack[i].row, stack[i].col);
		printf("%2d%5d\n", row, col);
		printf("%2d%5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("no path\n");
}
void push(element item) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}
element pop() {
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}
element stackEmpty() {
	element error;
	error.row = -1;
	printf("stack is empty. cannot delete element\n");
	return error;
}
void stackFull() {
	element item;
	fprintf(stderr, "Stack is full, cannot add element\n");
	printf("current stack element:\n");
	while (top > -1) {
		item = pop();
		printf("%d %d %d\n", item.row, item.col, item.dir);
	}
	exit(EXIT_FAILURE);
}