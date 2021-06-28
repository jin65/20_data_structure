#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
#define MAX_STACK_SIZE 100
typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data;
	treePointer leftChild, rightChild;
}treeNode;
int top = -1;
treePointer stack[MAX_STACK_SIZE];
void iterInorder(treePointer node);
void stackFull();
treePointer stackEmpty();
void push(treePointer item);
treePointer pop();

int main() {
	treePointer root, a, b, c, d, e, f, g, h, i;
	MALLOC(a, sizeof(*a));
	MALLOC(b, sizeof(*b));
	MALLOC(c, sizeof(*c));
	MALLOC(d, sizeof(*d));
	MALLOC(e, sizeof(*e));
	MALLOC(f, sizeof(*f));
	MALLOC(g, sizeof(*g));
	MALLOC(h, sizeof(*h));
	MALLOC(i, sizeof(*i));
	a->data = 'a';
	a->leftChild = b;
	a->rightChild = c;
	b->data = 'b';
	b->leftChild = d;
	b->rightChild = e;
	c->data = 'c';
	c->leftChild = f;
	c->rightChild = g;
	d->data = 'd';
	d->leftChild = h;
	d->rightChild = i;
	e->data = 'e';
	e->leftChild = NULL;
	e->rightChild = NULL;
	f->data = 'f';
	f->leftChild = NULL;
	f->rightChild = NULL;
	g->data = 'g';
	g->leftChild = NULL;
	g->rightChild = NULL;
	h->data = 'h';
	h->leftChild = NULL;
	h->rightChild = NULL;
	i->data = 'i';
	i->leftChild = NULL;
	i->rightChild = NULL;
	iterInorder(a);

	return 0;
}
void iterInorder(treePointer node) {
	for (;;) {
		for (; node; node = node->leftChild) {
			push(node);
		}
		node = pop();
		if (!node) break;
		printf("\ndata: %c\n", node->data);
		node = node->rightChild;
	}
}
void push(treePointer item) {
	if (top >= MAX_STACK_SIZE - 1)
		stackFull();
	return stack[++top] = item;
}
void stackFull() {
	fprintf(stderr, "stackfull");
	exit(EXIT_FAILURE);
}
treePointer pop() {
	if (top < 0)
		return stackEmpty();
	return stack[top--];
}
treePointer stackEmpty() {
	treePointer err;
	MALLOC(err, sizeof(*err));
	err->data = -1;
	return err;
}