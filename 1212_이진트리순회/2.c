#include <stdio.h>
#include <stdlib.h>
#define MAX_QUEUE_SIZE 50
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory\n");\
		exit(EXIT_FAILURE);\
	}\
}
typedef struct treeNode *treePointer;
typedef struct treeNode{
	char data;
	treePointer leftchild;
	treePointer rightchild;
}treeNode;
treePointer root;
treePointer queue[MAX_QUEUE_SIZE];
int front=-1, rear=-1;

treePointer createNode(char data);
treePointer createCompBinTree(FILE *fp);
void insert(treePointer *pRoot, treePointer pNode);
int hasBothChild(treePointer pNode);
void addq(treePointer item);
treePointer deleteq();
void queueFull();
treePointer queueEmpty();
treePointer getFront();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main() {
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	printf("creating a complete binary tree\n");
	root = createCompBinTree(fp);
	printf("\ninorder: "); inorder(root);
	printf("\npreorder: "); preorder(root);
	printf("\npostorder: "); postorder(root);
}
treePointer createNode(char data) {
	treePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->rightchild = NULL;
	temp->leftchild = NULL;
	return temp;
}
treePointer createCompBinTree(FILE *fp) {
	char data;
	treePointer temp;
	fscanf_s(fp, "%c", &data, sizeof(char));
	temp = createNode(data);
	while (!feof(fp)) {
		insert(&root, temp);
		fscanf_s(fp, "%c", &data, sizeof(char));
		temp = createNode(data);
	}
	free(temp);

	return root;
}
void insert(treePointer *pRoot, treePointer pNode) {
	if (*pRoot == NULL) {
		(*pRoot) = pNode;
	}
	else {
		treePointer temp = getFront();
		if (temp->leftchild == NULL) {
			temp->leftchild = pNode;
		}
		else if (temp->rightchild == NULL) {
			temp->rightchild = pNode;
		}
		if (hasBothChild(temp) == 1) {
			deleteq();
		}
	}
	addq(pNode);
}
int hasBothChild(treePointer pNode) {
	if ((pNode->leftchild != NULL) && (pNode->rightchild != NULL))
		return 1;
	else
		return 0;
}
void addq(treePointer item) {
	if (rear == MAX_QUEUE_SIZE - 1)
		queueFull();
	queue[++rear] = item;
}
treePointer deleteq() {
	if (front == rear)
		return queueEmpty();
	return queue[++front];
}
void queueFull() {
	fprintf(stderr, "queuefull\n");
	exit(EXIT_FAILURE);
}
treePointer queueEmpty() {
	treePointer err;
	MALLOC(err, sizeof(*err));
	err->data = -1;
	return err;
}
treePointer getFront() {
	return queue[front + 1];
}
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftchild);
		printf("%c", ptr->data);
		inorder(ptr->rightchild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftchild);
		preorder(ptr->rightchild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftchild);
		postorder(ptr->rightchild);
		printf("%c", ptr->data);
	}
}