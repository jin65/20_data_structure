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
//������ ����>>�� ������ĵ>>�� ��������
//��ġ�Ҷ��� ��(col)�� ��ĵ>>��(row)Ȯ�� ����
void fastTranspose(term a[], term b[]) {
	int rowTerms[MAX_COL], startingPos[MAX_COL];//rowTerms::a �� �ϳ����� �� �����->b �� �ϳ����� �� �
												//startingPos::b �� ���� ������ġ üũ
	int i, j;
	b[0].row = a[0].col;//b ��==a ��
	b[0].col = a[0].row;//b ��==a ��
	b[0].value = a[0].value;
	if (a[0].value > 0) {//0��� �ƴϸ�
		for (i = 0; i < a[0].col; i++)//a ������ Ȯ��>>b �ళ����ŭ 0���� �ʱ�ȭ
			rowTerms[i] = 0;
		for (i = 1; i <= a[0].value; i++)//b�� �� �࿡���� ���Ұ� ��� ������
			rowTerms[a[i].col]++;//a�� ��������� ����>>���κ��� �����ִ»���
								 //�����ִ� a ���κ� ���ʷ� �о�ͼ� b�� a���ε�����° ��(��ġ)�� ���Ҽ�++
		startingPos[0] = 1;//b[0]�� �������.�����������>>��ŸƮ�������� b[1]
		for (i = 1; i < a[0].col; i++)//a�� ���� �о�鼭
			startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];//������Ÿ�� ��ġ+rowTerms[��������ġ]=(������ ���Ұ���)>>b�� ���� ������ ��Ÿ�� �������� �Ѿ
																  //>>b�� �� ���� ��Ÿ����ġ ã�Ƴ���
		for (i = 1; i <= a[0].value; i++) {
			j = startingPos[a[i].col]++;//a ����ī����>>������ b ���� ��Ÿ�� ���������� ��� �̵�
										//a�� row���� ���ĵ� �����̹Ƿ�(a[i].col::4>3>5>...�� ��������)
			//��ġ����
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