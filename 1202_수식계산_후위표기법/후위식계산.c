//후위식의 계산
//프로그램 흐름 :: 파일에서 수식을 입력받아 expr로 대입,
//					대입된 expr을 eval함수로 계산한다.
//eval함수에서는 getToken으로 symbol에 하나씩 expr의 문자를 가져와서 검사한다.
//	스택에 피연산자를 연산자를 만날때까지 집어넣다가 연산자를 만나면 집어넣었던 피연산자들을 하나씩 꺼내와서 계산한다.
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
	token = getToken(&symbol, &n);//eos판단하기위한 첫 getToken;
	while (token != eos) {
		if (token == operand)
			push(symbol - '0');//symbol이 지금 char값이라서 숫자값이 아니고 문자값의 아스키코드를 갖는데
		//이걸 실제 문자로 보이는 숫자값으로 만들어주려면 아스키코드값으로 계산한다.
		//0의 아스키코드값 : 48이기 때문에 symbol-'0'하면 그 숫자의 값이 나온다.
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
		token = getToken(&symbol, &n);//getToken으로 다음 토큰 계속 검사해야된다.
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
//스택함수
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