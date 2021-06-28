#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define COMPARE(x, y) ((x>y)?1:((x==y)?0:-1))
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory allocation.");\
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

treePointer modifiedSearch(treePointer tree, int k);
void insert(treePointer *root, iType item, int key);
void inorder(treePointer root);

treePointer root;

int main() {
	iType item;
	int key;
	int n, seed;
	printf("seed : ");
	scanf("%d", &seed);
	printf("nodeNum : ");
	scanf("%d", &n);
	srand(seed);
	for (int i = 0; i < n; i++) {
		key = rand() % 500 + 1;
		item = key;
		//printf("%4d", key);//생성된 key
		insert(&root, item, key);
		//inorder(root);
		printf("\n");
	}
	printf("\n");
	inorder(root); printf("\n");

	return 0;
}
treePointer modifiedSearch(treePointer tree, int k) {
	/*while (tree) {
		switch (COMPARE(k, tree->data.key)) {
		case 1:tree = tree->rightChild;
		case 0: return tree;
		case -1: tree = tree->leftChild;
		}
	}
	return NULL;*/
	treePointer insertPos;
	MALLOC(insertPos, sizeof(*insertPos));
	if (!tree) return NULL;
	while (tree) {
		insertPos = tree;
		if (k == tree->data.key)
			return NULL;
		if (k < tree->data.key)
			tree = tree->leftChild;
		else
			tree = tree->rightChild;
	}
	return insertPos;
}
void insert(treePointer *root, iType item, int key) {
	treePointer ptr, temp = modifiedSearch(*root, key);//temp는 insert위치
	if (temp || !(*root)) {
	//key is not in tree
		MALLOC(ptr, sizeof(*ptr));
		ptr->data.key = key;
		ptr->data.item = item;
		ptr->leftChild = NULL;
		ptr->rightChild = NULL;//새로운노드 삽입을 위해 노드 세팅
		
		if (*root) {
			//트리가 null이 아니라면
			if (temp->data.key > key)//key가 더작으면 leftChild로 가야 이원탐색트리
				temp->leftChild = ptr;
			else
				temp->rightChild = ptr;//key가 루트보다 크면 rightChild로 가야 이원탐색트리

		}
		else
			*root = ptr;
	}
}
void inorder(treePointer root) {
	if (root) {
		inorder(root->leftChild);
		printf("%4d", root->data.item);
		inorder(root->rightChild);
	}
}