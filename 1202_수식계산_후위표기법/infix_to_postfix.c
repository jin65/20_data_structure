//�������� �Է¹޾� ���������� ��Ÿ����-����Ȱ�뿹��
//���α׷� �帧 :: �̹��� �ǿ����ڰ� �ƴϰ� �����ڵ��� ���ÿ� �״´�.
//�켱������ �������� ��µȴ�.
//isp<icp�� push
//isp>=icp�� pop
//icp�켱���� ������ push�ȴ�.
//�� �̷��� �ϴ���? ���� ���ݵ���մ°�(icp)���� �̹� ���ִ°�(isp) �켱������ ������ push
//���� ���� �����ִ°�(icp) �̹� ���ִ°�(isp)���� �켱������ ������ �ٽ� icp�� ������������ pop�ϰ�, �������� push�Ѵ�.
//�׸��� isp�� icp���� �ް�ȣ(lparen)�� isp�϶��� �켱������ ���� ����. �ϴ� ������ push�ϰ� ������ȣ������ �����Ѵ�.
//�ٵ� isp������ �켱������ ���� ����. �ֳĸ� ������ȣ�� ������ ������ ������� �ٷ� ������ pop�ؼ� �����ؾߵǴϱ� � �����ڰ� token���� �͵� pop�Ѵ�. >> isp(lparen)�� ��ũ��.
//�ް�ȣ�� ������ȣ�� �������� �ް�ȣ���� ���ü��� ���ҵ��� �ٷ� ��µȴ�.
//�׷��� �ް�ȣ���� �����ִ� �����ڵ��� ��� pop�ؾߵǴϱ� isp���� �ް�ȣ���� �ٸ� �����ڵ��� �켱������ ����.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum {
	lparen, rparen, plus, minus, times, divide, mod, eos, operand
}precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
int icp[] = { 20,19,12,12,13,13,13,0 };

char expr[MAX_EXPR_SIZE];
precedence stack[MAX_STACK_SIZE];
int top = -1;

precedence getToken(char*, int*);
void printToken(precedence);
void push(precedence item);
precedence pop();
void stackFull();
precedence stackEmpty();
void postfix();

FILE* fp;
FILE* output;

int main() {
	fp = fopen("input.txt", "r");
	output = fopen("output.txt", "w");
	char outexpr[MAX_EXPR_SIZE];
	fgets(expr, sizeof(expr), fp);
	printf("exist expression: %s\n", expr);
	printf("postfix expression: ");
	postfix();
	fclose(fp);
	fclose(output);
	return 0;
}
void postfix() {
	char symbol;
	precedence token;
	int n = 0;
	top = 0;
	stack[0] = eos;
	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n)) {
		if (token == operand) {
			printf("%c", symbol);
			fprintf(output, "%c", symbol);
		}
		else if (token == rparen) {
			while (stack[top] != lparen)
				printToken(pop());
			pop();
		}
		else {
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}
	while ((token = pop()) != eos)
		printToken(token);

	printf("\n");
}
void printToken(precedence token) {
	switch (token) {
	case plus:printf("+"); fprintf(output, "+"); break;
	case minus:printf("-"); fprintf(output, "-"); break;
	case times: printf("*"); fprintf(output, "*"); break;
	case divide: printf("/"); fprintf(output, "/"); break;
	case mod: printf("%%"); fprintf(output, "%%"); break;
	default: break;
	}
}
precedence getToken(char* symbol, int* n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(':return lparen;
	case ')':return rparen;
	case '+':return plus;
	case '-':return minus;
	case '*':return times;
	case '/':return divide;
	case '%':return mod;
	case '\0':return eos;
	default: return operand;
	}
}
//�����Լ�
void push(precedence item) {
	if (top > MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}
void stackFull() {
	fprintf(stderr, "stack is full. cannot push.");
	exit(EXIT_FAILURE);
}
precedence pop() {
	if (top < 0)
		return stackEmpty();
	return stack[top--];
}
precedence stackEmpty() {
	precedence err = -1;
	return err;
}