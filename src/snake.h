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

void printSnake(Queue *snake) {
	int i;
	SnakePoint *snakePoint;

	snakePoint = (SnakePoint*) getValue(snake, 0);
	gotoxy(snakePoint->x, snakePoint->y);
	printf("@");

	for (i=1; i<snake->size; i++) {
		snakePoint = (SnakePoint*) getValue(snake, i);
		gotoxy(snakePoint->x, snakePoint->y);
		printf("#");
		fflush(stdout);
	}
}

void moveSnake(Queue *snake) {
	FILE *f = fopen("../logs/snakePointsDirections", "a");
	if (f == NULL) {
		printf("[ERROR] Could not open file");
		exit(0);
	}
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

			fprintf(f, "Element %i has direction %d -> Element %i has direction %d\n", i, snakePoint->direction, i-1, nextSnakePoint->direction);
			snakePoint->direction = nextSnakePoint->direction;
		}
	}

	fclose(f);
}

void turnSnake(Queue *snake, Direction direction) {
	SnakePoint *snakeHead;

	snakeHead = (SnakePoint*) getValue(snake, 0);
	snakeHead->direction = direction;
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
		newSnakePoint->y = lastSnakePoint->y-1;
	}
	else if (newSnakePoint->direction == DOWN) {
		newSnakePoint->x = lastSnakePoint->x;
		newSnakePoint->y = lastSnakePoint->y-1;
	}

	enqueue(snake, newSnakePoint);
}