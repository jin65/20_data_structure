//���׽� ���ϱ⸦ ���Ḯ��Ʈ�� ����, �������� ���������ϰ�츦 ����ؼ� ���.
//���α׷� �帧 :: ���������ϰ�� findlast�� ������ ������ġ�� ã�� ���������ϰ��� ���� ù ���� �����ؼ� inputPoly�� ���Ͽ��� ���׽��� �о��>>padd�� ���׽� ���ϱ�, padd������ �� ��带 attach�Լ��� ����.
//attach�Լ����� rear�� temp�� ���>>rear�� �� ���� ���� ������ ���ؼ� ����� ���� c���׽��� ��������带 ����Ų��.
//rear�� ���ٸ� ���� ���� ������ c���׽��� �о ������ ��ġ(���׽��� ���� ��)�� ã�ƾ� �ϱ⶧���� �ߺ��Ǵ��۾��� ���� ������.
//c���׽��� no-value single node�� �����ؼ� �׵ڿ����� ���� ���Ѵ�. �׷��� �������� ���� ù���(�� ���)�� �����ؾߵǴµ�
//free(c)�� �����ع����⿣ c�ڿ� ����� ��ũ���� �Ҿ������ ������ temp=c�� ù ��带 temp�� �ְ�, c=c->link�� �������Ѵ��� free(temp)�� �����Ѵ�. 
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) ((x>y)?1:((x==y)?0:-1))
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory allocation!\n");\
		exit(EXIT_FAILURE); \
	}\
}
typedef struct listNode *listPointer;
typedef struct listNode {
	int expon;
	int coef;
	listPointer link;
}listNode;

void findLast(listPointer first, listPointer *last);
void insert(listPointer *first, listPointer preNode, int expon, int coef);
void inputPoly(char *filename, listPointer *a);
void printList(listPointer first);
listPointer padd(listPointer a, listPointer b);
void attach(int coefficient, int exponent, listPointer *ptr);
void erase(listPointer *ptr);

listPointer a;
listPointer b;
listPointer c;
int main() {
	
	printf("attach A polynomial & B polynomial\n\n");

	inputPoly("a.txt", &a);
	inputPoly("b.txt", &b);

	printf("a :");printList(a);
	printf("b :");printList(b);

	c = padd(a, b);
	printf("a+b=c :"); printList(c);

	erase(&a);
	erase(&b);
	erase(&c);

	return 0;
}
void findLast(listPointer first, listPointer *last) {
	for (; first;first=first->link) {
		*last = first;
	}
}
void insert(listPointer *first, listPointer preNode, int expon, int coef) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->expon = expon;
	temp->coef = coef;
	if (*first == NULL) {//���ʿ� ����Ʈ�� �� ����Ʈ�϶�
		temp->link = NULL;
		*first = temp;
	}
	else {
		if (preNode == NULL)//�� ����Ʈ�� �ƴҶ� ���� ù ���� ����
		{
			temp->link = *first;
			*first = temp;
		}
		else {
			temp->link = preNode->link;
			preNode->link = temp;
		}
	}
}
void inputPoly(char *filename, listPointer *a) {
	int coef, expon;
	listPointer x = NULL;//x
	listPointer last = NULL;
	char order;

	FILE *fp = fopen(filename, "r");
	fscanf(fp, "%c", &order);
	while (!feof(fp)) {
		fscanf_s(fp, "%d%d", &coef, &expon);
		if (order == 'd') {//��������>>������ ���� ����
			findLast(*a, &last);
			x = last;
			insert(a, x, expon, coef);
		}
		else if (order == 'a') {//��������>>ù ���� ����
			insert(a, x, expon, coef);
		}
	}
	fclose(fp);
}
void printList(listPointer first) {
	for (; first;first=first->link) {
		printf("%+dx^%d ", first->coef, first->expon);
	}
	printf("\n");
}
listPointer padd(listPointer a, listPointer b) {
	listPointer c, rear, temp;// temp>>temporary, c>>result polynomial
	//rear>>c�� ������ ��带 ����Ű�� ������
	MALLOC(rear, sizeof(*rear));
	c = rear;
	while (a&&b)
		switch (COMPARE(a->expon, b->expon)) {
		case -1:
			attach(b->coef, b->expon, &rear);
			b = b->link;
			break;
		case 0:
			if ((a->coef + b->coef) != 0);
			attach(a->coef + b->coef, a->expon, &rear);
			a = a->link;
			b = b->link;
			break;
		case 1:
			attach(a->coef, a->expon, &rear);
			a = a->link;
			break;
		}
	for (; a; a = a->link)
		attach(a->coef, a->expon, &rear);
	for (; b; b = b->link)
		attach(b->coef, b->expon, &rear);
	rear->link = NULL;
	temp = c;
	//c�� ���̳��(no-value single node)�� �����ϱ⶧���� temp��忡 c�� ù��� ����
	c = c->link;
	//temp�� �����صױ⶧���� c=c->link�� c�� �������� �Ѱ���
	free(temp);
	//free(c)�� �ϸ� c�ڿ� ����� link�κб��� �ٳ��ư��⶧���� free(temp)�� ��带 �Űܼ� �Ҵ������Ѵ�.
	return c;
}
void attach(int coefficient, int exponent, listPointer *ptr) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->expon = exponent;
	temp->coef = coefficient;
	(*ptr)->link = temp;//rear�� ��ũ�� temp��.(rear������ ����)
	*ptr = temp;
	//rear�� �׻� ���׽��� ���� ���� ����Ű�� �ֱ� ������ *ptr=temp�� ���� ������ ������� ���
}
void erase(listPointer *ptr) {
	listPointer temp;
	while (*ptr != NULL)
	{
		temp = (*ptr);//�Ҵ������� ��� �ӽó�忡 ����
		(*ptr) = (*ptr)->link;//���� ���� �Ѿ��
		free(temp);//���� ���´ٰ� ����Ʈ��尡 �����Ǵ� ���� �ƴ�>>free�� �Ҵ������������.
	}
}