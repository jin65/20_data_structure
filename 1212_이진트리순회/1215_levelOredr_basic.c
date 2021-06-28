#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
#define MAX_QUEUE_SIZE 100
typedef struct treeNode* treePointer;
typedef struct treeNode {
	char data;
	treePointer leftChild, rightChild;
}treeNode;

void levelOder(treePointer root);
void addq(treePointer item);
void queueFull();
treePointer deleteq();
treePointer queueEmpty();

treePointer queue[MAX_QUEUE_SIZE];
int front = 0;
int rear = 0;
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
	levelOder(a);

	return 0;
}
void levelOder(treePointer root) {
	if (!root) return;
	addq(root);
	for (;;) {
		root = deleteq();
		if (root!=NULL) {
			printf("%c", root->data);
			if (root->leftChild)
				addq(root->leftChild);
			if (root->rightChild)
				addq(root->rightChild);
		}
		else
			break;
	}
}
//queueFunction
void addq(treePointer item) {
	if (rear == (rear + 1) % MAX_QUEUE_SIZE)
		queueFull();
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	queue[rear] = item;
}
void queueFull() {
	fprintf(stderr, "queueFUll");
	exit(EXIT_FAILURE);
}
treePointer deleteq() {
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];
}
treePointer queueEmpty() {
	treePointer err;
	MALLOC(err, sizeof(*err));
	err->data = -1;
	return err;
}