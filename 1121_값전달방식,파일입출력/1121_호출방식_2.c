#include <stdio.h>
#include <stdlib.h>
//�����ͷ� �����Ҵ� �� ȣ�� ���������͵� �Լ��� ȣ��
int* func1() {
	int* pNum = (int*)malloc(sizeof(int));
	*pNum = 0;
	return pNum;
}
int* func2(int* pNum) {
	*pNum = 100;
	return pNum;
}
int** func3(int** pNum) {
	**pNum = 200;
	return pNum;
}

int main(){
	int* pNum = func1();
	printf("%d\n", *pNum);
	printf("%d\n", *func2(pNum));
	printf("%d\n", **func3(&pNum));

	free(pNum);
	return 0;
}