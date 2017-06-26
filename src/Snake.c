//ANSI C libs
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>

//Custom libs
#include "../libs/doruUtilities.h"

//Modules
#include "snake.h"

int screenWidth, screenHeight;
pthread_t tid[2];

void* moving(void *snake) {
	tid[1] = pthread_self();

	int i;
	Coordinate initGameArea, endGameArea;
	struct timespec waitingTime;

	initGameArea.x = 2;
	initGameArea.y = 6;
	endGameArea.x = screenWidth-1;
	endGameArea.y = screenHeight-1;

	waitingTime.tv_sec = 0;
	waitingTime.tv_nsec = 100000000;

	while (1) {
		moveSnake((Queue*)snake);
		clearArea(initGameArea, endGameArea);
		printSnake((Queue*)snake);
		nanosleep(&waitingTime, NULL);
	}

	return NULL;
}

void startGame() {

	int i, threadError, stopGame, event;
	Coordinate initGameArea, endGameArea;
	struct timespec waitingTime;
	Queue *snake;

	initGameArea.x = 2;
	initGameArea.y = 6;
	endGameArea.x = screenWidth-1;
	endGameArea.y = screenHeight-1;

	waitingTime.tv_sec = 0;
	waitingTime.tv_nsec = 100000000;

	snake = newSnake(screenWidth/2 - 2, screenHeight/2);

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
			pthread_cancel(tid[1]);
		}
	}
}

void menu() {
	startGame();
}

int main(int argc, char *argv[]) {
	
	tid[0] = pthread_self();

	if (argc < 3) {
        printf("[ERROR] Too few parameters\n");
        exit(0);
    }

    screenHeight = atoi(argv[1]);
    screenWidth = atoi(argv[2]);
    
    system("clear");
    printScreenBorder(screenWidth, screenHeight);

    menu();

    

	return 0;
}
