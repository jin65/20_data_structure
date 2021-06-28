#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr,"Insufficient Memory");\
		exit(EXIT_FAILURE);\
	}\
}
#define COMPARE(x, y) (((x)<(y)) ? -1 : ((x)==(y)) ? 0 : 1)
typedef struct polyNode *polyPointer;
typedef struct polyNode {
	int coef;
	int expon;
	polyPointer link;
}polyNode;
polyPointer a = NULL;
polyPointer b = NULL;
polyPointer c = NULL;
polyPointer padd(polyPointer a, polyPointer b); void insert(polyPointer *first, polyPointer x, int coef, int expon);
void attach(int coefficient, int exponent, polyPointer *ptr);
void printList(polyPointer first);
void findLast(polyPointer first, polyPointer *last);
void erase(polyPointer *ptr);
void inputPoly(char *filename, polyPointer *p);
int main() {
	inputPoly("a.txt", &a);
	inputPoly("b.txt", &b);

	printf("    a:");
	printList(a);
	printf("    b:");
	printList(b);

	c = padd(a, b);
	printf("a+b+c:");
	printList(c);

	erase(&a);
	erase(&b);
	erase(&c);

	return 0;
}
polyPointer padd(polyPointer a, polyPointer b) {
	polyPointer c, rear, temp;
	int sum;
	MALLOC(rear, sizeof(*rear));//더미노드
	c = rear;
	while (a&&b)
		switch (COMPARE(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
			sum = a->coef + b->coef;
			if (sum) attach(sum, a->expon, &rear);
			a = a->link; b = b->link; break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
		}
	for (; a; a = a->link) attach(a->coef, a->expon, &rear);
	for (; b; b = b->link) attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c; c = c->link; free(temp);
	return c;
}
void insert(polyPointer *first, polyPointer x, int coef, int expon) {
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coef;
	temp->expon = expon;
	if (first == NULL) {
		temp->link = NULL;
		*first = temp;
	}
	else {
		if (x == NULL) {
			temp->link = *first;
			*first = temp;
		}
		else {
			temp->link = x->link;
			x->link = temp;
		}
	}
}
void attach(int coefficient, int exponent, polyPointer *ptr) {
	polyPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}
void printList(polyPointer first) {
	for (; first; first = first->link)
		printf("%+4dx^%d", first->coef, first->expon);
	printf("\n");
}
void erase(polyPointer *ptr)
{
	polyPointer temp;
	while (*ptr)
	{
		temp = *ptr;
		*ptr = (*ptr)->link;
		free(temp);
	}
}
void findLast(polyPointer first, polyPointer *last) {
	for (; first; first = first->link)
		*last = first;
}
void inputPoly(char *filename, polyPointer *p) {
	int coef, expon;
	polyPointer x = NULL;
	polyPointer last = NULL;//내림차순으로 넣을때 마지막위치
	char order;//오름차순내림차순
	FILE *fp;
	fopen_s(&fp, filename, "r");
	fscanf_s(fp, "%c", &order, sizeof(order));

	while (!feof(fp)) {
		fscanf_s(fp, "%d%d", &coef, &expon);
		if (order == 'd') {
			findLast(*p, &last);
			x = last;
		}
		insert(p, x, coef, expon);
	}

	fclose(fp);
}