#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_STACK_SIZE 100
#define MALLOC(p,s) {\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
typedef enum {not, and, or, eos, operand}logical;
typedef struct treeNode *treePointer;
typedef struct treeNode {
	treePointer leftChild;
	char data;
	treePointer rightChild;
}treeNode;

logical getToken(char *symbol, int *n);
treePointer createBinTree();
void inorder(treePointer root);
treePointer pop();
treePointer stackEmpty();
void push(treePointer item);
void stackFull();

treePointer root;
char expr[81];
treePointer stack[MAX_STACK_SIZE];
int top = -1;

int main() {
	FILE *fp;
	fopen_s(&fp, "postfix.txt", "r");
	fgets(expr, 80, fp);
	printf("input string<postfix> : %s\n", expr);
	printf("creating its binary tree\n");
	root = createBinTree();
	printf("inorder traversal :"); inorder(root);
}
logical getToken(char *symbol, int *n) {
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '~': return not;
	case '&': return and;
	case '|': return or ;
	case '\0': return eos;
	default: return operand;
	}
}
treePointer createBinTree() {
	logical token;
	char symbol;
	int n = 0;
	treePointer op1, op2;
	treePointer newNode;
	token = getToken(&symbol, &n);
	while (token != eos) {
		if (token == operand) {
			MALLOC(newNode, sizeof(*newNode));
			newNode->data = symbol;
			newNode->leftChild = NULL;
			newNode->rightChild = NULL;
			push(newNode);
		}
		else {
			if (token == not) {//not이면 다른 연산자가 더필요함.(두 변수에 적용되서 결과값 낼 수없음)
				MALLOC(newNode, sizeof(*newNode));
				newNode->data = symbol;
				newNode->rightChild = pop();
				newNode->leftChild = NULL;
			}
			else {
				MALLOC(newNode, sizeof(*newNode));
				newNode->data = symbol;
				op1 = pop();
				op2 = pop();
				newNode->rightChild = op1;
				newNode->leftChild = op2;
			}
			push(newNode);
		}
		token = getToken(&symbol, &n);
	}
	return pop();
}
void inorder(treePointer root) {
	if (root) {
		inorder(root->leftChild);
		printf("%c", root->data);
		inorder(root->rightChild);
	}
}
treePointer pop() {
	if (top == -1)
		return stackEmpty();
	return stack[top--];
}
treePointer stackEmpty() {
	treePointer item;
	MALLOC(item, sizeof(*item));
	item->data = -1;
	return item;
}
void push(treePointer item) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	stack[++top] = item;
}
void stackFull() {
	fprintf(stderr, "stack is full, cannot add int\n");
	exit(EXIT_FAILURE);
}