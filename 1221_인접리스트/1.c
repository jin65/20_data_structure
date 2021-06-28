#include <stdio.h>
#include <stdlib.h>
#define MAX 100
typedef struct node *nodePointer;
typedef struct node {
	int data;
	nodePointer link;
}node;

void insert(int s, int v);

nodePointer adjList[MAX];
int main() {
	char type;
	int vertex, edge;
	int s, v;
	FILE *fp;
	fopen_s(&fp, "input.txt", "r");
	fscanf_s(fp, "%c%d%d", &type, sizeof(type), &vertex, &edge);
	if(type=='u')
		for (int i = 0; i < edge; i++) {
			fscanf_s(fp, "%d%d", &s, &v);
			insert(s, v);
			insert(v, s);
		}
	if(type=='d')
		for (int i = 0; i < edge; i++) {
			fscanf_s(fp, "%d%d", &s, &v);
			insert(s, v);
		}
	printf("adjacency list\n");
	for (int i = 0; i < vertex; i++) {
		printf("adjList[%d]:", i);
		while (adjList[i] != NULL) {
			printf("%2d", adjList[i]->data);
			adjList[i] = adjList[i]->link;
		}
		printf("\n");
	}
}
void insert(int s, int v) {
	nodePointer item;
	item = (node*)malloc(sizeof(node));
	item->data = v;
	item->link = adjList[s];//항상 헤더노드가 가리키는 처음노드로 입력되게함
	//item->link=adjList[s]>>삽입할 노드의 링크가 현재 adjList[s]의 첫 노드
	adjList[s] = item;//adjList[s]에 젤 첫위치로 삽입
}
