//다항식 더하기를 환형리스트로 구현

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
void attach(int coefficient, int exponent, listPointer *ptr);		// Program 4.10 수정
void insertFront(listPointer *last, listPointer node);					// Program 4.18 수정
void insertLast(listPointer *last, listPointer node);					// Program 4.18 수정
void printCList(listPointer header);												// Program 4.19 수정

// create a polynomial from file
void inputPolyCL(char *filename, listPointer *header, listPointer *last);

listPointer avail, a, b, c, lastA, lastB, lastC;

int main() {
	inputPolyCL("a.txt", &a, &lastA);
	inputPolyCL("b.txt", &b, &lastB);
	
	printf("a: "); printCList(a);
	//printf("%d %d  %d %d  %d %d", a->link->coef, a->link->expon, a->link->link->coef, a->link->link->expon, a->link->link->link->coef, a->link->link->link->expon);inputdata 출력확인용
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
	//다항식이 제일 처음에 제로노드를 갖고 있다고 생각한다.
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
			//printf("%d%d\n", node->coef, node->expon);input결과 체크용
			insertLast(last, node);
		}
		//retNode(node);//Q>>retnode 어디다 넣어야될지?
	}
	else {
		insertFront(last, node);
		while (!feof(fp)) {
			node = getNode();
			fscanf(fp, "%d%d", &node->coef, &node->expon);
			//printf("%d%d\n", node->coef, node->expon);//input결과 체크용
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
//가용 리스트에서 노드 가져오기(==MALLOC)
void retNode(listPointer node) {
	node->link = avail;//node 뒤에다 avail리스트(가용 리스트)연결
	avail = node;//avail노드에서 getNode로 받아올 경우에는 방금 반환한 node를 줄것이다. 
}
//노드를 가용 리스트로 반환(==free(node))
void cerase(listPointer *p) {//원형 리스트 제거
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
리스트의 요소개수에 상관없이 원형 리스트 전부 제거
*p리스트의 첫번째 요소고리를 뜯어서 avail로 변경시키는방법임.
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
	lastC->link = c;//단순리스트에서 temp=c, c=c->link, free(temp)해서 
					//c의 novalue singlenode 해제한것과 같은 역할
	return c;
}
