//ANSI C libs
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Custom libs
#include "../libs/doruUtilities.h"

//Modules
#include "snake.h"

int screenWidth, screenHeight;



void startGame() {
	char event;
	int i;
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
	printSnake(snake);
	clearArea(initGameArea, endGameArea);
	
	for (i=0; i<20; i++) {
		moveSnake(snake);
		clearArea(initGameArea, endGameArea);
		printSnake(snake);
		nanosleep(&waitingTime, NULL);
	}
	turnSnake(snake, DOWN);
	for (i=0; i<5; i++) {
		moveSnake(snake);
		clearArea(initGameArea, endGameArea);
		printSnake(snake);
		nanosleep(&waitingTime, NULL);
	}
	
	turnSnake(snake, LEFT);
	for (i=0; i<20; i++) {
		moveSnake(snake);
		clearArea(initGameArea, endGameArea);
		printSnake(snake);
		nanosleep(&waitingTime, NULL);
	}
	turnSnake(snake, UP);
	for (i=0; i<10; i++) {
		moveSnake(snake);
		clearArea(initGameArea, endGameArea);
		printSnake(snake);
		nanosleep(&waitingTime, NULL);
	}
	

	fflush(stdin);
	event = getchar();
    printf("%i", event);
}

void menu() {
	startGame();
}

int main(int argc, char *argv[]) {
	
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
