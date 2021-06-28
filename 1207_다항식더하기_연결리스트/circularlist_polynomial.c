//���׽� ���ϱ⸦ ȯ������Ʈ�� ����

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define TRUE 1
#define FALSE 0
#define COMPARE(x, y) ((x>y)?1:((x==y)?0:-1))
#define MALLOC(p,s) {\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory allocation.\n");\
		exit(EXIT_FAILURE);\
	}\
}
typedef struct listNode *listPointer;
typedef struct listNode{
	int coef;
	int expon;
	listPointer link;
}listNode;

void erase(listPointer *first);														// Program 4.11
listPointer getNode(void);															// Program 4.12
void retNode(listPointer node);													// Program 4.13
void cerase(listPointer *ptr);														// Program 4.14
listPointer cpadd(listPointer a, listPointer b);							// Program 4.15
void attach(int coefficient, int exponent, listPointer *ptr);		// Program 4.10 ����
void insertFront(listPointer *last, listPointer node);					// Program 4.18 ����
void insertLast(listPointer *last, listPointer node);					// Program 4.18 ����
void printCList(listPointer header);												// Program 4.19 ����

// create a polynomial from file
void inputPolyCL(char *filename, listPointer *header, listPointer *last);

listPointer avail, a, b, c, lastA, lastB, lastC;

int main() {
	inputPolyCL("a.txt", &a, &lastA);
	inputPolyCL("b.txt", &b, &lastB);
	
	printf("a: "); printCList(a);
	//printf("%d %d  %d %d  %d %d", a->link->coef, a->link->expon, a->link->link->coef, a->link->link->expon, a->link->link->link->coef, a->link->link->link->expon);inputdata ���Ȯ�ο�
	printf("b: "); printCList(b);
	c = cpadd(a, b);
	printf("a+b: "); printCList(c);
	cerase(&a);
	cerase(&b);
	cerase(&c);
	erase(&avail);

	return 0;
}
void insertFront(listPointer *last, listPointer node) {
	//���׽��� ���� ó���� ���γ�带 ���� �ִٰ� �����Ѵ�.
	if (*last) {//not empty, next to header node
		node->link = (*last)->link->link;
		(*last)->link->link = node;
		if ((*last)->expon == -1)//for first input data;
			*last = node;
	}
	else {//empty
		*last = node;
		node->link = node;
	}
}
void insertLast(listPointer *last, listPointer node) {
	if (*last) {//not empty
		node->link = (*last)->link;
		(*last)->link = node;
		(*last) = node;
	}
	else {//empty
		*last = node;
		node->link = node;
	}
}
void inputPolyCL(char *filename, listPointer *header, listPointer *last) {
	FILE *fp = fopen(filename, "r");
	char order;
	listPointer node;

	*header = getNode();
	(*header)->expon = -1;
	*last = NULL;
	insertLast(last, *header);

	fscanf(fp, "%c", &order);
	node = getNode();
	fscanf(fp, "%d%d", &node->coef, &node->expon);
	/*if (order == 'a')
		insertFront(last, *header);*/
	if (order == 'd') {
		insertLast(last, node);
		while (!feof(fp)) {
			node = getNode();
			fscanf(fp, "%d%d", &node->coef, &node->expon);
			//printf("%d%d\n", node->coef, node->expon);input��� üũ��
			insertLast(last, node);
		}
		//retNode(node);//Q>>retnode ���� �־�ߵ���?
	}
	else {
		insertFront(last, node);
		while (!feof(fp)) {
			node = getNode();
			fscanf(fp, "%d%d", &node->coef, &node->expon);
			//printf("%d%d\n", node->coef, node->expon);//input��� üũ��
			insertFront(last, node);
		}
		//retNode(node);
	}
	fclose(fp);
}
void printCList(listPointer head) {
	listPointer temp;
	if (head != NULL) {
		temp = head->link;
		while (temp!=head) {
			printf("%+dx^%d ", temp->coef, temp->expon);
			temp = temp->link;
		}
	}
	printf("\n");
}
listPointer getNode() {
	listPointer node;
	if (avail != NULL) {
		node = avail;
		avail = avail->link;
	}
	else
		MALLOC(node, sizeof(*node));
	return node;
}
//���� ����Ʈ���� ��� ��������(==MALLOC)
void retNode(listPointer node) {
	node->link = avail;//node �ڿ��� avail����Ʈ(���� ����Ʈ)����
	avail = node;//avail��忡�� getNode�� �޾ƿ� ��쿡�� ��� ��ȯ�� node�� �ٰ��̴�. 
}
//��带 ���� ����Ʈ�� ��ȯ(==free(node))
void cerase(listPointer *p) {//���� ����Ʈ ����
	listPointer temp;
	if (*p) {
		temp = (*p)->link;
		(*p)->link = avail;
		avail = temp;
		*p = NULL;
	}
}
void erase(listPointer *ptr) {
	listPointer temp;
	while (*ptr!=NULL) {
		temp = (*ptr);
		(*ptr) = (*ptr)->link;
		free(temp);
	}
}
/*
����Ʈ�� ��Ұ����� ������� ���� ����Ʈ ���� ����
*p����Ʈ�� ù��° ��Ұ��� �� avail�� �����Ű�¹����.
*/
void attach(int coefficient, int exponent, listPointer *ptr) {
	listPointer temp;
	temp = getNode();
	temp->expon = exponent;
	temp->coef = coefficient;
	(*ptr)->link = temp;
	*ptr = temp;	
}
listPointer cpadd(listPointer a, listPointer b) {
	listPointer startA, c, lastC;
	int done = FALSE;
	startA = a;
	a = a->link;//zeroNode pass
	b = b->link;//zeroNode pass
	c = getNode();//zero Node
	c->expon = -1;//zeroNode-expon=-1
	lastC = c;
	do {
		switch (COMPARE(a->expon, b->expon)) {
		case -1://(a<b)
			attach(b->coef, b->expon, &lastC);
			b = b->link;
			break;
		case 0://a==b
			if (startA == a) done = TRUE;
			else {
				if ((a->coef + b->coef) != 0) {
					attach(a->coef + b->coef, a->expon, &lastC);
					a = a->link;
					b = b->link;
				}
			}
			break;
		case 1://a>b
			attach(a->coef, a->expon, &lastC);
			a = a->link;
			break;
		}
	} while (!done);
	lastC->link = c;//�ܼ�����Ʈ���� temp=c, c=c->link, free(temp)�ؼ� 
					//c�� novalue singlenode �����ѰͰ� ���� ����
	return c;
}
