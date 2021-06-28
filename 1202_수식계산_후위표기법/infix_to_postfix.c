//중위식을 입력받아 후위식으로 나타내기-스택활용예제
//프로그램 흐름 :: 이번엔 피연산자가 아니고 연산자들을 스택에 쌓는다.
//우선순위가 높은쪽이 출력된다.
//isp<icp면 push
//isp>=icp면 pop
//icp우선순위 높으면 push된다.
//왜 이렇게 하느냐? 내가 지금들고잇는거(icp)보다 이미 들어가있는게(isp) 우선순위가 낮으면 push
//내가 지금 갖고있는게(icp) 이미 들어가있는거(isp)보다 우선순위가 낮으면 다시 icp가 높아질때까지 pop하고, 그제서야 push한다.
//그리고 isp와 icp에서 왼괄호(lparen)는 isp일때는 우선순위가 제일 낮다. 일단 무조건 push하고 오른괄호만날때 생각한다.
//근데 isp에서는 우선순위가 제일 높다. 왜냐면 오른괄호를 만나면 연산자 상관없이 바로 무조건 pop해서 삭제해야되니까 어떤 연산자가 token으로 와도 pop한다. >> isp(lparen)는 젤크다.
//왼괄호는 오른괄호를 만났을때 왼괄호까지 스택속의 원소들이 바로 출력된다.
//그래서 왼괄호보다 위에있는 연산자들을 모두 pop해야되니까 isp에서 왼괄호보다 다른 연산자들은 우선순위가 낮다.
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
//스택함수
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