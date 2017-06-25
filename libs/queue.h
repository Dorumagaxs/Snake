#define NO_MEMORY_ERROR "[ERROR] No enough memory available"

typedef struct Node {
	void *value;
	struct Node *next;
} Node;

typedef struct Queue {
	int size;
	Node *first, *last;
} Queue;

Queue* newQueue() {
	Queue *queue = (Queue*) malloc(sizeof(Queue));

	if (queue == NULL) {
		printf("%s", NO_MEMORY_ERROR);
		exit(0);
	}

	queue->first = NULL;
	queue->last = NULL;
	queue->size = 0;

	return queue;
}

void enqueue(Queue *queue, void *value) {
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

	queue->last->value = value;
	queue->last->next = NULL;

	queue->size++;
}

void* dequeue(Queue *queue) {
	void *dequeuedValue = NULL;
	Node *toBeDeleted;

	if (queue->size > 0) {
		toBeDeleted = queue->first;

		dequeuedValue = toBeDeleted->value;

		queue->first = toBeDeleted->next;

		toBeDeleted->next = NULL;
		free(toBeDeleted);

		queue->size--;
	}

	return dequeuedValue;
}

void* getValue(Queue *queue, unsigned int index) {
	Node *wantedValue = NULL;

	if ( (index >= 0)&&(index < queue->size) ) {
		int i;
		Node *wantedNode = queue->first;

		for (i=0; i<index; i++)
			wantedNode = wantedNode->next;

		wantedValue = wantedNode->value;
	}

	return wantedValue;
}