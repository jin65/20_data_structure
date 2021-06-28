#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s) {\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
typedef struct treeNode *treePointer;
typedef struct treeNode {
	char data;
	treePointer leftChild;
	treePointer rightChild;
}treeNode;
treePointer root = NULL;

treePointer createNode(char data);
treePointer createBinTree();
void inorder(treePointer ptr);
void preorder(treePointer ptr);
void postorder(treePointer ptr);

int main() {
	root = createBinTree();
	printf("creating binary tree\n");
	printf("\nthree binary tree traversals");
	printf("\ninorder: "); inorder(root);
	printf("\npreorder: "); preorder(root);
	printf("\npostorder: "); postorder(root);
}
treePointer createNode(char data) {
	treePointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	temp->rightChild = NULL;
	temp->leftChild = NULL;
	return temp;
}
treePointer createBinTree() {
	treePointer a, b, c, d, e;
	a = createNode('A');
	b = createNode('B');
	c = createNode('C');
	d = createNode('D');
	e = createNode('E');
	a->leftChild = b;
	a->rightChild = c;
	b->leftChild = d;
	b->rightChild = e;

	return a;
}
void inorder(treePointer ptr) {
	if (ptr) {
		inorder(ptr->leftChild);
		printf("%c", ptr->data);
		inorder(ptr->rightChild);
	}
}
void preorder(treePointer ptr) {
	if (ptr) {
		printf("%c", ptr->data);
		preorder(ptr->leftChild);
		preorder(ptr->rightChild);
	}
}
void postorder(treePointer ptr) {
	if (ptr) {
		postorder(ptr->leftChild);
		postorder(ptr->rightChild);
		printf("%c", ptr->data);
	}
}