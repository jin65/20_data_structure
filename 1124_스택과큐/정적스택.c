#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 5
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;
 
void push(element item);
element pop();
void stackFull();
element stackEmpty();
void printStack();

element stack[MAX_STACK_SIZE];
int top = -1;

int main() {
	char input[30];
	char *ptr=NULL;
	element student;
	printf("stack operation where MAX_STACK_SIZE is 5\n");
	printf("push 1 jung\npop\n\n");
	printf("*****************************************\n");
	while (1) {//while문을 계속 실행한다 종료조건은 while문 안에서 체크
		gets_s(input, sizeof(input));//스트링 받아오기
		ptr = strtok(input, " ");//분할함수, " "를 구분자로 input을 분할해 ptr로 반환
		if (strcmp(ptr, "push") == 0) {
			sscanf(input + strlen(ptr) + 1, "%d%s", &student.id, student.name);
			//input의 첫주소+ptr(push 단어수)+공백 길이
			push(student);
		}
		else if (strcmp(ptr, "pop") == 0) {//pop을 입력하면
			if (pop().id == -1) {
				fprintf(stderr, "stack is empty. cannot delete element\n");
				exit(EXIT_FAILURE);
			}
			else
				pop();
		}
		else
			printf("wrong command! try again!\n");
	}
}
void push(element item) {
	if (top >= MAX_STACK_SIZE-1)
		stackFull();
	stack[++top] = item;
}
element pop() {
	if (top <= -1)
		return stackEmpty();
	return stack[top--];
}
void stackFull() {
	fprintf(stderr, "stackfull!\n");
	printf("current stack elements:\n");
	printStack();
	exit(EXIT_FAILURE);
}
element stackEmpty() {
	element err;
	err.id = -1;
	return err;
}
void printStack() {
	while (top >= 0) {
		printf("%d %s\n", stack[top].id, stack[top].name);
		pop();
	}
}