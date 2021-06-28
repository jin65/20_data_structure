#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define FALSE 0
#define TRUE 1
typedef struct humanBeing {
	char name[20];
	int age;
	int salary;
}humanBeing;

int humanEqual(humanBeing person1, humanBeing person2);

int main() {
	humanBeing p1, p2;
	printf("Input person1's name, age, salary :\n");
	gets(p1.name);
	scanf("%d", &p1.age);
	scanf("%d", &p1.salary);
	getchar();
	printf("Input person2's name, age, salary :\n");
	gets(p2.name);
	scanf("%d", &p2.age);
	scanf("%d", &p2.salary);
	getchar();
	if (humanEqual(p1, p2))
		printf("The two human beings are the same\n");
	else
		printf("The two human beings are not the same\n");

	return 0;
}
int humanEqual(humanBeing person1, humanBeing person2) {
	if (strcmp(person1.name, person2.name) != 0)
		return FALSE;
	if (person1.age != person2.age)
		return FALSE;
	if (person1.salary != person2.salary)
		return FALSE;
	return TRUE;
}