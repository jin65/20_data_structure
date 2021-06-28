#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
#define MAX_COL 10

typedef struct {
	int col;
	int row;
	int value;
}term;

void fastTranspose(term a[], term b[]);
void printMtrix(term a[]);

int main() {
	term a[MAX_SIZE];
	term b[MAX_SIZE];

	FILE *ifp, *ofp;
	fopen_s(&ifp, "a.txt", "r");
	fopen_s(&ofp, "b.txt", "w");

	fscanf_s(ifp, "%d %d %d", &a[0].row, &a[0].col, &a[0].value);
	for (int i = 1; i <= a[0].value; i++)
		fscanf_s(ifp, "%d %d %d", &a[i].row, &a[i].col, &a[i].value);

	fastTranspose(a, b);

	printMtrix(a);
	printf("\n");
	printMtrix(b);
	printf("\n");
	fclose(ifp);
	fclose(ofp);
}
//희소행렬 정렬>>행 먼저스캔>>열 오름차순
//전치할때는 열(col)로 스캔>>행(row)확인 순서
void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];//rowTerms::a 열 하나마다 값 몇개인지->b 행 하나마다 값 몇개
												//startingPos::b 각 행의 시작위치 체크
	int i, j;
	b[0].row = a[0].col;//b 행==a 열
	b[0].col = a[0].row;//b 열==a 행
	b[0].value = a[0].value;
	if (a[0].value > 0) {//0행렬 아니면
		for (i = 0; i < a[0].col; i++)//a 열개수 확인>>b 행개수만큼 0으로 초기화
			rowTerms[i] = 0;
		for (i = 1; i <= a[0].value; i++)//b의 각 행에대해 원소가 몇개씩 들어가는지
			rowTerms[a[i].col]++;//a는 행기준으로 정렬>>열부분은 섞여있는상태
								 //섞여있는 a 열부분 차례로 읽어와서 b의 a열인덱스번째 행(전치)의 원소수++
		startingPos[0] = 1;//b[0]은 행렬정보.사용하지않음>>스타트포지션이 b[1]
		for (i = 1; i < a[0].col; i++)//a의 열을 읽어가면서
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];//이전스타팅 위치+rowTerms[이전행위치]=(이전행 원소개수)>>b의 다음 행으로 스타팅 포지션이 넘어감
																  //>>b의 각 행의 스타팅위치 찾아놓음
		for (i = 1; i <= a[0].value; i++) {
			j = startingPos[a[i].col]++;//a 원소카운팅>>읽히는 b 행의 스타팅 포지션으로 계속 이동
										//a는 row기준 정렬된 상태이므로(a[i].col::4>3>5>...로 섞여있음)
			//전치실행
			b[j].row = a[i].col;
			b[j].col = a[i].row;
			b[j].value = a[i].value;
		}
	}
}
void printMtrix(term a[]) {
	int k = 1;
	for (int i = 0; i < a[0].row; i++) {
		for (int j = 0; j < a[0].col; j++) {
			if (i == a[k].row && j == a[k].col)
				printf("%3d", a[k++].value);
			else
				printf("%3d", 0);
		}
		printf("\n");
	}
}