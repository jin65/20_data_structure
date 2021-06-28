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
	while (1) {//while���� ��� �����Ѵ� ���������� while�� �ȿ��� üũ
		gets_s(input, sizeof(input));//��Ʈ�� �޾ƿ���
		ptr = strtok(input, " ");//�����Լ�, " "�� �����ڷ� input�� ������ ptr�� ��ȯ
		if (strcmp(ptr, "push") == 0) {
			sscanf(input + strlen(ptr) + 1, "%d%s", &student.id, student.name);
			//input�� ù�ּ�+ptr(push �ܾ��)+���� ����
			push(student);
		}
		else if (strcmp(ptr, "pop") == 0) {//pop�� �Է��ϸ�
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