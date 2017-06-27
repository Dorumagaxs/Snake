//ANSI C libs
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <pthread.h>

//Custom libs
#include "../libs/doruUtilities.h"

//Modules
#include "snake.h"

int screenWidth, screenHeight, stopGame;
pthread_t tid[2];

void printScore(int score);
void* moving(void *snake);
void startGame(Coordinate initTitleArea, Coordinate endTitleArea);
void showRecordsTable(Coordinate initTitleArea, Coordinate endTitleArea);
void menu();

void printScore(int score) {
	
	char scoreString[15], stringifiedNumber[5];
	
	gotoxy(screenWidth/2-5, 3);
	printf("SCORE: %04d", score);

}

void* moving(void *snake) {
	tid[1] = pthread_self();

	int isThereFood, score;
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


	printScore(score);
	while (!stopGame) {
		clearSnake(snake);
		moveSnake((Queue*)snake);
		printSnake((Queue*)snake);
		if (isColliding(snake, initGameArea, endGameArea)) {
			stopGame = 1;
		}
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
	menu();
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
	printCentered("1 - Play", 1, screenWidth, 11);
	printCentered("2 - Records", 1, screenWidth, 13);
	printCentered("3 - Get the fuck out", 1, screenWidth, 15);

	while (1) {
		option = getchar();

		switch(option) {
			case 49:
				startGame(initTitleArea, endTitleArea);
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
