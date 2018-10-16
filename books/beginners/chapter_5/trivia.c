#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int  sportsQuestion(void);
int  geographyQuestion(void);
void pause(int);

int iResponse = 0;

int main() {
	do {
		system("clear");
		printf("\n\tThe Trivia Game\n\n");
		printf("1\tSports\n");
		printf("2\tGeography\n");
		printf("3\tQuit\n");
		printf("Enter you selection: ");
		scanf_s("%d", &iResponse);

		switch (iResponse) {
			case 1: {
				if (sportsQuestion() == 4)
					puts("Correct");
				else
					puts("Incorrect");
				pause(2);
			} break;
			case 2: {
				if (geographyQuestion() == 2)
					puts("Correct");
				else
					puts("Incorrect");
				pause(2);
			} break;
		}

	} while (iResponse != 3);

	return (0);
}

int sportsQuestion() {
	int iAnswer = 0;

	system("clear");
	printf("\tSports Question");
	printf("\nWhat University did NFL star Deon Sanders attend?");
	printf("\n\n1\tUniversity of Miami\n");
	printf("2\tCalifornia State University\n");
	printf("3\tIndiana University\n");
	printf("4\tFlorida State University\n");
	printf("\nEnter you selection:  ");
	scanf_s("%d", &iAnswer);

	return (iAnswer);
}

int geographyQuestion() {
	int iAnswer = 0;

	system("clear");
	printf("\tGeography Question");
	printf("\nWhat is the state capitol of Florida?");
	printf("\n\n1\tPensecola\n");
	printf("2\tTallahassee\n");
	printf("3\tJacksonville\n");
	printf("4\tMiami\n");
	printf("\nEnter you selection:  ");
	scanf_s("%d", &iAnswer);

	return (iAnswer);
}

void pause(int inNum) {
	int iCurrentTime = 0;
	int iElapsedTime = 0;

	iCurrentTime = time(NULL);

	do {
		iElapsedTime = time(NULL);
	} while (iElapsedTime - iCurrentTime < inNum);
}
