//�������� ���
//���α׷� �帧 :: ���Ͽ��� ������ �Է¹޾� expr�� ����,
//					���Ե� expr�� eval�Լ��� ����Ѵ�.
//eval�Լ������� getToken���� symbol�� �ϳ��� expr�� ���ڸ� �����ͼ� �˻��Ѵ�.
//	���ÿ� �ǿ����ڸ� �����ڸ� ���������� ����ִٰ� �����ڸ� ������ ����־��� �ǿ����ڵ��� �ϳ��� �����ͼ� ����Ѵ�.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
typedef enum{lparen, rparen, plus, minus, times, divide, mod, eos, operand}precedence;

int eval();
precedence getToken(char *symbol, int *n);
void push(int item);
void stackFull();
int pop();
int stackEmpty();

int stack[MAX_STACK_SIZE];
int top = -1;
char expr[MAX_EXPR_SIZE];

int main() {
	FILE *fp=fopen("input.txt", "r");
	fgets(expr, sizeof(expr), fp);
	printf("postfix expression : %s\n", expr);
	printf("the evaluation value : %d", eval());
	fclose(fp);
	return 0;
}
int eval() {
	precedence token;
	char symbol;
	int n = 0;
	int op1, op2;
	token = getToken(&symbol, &n);//eos�Ǵ��ϱ����� ù getToken;
	while (token != eos) {
		if (token == operand)
			push(symbol - '0');//symbol�� ���� char���̶� ���ڰ��� �ƴϰ� ���ڰ��� �ƽ�Ű�ڵ带 ���µ�
		//�̰� ���� ���ڷ� ���̴� ���ڰ����� ������ַ��� �ƽ�Ű�ڵ尪���� ����Ѵ�.
		//0�� �ƽ�Ű�ڵ尪 : 48�̱� ������ symbol-'0'�ϸ� �� ������ ���� ���´�.
		else {
			op2 = pop();
			op1 = pop();
			switch (token) {
			case plus:push(op1 + op2); break;
			case minus:push(op1 - op2); break;
			case times:push(op1*op2); break;
			case divide:push(op1 / op2); break;
			case mod:push(op1%op2); break;
			}
		}
		token = getToken(&symbol, &n);//getToken���� ���� ��ū ��� �˻��ؾߵȴ�.
	}
	return pop();
}
precedence getToken(char *symbol, int *n) {
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
void push(int item) {
	if (top > MAX_STACK_SIZE-1)
		stackFull();
	stack[++top] = item;
}
void stackFull() {
	fprintf(stderr, "stack is full. cannot push.");
	exit(EXIT_FAILURE);
}
int pop() {
	if (top < 0)
		return stackEmpty();
	return stack[top--];
}
int stackEmpty() {
	int err = -1;
	return err;
}