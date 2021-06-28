#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MALLOC(p,s){\
	if(!((p)=malloc(s))){\
		fprintf(stderr, "insufficient memory");\
		exit(EXIT_FAILURE);\
	}\
}
typedef enum{FALSE, TRUE}tBoolean;
typedef struct edge* tEdgePointer;
typedef struct edge {
	tBoolean marked;
	int vertex1;
	int vertex2;
	tEdgePointer link1;
	tEdgePointer link2;
}tEdge;

tEdgePointer createEdge(int ver1, int ver2);
void addEdge(tEdgePointer temp, int ver1, int ver2);
void printMultilist(int numVertex, int choice);

tEdgePointer* adjMulList;

int main() {
	tEdgePointer edge;
	int vNum, eNum;
	int v1, v2;
	FILE *fp;
	fopen_s(&fp, "input_2.txt", "r");
	fscanf_s(fp, "%d%d", &vNum, &eNum);
	MALLOC(adjMulList, vNum * sizeof(tEdgePointer));
	for (int i = 0; i < vNum; i++)
		adjMulList[i] = NULL;
	for(int i=0; i<eNum; i++){
		fscanf_s(fp, "%d%d", &v1, &v2);
		edge = createEdge(v1, v2);
		addEdge(edge, v1, v2);
	}
	printf("간선 출력-입력데이터순서\n");
	printMultilist(vNum, 0);
	printf("간선 출력-헤더노드 정점이 먼저오게\n");
	printMultilist(vNum, 1);

}
tEdgePointer createEdge(int ver1, int ver2) {
	tEdgePointer element;
	MALLOC(element, sizeof(*element));
	element->vertex1 = ver1;
	element->vertex2 = ver2;
	element->link1 = NULL;
	element->link2 = NULL;
	return element;
}
void addEdge(tEdgePointer temp, int ver1, int ver2) {
	tEdgePointer cur, pre=NULL;
	int order;
	if (adjMulList[ver1] == NULL)//예외발생>>adjList 메모리할당 안했음
		adjMulList[ver1] = temp;
	else {
		cur = adjMulList[ver1];
		while (cur != NULL) {
			pre = cur;
			if (cur->vertex1 == ver1) {
				cur = cur->link1;
				order = 0;
			}
			else {
				cur = cur->link2;
				order = 1;
			}
		}
		if (order == 0) {
			pre->link1 = temp;
		}
		else
			pre->link2 = temp;
	}
	if (adjMulList[ver2] == NULL)
		adjMulList[ver2] = temp;
	else {
		cur = adjMulList[ver2];
		while (cur != NULL) {
			pre = cur;
			if (cur->vertex2 == ver2) {
				cur = cur->link2;
				order = 0;
			}
			else {
				cur = cur->link1;
				order = 1;
			}
		}
		if (order == 0) {
			pre->link2 = temp;
		}
		else
			pre->link1 = temp;
	}
}
void printMultilist(int numVertex, int choice) {
	tEdgePointer cur;
	if (choice == 0) {//입력데이터순서
		for (int i = 0; i < numVertex; i++) {
			cur = adjMulList[i];
			printf("edges incident to vertex %d ", i);
			while (cur != NULL) {
				printf("<%d,%d>", cur->vertex1, cur->vertex2);
				if (i == cur->vertex1)
					cur = cur->link1;
				else
					cur = cur->link2;
			}
			printf("\n");
		}
	}
	else {//헤더노드정점이 먼저오게
		for (int i = 0; i < numVertex; i++) {
			cur = adjMulList[i];
			printf("edges incident to vertex %d ", i);
			while (cur != NULL) {
				if (i == cur->vertex1) {
					printf("<%d,%d>", cur->vertex1, cur->vertex2);
					cur = cur->link1;
				}
				else {
					printf("<%d,%d>", cur->vertex2, cur->vertex1);
					cur = cur->link2;
				}
			}
			printf("\n");
		}
	}
}
