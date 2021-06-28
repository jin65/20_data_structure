#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME_SIZE 20
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr,"insufficient memory\n");\
		exit(EXIT_FAILURE);\
	}\
}

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

void addq(element item);
element deleteq();
void queueFull();
element queueEmpty();
void copy(element *a, element *b, element *c);

element *queue;
int capacity = 2;
int rear = 0;
int front = 0;

int main() {
	char input[MAX_NAME_SIZE];
	char *ptr;
	element student;
	printf("circular queue operations where the initial capacity is 2\n");
	printf("add 1 jung\n");
	printf("delete\n");
	printf("***************************************************************\n");
	MALLOC(queue, capacity*sizeof(*queue));
	while (1) {
		gets_s(input, sizeof(input));
		ptr = strtok(input, " ");
		if (strcmp(ptr, "add") == 0) {
			sscanf(input + strlen(ptr) + 1, "%d%s", &student.id, student.name);
			addq(student);
		}
		else if (strcmp(ptr, "delete") == 0) {
			element item = deleteq();
			if (item.id == -1) {
				fprintf(stderr, "queue is empty. cannot delete element\n");
				exit(EXIT_FAILURE);
			}
			else {
				printf("deleted item: %d, %s\n", item.id, item.name);
			}
		}
		else if (strcmp(ptr, "quit")) {
			printf("program quit.\n");
			exit(0);
		}
		else
			printf("wrong command! try again!\n");
	}
}
void addq(element item) {
	rear = (rear + 1) % capacity;
	if (front == rear)
		queueFull();
	queue[rear] = item;
}
element deleteq() {
	if (front == rear)
		return queueEmpty();
	front = (front + 1) % capacity;
	return queue[front];
}
void queueFull() {//////copy 실행내용 공부
	int start;
	element* newQueue;
	MALLOC(newQueue, 2 * capacity * sizeof(*queue));
	start = (front + 1) % capacity;
	if (start < 2)
		copy(queue + start, queue + start + capacity - 1, newQueue);
	else
	{
		copy(queue + start, queue + capacity, newQueue);
		copy(queue, queue + rear + 1, newQueue + capacity - start);
	}
	front = 2 * capacity - 1;
	rear = capacity - 1;
	capacity *= 2;
	free(queue);
	queue = newQueue;
	printf("queue capacity is doubled\n");
	printf("current queue capacity is %d\n", capacity);
}
element queueEmpty() {
	element err;
	err.id = -1;
	return err;
}
void copy(element *a, element *b, element *c) {
	//a~b-1까지 c시작주소부분부터 삽입으로 복사
	while (a != b)
		*c++ = *a++;
}