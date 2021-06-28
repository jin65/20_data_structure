//���Ḯ��Ʈ �����ϸ鼭 ����
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
	printList(first);//������� ����Ʈ�� �����Ҷ� �����ϸ鼭 �����ϴ°�

	first=delete(first);
	printf("list was deleted\n");

	return 0;
}
listPointer find(listPointer first, int data) {
	listPointer insertPoint;
	MALLOC(insertPoint, sizeof(*insertPoint));
	insertPoint = first;
	if (first == NULL)//���࿡ �󸮽�Ʈ��
		return NULL;
	while (1) {//�󸮽�Ʈ �ƴϸ�
		//�ϴ� ����ó���� �����ؾߵȴٸ�?
		if (first->data >= data)
			return NULL;
		//�ƴϸ� �߰���
		if (data >= insertPoint->data) {
			if (insertPoint->link == NULL)
				return insertPoint;
			else if (insertPoint->link->data >= data)
				return insertPoint;
			else
				insertPoint = insertPoint->link;
		}
		//�ƴϸ� ���ϳ���
		else
			insertPoint = insertPoint->link;
	}
}
void insert(listPointer* first, listPointer preNode, int data) {
	//���� ù���� �����ͷ� ������ �´�.
	//(���� �ٲ�� �Ҽ��� ������ ���ٲٷ��� �Ű����� �����ͷ� �޾ƿð�)
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->data = data;
	if ((*first) != 0) {//if(*first)>>*first�� ���� �����϶�>>�� ����Ʈ�� �ƴҶ�
		if (preNode == NULL) {//���� ù���� �����ϰ� �ʹٸ�=>prenode�� NULL�϶�
			temp->link = (*first);
			(*first) = temp;
		}
		else {//prenode�ڿ� �����ϰ� �ʹٸ�
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