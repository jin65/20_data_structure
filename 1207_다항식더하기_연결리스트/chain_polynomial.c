//다항식 더하기를 연결리스트로 수행, 오름차순 내림차순일경우를 고려해서 계산.
//프로그램 흐름 :: 내림차순일경우 findlast로 마지막 삽입위치를 찾고 오름차순일경우는 제일 첫 노드로 삽입해서 inputPoly로 파일에서 다항식을 읽어옴>>padd로 다항식 더하기, padd에서는 각 노드를 attach함수로 더함.
//attach함수에서 rear와 temp의 사용>>rear는 각 항을 더할 때마다 더해서 결과로 나올 c다항식의 마지막노드를 가리킨다.
//rear가 없다면 항을 더할 때마다 c다항식을 읽어서 삽입할 위치(다항식의 제일 끝)을 찾아야 하기때문에 중복되는작업이 많이 생간다.
//c다항식은 no-value single node로 시작해서 그뒤에부터 항을 더한다. 그러면 마지막에 제일 첫노드(빈 노드)를 삭제해야되는데
//free(c)로 삭제해버리기엔 c뒤에 연결된 링크들을 잃어버리기 때문에 temp=c로 첫 노드를 temp에 주고, c=c->link로 마무리한다음 free(temp)로 삭제한다. 
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
	if (*first == NULL) {//애초에 리스트가 빈 리스트일때
		temp->link = NULL;
		*first = temp;
	}
	else {
		if (preNode == NULL)//빈 리스트가 아닐때 제일 첫 노드로 삽입
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
		if (order == 'd') {//내림차순>>마지막 노드로 삽입
			findLast(*a, &last);
			x = last;
			insert(a, x, expon, coef);
		}
		else if (order == 'a') {//오름차순>>첫 노드로 삽입
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
	//rear>>c의 마지막 노드를 가리키는 포인터
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
	//c는 더미노드(no-value single node)로 시작하기때문에 temp노드에 c의 첫노드 복사
	c = c->link;
	//temp에 복사해뒀기때문에 c=c->link로 c는 다음노드로 넘겨줌
	free(temp);
	//free(c)를 하면 c뒤에 연결된 link부분까지 다날아가기때문에 free(temp)로 노드를 옮겨서 할당해제한다.
	return c;
}
void attach(int coefficient, int exponent, listPointer *ptr) {
	listPointer temp;
	MALLOC(temp, sizeof(*temp));
	temp->expon = exponent;
	temp->coef = coefficient;
	(*ptr)->link = temp;//rear의 링크가 temp임.(rear끝에다 삽입)
	*ptr = temp;
	//rear는 항상 다항식의 제일 끝을 가리키고 있기 때문에 *ptr=temp로 제일 마지막 노드임을 명시
}
void erase(listPointer *ptr) {
	listPointer temp;
	while (*ptr != NULL)
	{
		temp = (*ptr);//할당해제할 노드 임시노드에 대입
		(*ptr) = (*ptr)->link;//다음 노드로 넘어가기
		free(temp);//연결 끊는다고 리스트노드가 삭제되는 것은 아님>>free로 할당해제해줘야함.
	}
}