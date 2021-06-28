#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MALLOC(p,s) {\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficientmemory\n");\
		exit(EXIT_FAILURE);\
	}\
}
typedef int iType;
typedef struct {
	int key;
	iType item;
}element;
typedef struct node *treePointer;
typedef struct node {
	element data;
	treePointer leftChild, rightChild;
}node;

element* search(treePointer root, int key);
void insert(treePointer *node, int k, iType theItem);
treePointer modifiedSearch(treePointer node, int k);
void inorder(treePointer root);

treePointer root;
int main() {
	element *ptr;
	int key;
	iType item;
	int seed, n, searchnum;
	int i = 0;
	printf("random number generation <1~500>\nthe number of nodes in BST<less than and equal to 50> :");
	scanf_s("%d", &n);
	printf("seed : "); scanf_s("%d", &seed);
	srand(seed);
	printf("creating a BST from random numbers");
	while (i < n) {
		key = rand() % ((500 - 1) + 1) + 1;
		item = key;
		insert(&root, key, item);
		i++;
	}
	printf("\nthe key to search: "); scanf_s("%d", &searchnum);
	ptr = search(root, searchnum);

	printf("inorder traversal of the BST shows the sorted sequence\n");
	inorder(root);
}
element* search(treePointer root, int key) {
	if (!root) {
		printf("there is no such an element\n");
		return NULL;
	}
	if (key == root->data.key) {
		printf("the element's item is %d\n", root->data.item);
		return &(root->data);
	}
	if (key < root->data.key)
		return search(root->leftChild, key);
	return search(root->rightChild, key);
}
void insert(treePointer *node, int k, iType theItem) {
	treePointer ptr;
	treePointer temp = modifiedSearch(*node, k);
	if (temp || !(*node)) {
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = k;
		ptr->data.item = theItem;
		ptr->leftChild = NULL;
		ptr->rightChild = NULL;
		if (*node) {
			if (k < temp->data.key) temp->leftChild = ptr;
			else temp->rightChild = ptr;
			//else로 안하고 k>node->data.key하면 node가 nullptr에러
		}
		else *node = ptr;
	}
}
treePointer modifiedSearch(treePointer node, int k) {//반복문탐색
	treePointer temp = NULL;
	if (!node) return NULL;
	while (node) {
		temp = node;
		if (k == node->data.key) return NULL;
		if (k < node->data.key)
			node = node->leftChild;
		else//else로 안하고 k>node->data.key하면 node가 nullptr에러
			node = node->rightChild;
	}
	return temp;
}
void inorder(treePointer root) {
	if (root) {
		inorder(root->leftChild);
		printf("%5d", root->data.item);
		inorder(root->rightChild);
	}
}