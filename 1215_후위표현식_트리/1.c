#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STACK_SIZE 100
#define MAX_EXPR_SIZE 100
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory\n");\
		exit(EXIT_FAILURE);\
	}\
}
typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand }precedence;
typedef struct treeNode *treePointer;
typedef struct treeNode {
	char data;
	treePointer leftchild, rightchild;
}treeNode;

treePointer createBinTree();
precedence getToken(char *symbol, int *n);
void push(treePointer item);
treePointer pop();
treePointer stackEmpty();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

treePointer root;
treePointer stack[MAX_STACK_SIZE];
char expr[MAX_EXPR_SIZE];//postfix expression
int top = -1;

int main(){
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	printf("postfix expression:");
	fgets(expr, sizeof(expr), fp);
	printf("%s", expr);
	printf("\n");
	root = createBinTree();
	printf("inorder:  "); inorder(root);
	printf("\npreorder:  "); preorder(root);
	printf("\npostorder:  "); postorder(root);
}
treePointer createBinTree() {
	precedence token;
	char symbol;
	int n = 0;
	treePointer op1, op2;
	top = -1;
	token = getToken(&symbol, &n);
	treePointer tNode;
	treePointer newNode;
	while (token != eos) {
		if (token == operand) {
			MALLOC(newNode, sizeof(*newNode));
			newNode->data = symbol;
			newNode->rightchild = NULL;
			newNode->leftchild = NULL;
			push(newNode);
		}
		else {
			MALLOC(tNode, sizeof(*tNode));
			tNode->data = symbol;
			op1 = pop();
			op2 = pop();
			tNode->rightchild = op1;
			tNode->leftchild = op2;
			push(tNode);
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}
precedence getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];//symbol값을 getToken함수 밖에서도 쓰기위해서 포인터로 사용함.
	switch (*symbol) {
	case '(':return lparen;
	case ')':return rparen;
	case '+':return plus;
	case '-':return minus;
	case '/':return divide;
	case '*':return times;
	case '%':return mod;
	case '\0':return eos;
	default: return operand;
	}
}
void push(treePointer item) {
	if (top > MAX_STACK_SIZE - 1) {
		fprintf(stderr, "stackfull\n");
		exit(EXIT_FAILURE);
	}
	stack[++top] = item;
}
treePointer pop() {
	if (top < 0) {
		fprintf(stderr, "stackEmpty\n");
		exit(EXIT_FAILURE);
	}
	return stack[top--];
}
treePointer stackEmpty() {
	treePointer item;
	MALLOC(item, sizeof(*item));
	item->data = -1;
	return item;
}
void inorder(treePointer ptr) {//L->Root->R
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%c", ptr->data);
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr) {//Root->L->R
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr) {//L->R->Root
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%c", ptr->data);
	}
}