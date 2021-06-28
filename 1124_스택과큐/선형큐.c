#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 5
#define MAX_NAME_SIZE 20

typedef struct {
	int id;
	char name[MAX_NAME_SIZE];
}element;

void addq(element item);
element deleteq();
element queueEmpty();
void queueFull();
void arrayshifting();

element queue[MAX_QUEUE_SIZE];
int rear = -1;
int front = -1;

int main() {
	char input[MAX_NAME_SIZE];
	char *ptr;
	element student;
	printf("linear queue operation whehe MAX_QUEUE_SIZE is 5\n");
	printf("add 1 jung\ndelete\n");
	printf("******************************************************\n");
	while (1) {
		gets_s(input, sizeof(input));
		ptr=strtok(input, " ");
		if (strcmp(ptr, "add") == 0) {
			sscanf(input + strlen(ptr) + 1, "%d%s", &student.id, student.name);
			addq(student);
		}
		else if (strcmp(ptr, "delete") == 0) {
			if (deleteq().id == -1) {
				fprintf(stderr, "queue is empyt, cannot delete element\n");
				exit(EXIT_FAILURE);
			}
			else
				deleteq();
		}
		else
			printf("wrong command! try again!\n");
	}
}
void addq(element item) {
	if (rear == MAX_QUEUE_SIZE - 1)
			queueFull();
	else
		queue[++rear] = item;
}
element deleteq() {
	if (front == rear)
		return queueEmpty();
	else
		return queue[++front];
}
element queueEmpty() {
	element err;
	err.id = -1;
	return err;
}
void queueFull() {
	fprintf(stderr, "queue is full. cannot add element!\n");
	printf("current queue elements:\n");
	while (front != rear) {
		deleteq();
		printf("%d %s\n", queue[front].id, queue[front].name);
	}
	exit(EXIT_FAILURE);
}