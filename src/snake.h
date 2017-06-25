#include "../libs/pointQueue.h"

typedef enum{UP, DOWN, LEFT, RIGHT} Direction;

typedef struct SnakePoint {
	int x, y;
	Direction direction;
} SnakePoint;

typedef struct Snake {
	Direction direction;
	Queue *body;
} Snake;

Queue* newSnake() {
	Queue *snake = newQueue();

	return snake;
}

void feedSnake(Queue *snake) {
	SnakePoint *newSnakePoint, lastSnakePoint;

	newSnakePoint = (SnakePoint*) malloc(sizeof(SnakePoint));
	lastSnakePoint = ( (SnakePoint*)getValue(snake, snake->size-1) );

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