#include "../libs/queue.h"

typedef enum{UP, DOWN, LEFT, RIGHT} Direction;

typedef struct SnakePoint {
	int x, y;
	Direction direction;
} SnakePoint;

SnakePoint* newSnakePoint(int x, int y, Direction direction) {
	SnakePoint *newSnakePoint = (SnakePoint*) malloc(sizeof(SnakePoint));

	if (newSnakePoint == NULL) {
		printf("%s", NO_MEMORY_ERROR);
		exit(0);
	}

	newSnakePoint->x = x;
	newSnakePoint->y = y;
	newSnakePoint->direction = direction;

	return newSnakePoint;
}

Queue* newSnake(int x, int y) {
	int i;
	Queue *snake = newQueue();

	for (i=2; i>=-2; i--)
		enqueue(snake, newSnakePoint(x+i, y, RIGHT));

	return snake;
}

void clearSnake(Queue *snake) {
	int i;
	SnakePoint *snakePoint;

	for (i=0; i<snake->size; i++) {
		snakePoint = (SnakePoint*) getValue(snake, i);
		gotoxy(snakePoint->x, snakePoint->y);
		printf(" ");
		fflush(stdout);
	}
}

void printSnake(Queue *snake) {
	int i;
	SnakePoint *snakePoint;

	snakePoint = (SnakePoint*) getValue(snake, 0);
	gotoxy(snakePoint->x, snakePoint->y);
	printf("@");

	for (i=1; i<snake->size; i++) {
		snakePoint = (SnakePoint*) getValue(snake, i);
		gotoxy(snakePoint->x, snakePoint->y);
		printf("¤");
		fflush(stdout);
	}
}

void moveSnake(Queue *snake) {
	int i;
	SnakePoint *snakePoint;

	for (i=(snake->size-1); i>=0; i--) {
		snakePoint = (SnakePoint*) getValue(snake, i);

		if (snakePoint->direction == RIGHT)
			snakePoint->x++;
		else if (snakePoint->direction == LEFT)
			snakePoint->x--;
		else if (snakePoint->direction == DOWN)
			snakePoint->y++;
		else if (snakePoint->direction == UP)
			snakePoint->y--;

		if (i > 0) {
			SnakePoint *nextSnakePoint;
			nextSnakePoint = (SnakePoint*) getValue(snake, i-1);

			snakePoint->direction = nextSnakePoint->direction;
		}
	}
}

void turnSnake(Queue *snake, Direction direction) {
	SnakePoint *snakeHead;

	snakeHead = (SnakePoint*) getValue(snake, 0);
	snakeHead->direction = direction;
}

Coordinate generateFood(Queue *snake, Coordinate initGameArea, Coordinate endGameArea) {
	int i, isValidCoordinateForFood;
	Coordinate food, *snakeCoordinates;

	snakeCoordinates = (Coordinate*) malloc(snake->size * sizeof(Coordinate));

	for (i=0; i<snake->size; i++) {
		snakeCoordinates[i].x = ( (SnakePoint*)getValue(snake, i) )->x;
		snakeCoordinates[i].y = ( (SnakePoint*)getValue(snake, i) )->y;
	}

	isValidCoordinateForFood = 1;
	do {
		food.x = (rand() % (endGameArea.x - initGameArea.x + 1)) + initGameArea.x;
		food.y = (rand() % (endGameArea.y - initGameArea.y + 1)) + initGameArea.y;

		for (i=0; i<snake->size; i++) {
			if ( (food.x == snakeCoordinates[i].x)&&(food.y == snakeCoordinates[i].y) ) {
				isValidCoordinateForFood = 0;
				i = snake->size;
			}
		}
	} while(!isValidCoordinateForFood);
	
	return food;
}

void printFood(Coordinate food) {
	gotoxy(food.x, food.y);
	printf("*");
}

int ateFood(SnakePoint *snakeHead, Coordinate food) {
	return (snakeHead->x == food.x)&&(snakeHead->y == food.y);
}

int isCollidingWithSnake(Queue *snake) {
    int i, collision;
    SnakePoint *snakeHead, *snakeBodyPoint;

    collision = 0;
    snakeHead = (SnakePoint*) getValue(snake, 0);
    for (i=1; i<snake->size; i++) {
        snakeBodyPoint = (SnakePoint*) getValue(snake, i);

        collision = (
            (snakeHead->x == snakeBodyPoint->x)&&
            (snakeHead->y == snakeBodyPoint->y)
        );

        if (collision)
            i = snake->size;
    }

    return collision;
}

int isCollidingWithBorders(SnakePoint *snakeHead, Coordinate initGameArea, Coordinate endGameArea) {
	return ( 
    	(snakeHead->x == initGameArea.x-1)||(snakeHead->x == endGameArea.x+1)||
        (snakeHead->y == initGameArea.y-1)||(snakeHead->y == endGameArea.y+1) 
    );
    
}

int isColliding(Queue *snake, Coordinate initGameArea, Coordinate endGameArea) {
    return (
        isCollidingWithBorders((SnakePoint*) getValue(snake, 0), initGameArea, endGameArea)||
        isCollidingWithSnake(snake)
    );
}

void feedSnake(Queue *snake) {
	SnakePoint *newSnakePoint, *lastSnakePoint;

	newSnakePoint = (SnakePoint*) malloc(sizeof(SnakePoint));
	lastSnakePoint = ( (SnakePoint*) getValue(snake, snake->size-1) );

	newSnakePoint->direction = lastSnakePoint->direction;

	if (newSnakePoint->direction == RIGHT) {
		newSnakePoint->x = lastSnakePoint->x-1;
		newSnakePoint->y = lastSnakePoint->y;
	}
	else if (newSnakePoint->direction == LEFT) {
		newSnakePoint->x = lastSnakePoint->x+1;
		newSnakePoint->y = lastSnakePoint->y;
	}
	else if (newSnakePoint->direction == UP) {
		newSnakePoint->x = lastSnakePoint->x;
		newSnakePoint->y = lastSnakePoint->y+1;
	}
	else if (newSnakePoint->direction == DOWN) {
		newSnakePoint->x = lastSnakePoint->x;
		newSnakePoint->y = lastSnakePoint->y-1;
	}

	enqueue(snake, newSnakePoint);
}
