//기본적 단일연결리스트 생성(2노드)
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
typedef struct listNode *listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;

listPointer createlist();
void insert(listPointer *first, listPointer prenode, int data);
int main() {
	listPointer first;
	first=createlist();
	printf("%d ", first->data);
	printf("%d ", first->link->data);

	printf("\n");

	insert(&first, NULL, 50);
	insert(&first, NULL, 100);
	printf("%d ", first->data);
	printf("%d ", first->link->data);
	printf("%d ", first->link->link->data);
	printf("%d ", first->link->link->link->data);
	return 0;
}
listPointer createlist() {
	listPointer first, second;
	MALLOC(first, sizeof(*first));
	MALLOC(second, sizeof(*second));
	first->data = 10;
	second->data = 20;
	second->link = NULL;
	first->link = second;
	return first;
}
void insert(listPointer *first, listPointer prenode, int data) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	if (*first) {
		if (prenode == NULL) {
			temp->link = (*first);
			(*first) = temp;
		}

		else {
			temp->link = prenode->link;
			prenode->link = temp;
		}
	}
	else {
		temp->link = NULL;
		(*first)->link= temp;
	}
}