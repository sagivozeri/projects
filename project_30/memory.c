#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct student {
	int age;
	int grade;
	int height;
	int weight;
};

int main(int argc, char **argv)
{
	struct student s1 = {0}, s2 = {0};

	s1.age = 20;
	s1.grade = 80;
	s1.height = 180;
	s1.weight = 70;

	printf("Student s1: age = %d, grade = %d, height = %d, weight = %d\n",
			s1.age, s1.grade, s1.height, s1.weight);

	printf("Student s2: age = %d, grade = %d, height = %d, weight = %d\n",
			s2.age, s2.grade, s2.height, s2.weight);

	memcpy(&s2, &s1, sizeof(struct student));

	printf("Student s1: age = %d, grade = %d, height = %d, weight = %d\n",
			s1.age, s1.grade, s1.height, s1.weight);

	printf("Student s2: age = %d, grade = %d, height = %d, weight = %d\n",
			s2.age, s2.grade, s2.height, s2.weight);

	return 0;
}
