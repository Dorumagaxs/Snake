//ANSI C libs
#include <stdlib.h>
#include <stdio.h>

//Custom libs
#include "../libs/doruUtilities.h"

//Modules
#include "snake.h"

int screenWidth, screenHeight;

void printScreenBorder(int width, int height) {
    char line[width+1];
    char noline[width+1];
    int i;


    line[0] = '|';
    noline[0] = '|';
    line[width-1] = '|';
    noline[width-1] = '|';
    line[width] = 0;
    noline[width] = 0;

    for (i=1; i<width-1; i++) {
    	line[i] = '-';
    	noline[i] = ' ';
    }

    gotoxy(1,1);
    printf("%s", line);

    for (i=2; i<5; i++) {
    	gotoxy(1,i);
    	printf("%s", noline);
    }

    gotoxy(1,5);
    printf("%s", line);

    for (i=6; i<height; i++) {
    	gotoxy(1,i);
    	printf("%s", noline);
    }
}

void initGame() {
	char event;

	Queue *snake = newSnake(screenWidth/2 - 2, screenHeight/2);
	printSnake(snake);

	event = getchar();
    printf("%i", event);
}

void menu() {
	initGame();
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
