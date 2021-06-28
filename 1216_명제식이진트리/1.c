#include <stdio.h>
#include <stdlib.h>
#define MAX_STACK_SIZE 100
typedef enum{lparen, rparen, and, or, not, eos, operand}logical;

int isp[] = { 0, 19, 12, 12, 13, 0 };
int icp[] = { 20, 19, 12, 12, 13, 0 };

void postfix(void);
logical getToken(char *symbol, int *n);
void printToken(logical pre);
logical pop();
logical stackEmpty();
void push(logical item);
void stackFull();

char expr[81];
logical stack[MAX_STACK_SIZE];
int top = -1;

int main() {
	FILE *fp;
	fopen_s(&fp, "infix.txt", "r");
	fgets(expr, 80, fp);
	printf("<<<<<<<infix to postfiz>>>>>>>\n");
	printf("infix: "); printf("%s", expr);
	printf("\npostfix: "); postfix();
}
void postfix(void)
{
	char symbol;
	logical token;
	int n = 0;
	top = -1;
	stack[++top] = eos; /* place eos on stack */

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{
		if (token == operand)
		{
			printf("%c", symbol);
		}
		else if (token == rparen) {
			/* unstack tokens until left parenthesis */
			while (stack[top] != lparen)
				printToken(pop());
			pop();	/* discard the left parenthesis */
		}
		else { // operator, lparen
			/* remove and print symbols whose isp is greater
				than or equal to the current token's icp */
			while (isp[stack[top]] >= icp[token])
				printToken(pop());
			push(token);
		}
	}// for

	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}
logical getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')':  return rparen;
	case '~': return not;
	case '&': return and;
	case '|': return or ;
	case '\0': return eos;
	default: return operand;
	}
}
void printToken(logical pre)
{
	switch (pre)
	{
	case not:	printf("~"); break;
	case and:	printf("&"); break;
	case or :	printf("|"); break;
	default:;	// operand
	}

}

/////////////////////// stack operations ///////////////////////////////////
logical pop() {
	if (top == -1)
		return stackEmpty();	/* returns an error key */
	return stack[top--];
}
logical stackEmpty() {
	logical item;
	item = operand;  // error key! In this program, operand is used for error key, since stack has only operators.
	return item;
}
void push(logical item) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}
void stackFull() {
	fprintf(stderr, "stack is full, cannot add int\n");
	exit(EXIT_FAILURE);
}

