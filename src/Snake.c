//ANSI C libs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

//Custom libs
#include "../libs/doruUtilities.h"
#include "../libs/queue.h"

//Modules
#include "snake.h"
#include "scores.h"

char playerName[10];
int screenWidth, screenHeight, stopGame, score;
pthread_t tid[2];

void printOnGameHeader(int score);
void printScore(int score);
void* moving(void *snake);
void startGame(Coordinate initTitleArea, Coordinate endTitleArea);
void choosePlayerName(Coordinate initTitleArea, Coordinate endTitleArea);
void showRecordsTable(Coordinate initTitleArea, Coordinate endTitleArea);
void menu();

void printOnGameHeader(int score) {
	Record record;

	gotoxy(3,3);
	printf("PLAYER: %s", playerName);

	printScore(score);

	record = getRecord();
    gotoxy(screenWidth-17-strlen(record.playerName), 3);
    printf("RECORD: %04d (%s)", record.score, record.playerName);
}

void printScore(int score) {
	gotoxy(screenWidth/2-5, 3);
	printf("SCORE: %04d", score);
}

void* moving(void *snake) {
	tid[1] = pthread_self();

	int isThereFood;
	Coordinate initGameArea, endGameArea, food;
	struct timespec waitingTime;
	SnakePoint *snakeHead;

	isThereFood = 0;
	score = 0;

	initGameArea.x = 2;
	initGameArea.y = 6;
	endGameArea.x = screenWidth-1;
	endGameArea.y = screenHeight-1;

	waitingTime.tv_sec = 0;
	waitingTime.tv_nsec = 100000000;

	snakeHead = (SnakePoint*) getValue(snake, 0);


	printOnGameHeader(score);
	while (!stopGame) {
		clearSnake(snake);
		moveSnake((Queue*)snake);
		printSnake((Queue*)snake);
		if (isColliding(snake, initGameArea, endGameArea)) {
			stopGame = 1;
		}
		else {
			if (ateFood(snakeHead, food)) {
				isThereFood = 0;
				feedSnake(snake);

				score++;
				printScore(score);
			}
			if (!isThereFood) {
				food = generateFood(snake, initGameArea, endGameArea);
				isThereFood = 1;
				printFood(food);
			}
			nanosleep(&waitingTime, NULL);
		} 
	}

	return NULL;
}

void startGame(Coordinate initTitleArea, Coordinate endTitleArea) {
	int i, threadError, event;
	Coordinate initGameArea, endGameArea;
	struct timespec waitingTime;
	SnakePoint *snakeHead;
	Queue *snake;

	initGameArea.x = 2;
	initGameArea.y = 6;
	endGameArea.x = screenWidth-1;
	endGameArea.y = screenHeight-1;

	waitingTime.tv_sec = 0;
	waitingTime.tv_nsec = 100000000;

	snake = newSnake(screenWidth/2 - 2, screenHeight/2);
	snakeHead = (SnakePoint*) getValue(snake, 0);

	srand(time(NULL));

	clearArea(initTitleArea, endTitleArea);
	clearArea(initGameArea, endGameArea);

	threadError = pthread_create(&(tid[1]), NULL, &moving, snake);
	
	if (threadError != 0) {
		printf("[ERROR] Could not create thread");
		exit(0);
	}

	stopGame = 0;
	while(!stopGame) {
		fflush(stdin);
		event = getchar();

		fprintf(fopen("bla.txt","w"), "%i", event);
		if (event == 27) {
			event = getchar();

			if (event == 91) {
				event = getchar();

				switch (event) {
					case 65:
						turnSnake(snakeHead, UP);
						break;
					case 66:
						turnSnake(snakeHead, DOWN);
						break;
					case 67:
						turnSnake(snakeHead, RIGHT);
						break;
					case 68:
						turnSnake(snakeHead, LEFT);
						
				}
			}
		}
		else
			stopGame = 1;
	}
    addNewScore(playerName, score);

	menu();
}

void choosePlayerName(Coordinate initTitleArea, Coordinate endTitleArea) {
	system("stty cooked -brkint && stty echo");

	gotoxy(screenWidth/2 - 15,8);
	printf("Choose a name as player: ");
	fgets(playerName, 10, stdin);
	fflush(stdin);

	system("stty raw && stty -echo");
	startGame(initTitleArea, endTitleArea);
}

void showRecordsTable(Coordinate initTitleArea, Coordinate endTitleArea) {

}

void menu() {
	int option;
	Coordinate initTitleArea, endTitleArea;

	initTitleArea.x = 2;
	initTitleArea.y = 2;
	endTitleArea.x = screenWidth-1;
	endTitleArea.y = 4;

	system("clear");
    printScreenBorder(screenWidth, screenHeight);

	printCentered("Snake", 1, screenWidth, 3);
	printCentered("1 - Play", 1, screenWidth, 12);
	printCentered("2 - Records", 1, screenWidth, 14);
	printCentered("3 - Get the fuck out", 1, screenWidth, 16);

	while (1) {
		option = getchar();

		switch(option) {
			case 49:
				choosePlayerName(initTitleArea, endTitleArea);
				break;
			case 50:
				showRecordsTable(initTitleArea, endTitleArea);
				break;
			case 51:
				exit(0);
		}
	}
}

int main(int argc, char *argv[]) {
	
	tid[0] = pthread_self();

	if (argc < 3) {
        printf("[ERROR] Too few parameters\n");
        exit(0);
    }

    screenHeight = atoi(argv[1]);
    screenWidth = atoi(argv[2]);

    menu();

	return 0;
}
