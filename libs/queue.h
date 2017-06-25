#define NO_MEMORY_ERROR "[ERROR] No enough memory available"

typedef struct Point {
	int x, y;
} Point;

typedef struct Node {
	Point value;
	Node *next;
}

typedef struct Queue {
	int size;
	Node *first;
} Queue;

Queue* newQueue() {
	Queue queue;
	queue.first = NULL;
	queue.last = NULL;
	queue.size = 0;
}

void enqueue(Queue *queue, Point value) {
	if (queue->size == 0) {
		queue->first = (Node*) malloc(sizeof(Node));
		if (queue->first == NULL) {
			printf("%s", NO_MEMORY_ERROR);
			exit(0);
		}

		queue->last = queue->first;
	}
	else {
		queue->last->next = (Node*) malloc(sizeof(Node));
		if (queue->last->next == NULL) {
			printf("%s", NO_MEMORY_ERROR);
			exit(0);
		}

		queue->last = queue->last->next;
	}

	queue->first->value = value;
	queue->first->next = NULL;

	queue->size++;
}

Point dequeue(Queue *queue) {
	Point dequeuedValue = {0,0};

	if (queue->size > 0) {
		dequeuedValue = queue->last->value;

		free(queue->last);
		queue->last = NULL;

		size--;
	}

	return dequeuedValue;
}