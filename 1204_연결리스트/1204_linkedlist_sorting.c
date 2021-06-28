//연결리스트 정렬하면서 생성
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
typedef struct listNode* listPointer;
typedef struct listNode {
	int data;
	listPointer link;
}listNode;
listPointer first = NULL;

listPointer find(listPointer , int );
void insert(listPointer* , listPointer , int);
void printList(listPointer );
listPointer delete(listPointer first);
int main() {
	listPointer insertPoint=NULL;
	int data;
	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &data);
	while (!feof(fp)) {
		insertPoint = find(first, data);
		insert(&first, insertPoint, data);
		fscanf(fp, "%d", &data);
	}
	printList(first);//여기까진 리스트에 삽입할때 정렬하면서 삽입하는거

	first=delete(first);
	printf("list was deleted\n");

	return 0;
}
listPointer find(listPointer first, int data) {
	listPointer insertPoint;
	MALLOC(insertPoint, sizeof(*insertPoint));
	insertPoint = first;
	if (first == NULL)//만약에 빈리스트면
		return NULL;
	while (1) {//빈리스트 아니면
		//일단 제일처음에 삽입해야된다면?
		if (first->data >= data)
			return NULL;
		//아니면 중간에
		if (data >= insertPoint->data) {
			if (insertPoint->link == NULL)
				return insertPoint;
			else if (insertPoint->link->data >= data)
				return insertPoint;
			else
				insertPoint = insertPoint->link;
		}
		//아니면 제일끝에
		else
			insertPoint = insertPoint->link;
	}
}
void insert(listPointer* first, listPointer preNode, int data) {
	//실제 첫노드는 포인터로 가지고 온다.
	//(값을 바꿔야 할수도 있으니 값바꾸려면 매개변수 포인터로 받아올것)
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	if ((*first) != 0) {//if(*first)>>*first의 값이 있음일때>>빈 리스트가 아닐때
		if (preNode == NULL) {//만약 첫노드로 삽입하고 싶다면=>prenode가 NULL일때
			temp->link = (*first);
			(*first) = temp;
		}
		else {//prenode뒤에 삽입하고 싶다면
			temp->link = preNode->link;
			preNode->link = temp;
		}
	}
	else {
		temp->link = NULL;
		(*first) = temp;
	}
}
void printList(listPointer first) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp = first;
	while (1) {
		printf("%3d", temp->data);
		if (temp->link == NULL)
			break;
		temp = temp->link;
	}
	printf("\n");
}
listPointer delete(listPointer first) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp = first;
	if (first == NULL)
		return temp;
	while (temp->link != NULL)
		temp = temp->link;
	return temp;
}