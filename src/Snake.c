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
void startGame(Coordinate initTitleArea, Coordinate endTitleArea, Coordinate initMainArea, Coordinate endMainArea);
void choosePlayerName(Coordinate initTitleArea, Coordinate endTitleArea, Coordinate initMainArea, Coordinate endMainArea);
void showScoresTable(Coordinate initTitleArea, Coordinate endTitleArea, Coordinate initMainArea, Coordinate endMainArea);
void menu();

void printOnGameHeader(int score) {
	Score record;

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
		moveSnake((Queue*)snake);
		printSnake((Queue*)snake);
		if (isColliding(snake, initGameArea, endGameArea)) {
			stopGame = 1;
			deleteQueue(snake);
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

void startGame(Coordinate initTitleArea, Coordinate endTitleArea, Coordinate initMainArea, Coordinate endMainArea) {
	int i, threadError, event;
	struct timespec waitingTime;
	SnakePoint *snakeHead;
	Queue *snake;

	waitingTime.tv_sec = 0;
	waitingTime.tv_nsec = 100000000;

	snake = newSnake(screenWidth/2 - 2, screenHeight/2);
	snakeHead = (SnakePoint*) getValue(snake, 0);

	srand(time(NULL));

	clearArea(initTitleArea, endTitleArea);
	clearArea(initMainArea, endMainArea);

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
						turnSnake(snake, UP);
						break;
					case 66:
						turnSnake(snake, DOWN);
						break;
					case 67:
						turnSnake(snake, RIGHT);
						break;
					case 68:
						turnSnake(snake, LEFT);
						
				}
			}
		}
		else {
			stopGame = 1;
			deleteQueue(snake);
		}
	}
    addNewScore(playerName, score);

	menu();
}

void choosePlayerName(Coordinate initTitleArea, Coordinate endTitleArea, Coordinate initMainArea, Coordinate endMainArea) {
	system("stty cooked -brkint && stty echo");

	gotoxy(screenWidth/2 - 15,8);
	printf("Choose a name as player: ");
	fgets(playerName, 10, stdin);
	fflush(stdin);

	system("stty raw && stty -echo");
	startGame(initTitleArea, endTitleArea, initMainArea, endMainArea);
}

void showScoresTable(Coordinate initTitleArea, Coordinate endTitleArea, Coordinate initMainArea, Coordinate endMainArea) {
	int i, option, leave, initScore, initScorePosition, scoresPerScreen;
	Score *score;
	Queue *scoresQueue;

	clearArea(initTitleArea, endTitleArea);
	clearArea(initMainArea, endMainArea);

	printCentered("List of Scores", 2, screenWidth-1, 3);
	gotoxy(3, screenHeight-1);
	printf("Move with arrows, pageUp/Down, Home/End. Tap another key to leave");

	isMoving = 0;
	isTurning = 0;
	moved = 0;

	scoresQueue = getScores();
	if (scoresQueue != NULL) {
		leave = 0;
		initScorePosition = 7;
		scoresPerScreen = (screenHeight-2) - initScorePosition;
		initScore = 0;

		do {

			for (i=0; (i < scoresPerScreen)&&(i+initScore < scoresQueue->size); i++) {
				score = (Score*) getValue(scoresQueue, i+initScore);

				gotoxy(screenWidth/2 - 11, i + initScorePosition);
				printf("%s ", score->playerName);

				gotoxy(screenWidth/2, i + initScorePosition);
				printf("= %04d", score->score);
			}

			option = getchar();
			if (option == 27) {
				option = getchar();

				if (option == 91) {
					option = getchar();

					switch (option) {
						case 65:
							if (initScore > 0)
								initScore--;
							break;
						case 66:
							if (initScore < (scoresQueue->size - scoresPerScreen))
								initScore++;
							break;
						default:
							leave = 1;
					}
				}
			}
			else {
				leave = 1;
			}
		} while(!leave);

		deleteQueue(scoresQueue);
	}

	menu();
}

void menu() {
	int option;
	Coordinate initTitleArea, endTitleArea, initMainArea, endMainArea;

	initTitleArea.x = 2;
	initTitleArea.y = 2;
	endTitleArea.x = screenWidth-1;
	endTitleArea.y = 4;

	initMainArea.x = 2;
	initMainArea.y = 6;
	endMainArea.x = screenWidth-1;
	endMainArea.y = screenHeight-1;

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
				choosePlayerName(initTitleArea, endTitleArea, initMainArea, endMainArea);
				break;
			case 50:
				showScoresTable(initTitleArea, endTitleArea, initMainArea, endMainArea);
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
