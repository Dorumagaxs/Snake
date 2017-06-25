#define NO_MEMORY_ERROR "[ERROR] No enough memory available"

typedef struct Node {
	void *value;
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

	queue->first->value = value;
	queue->first->next = NULL;

	queue->size++;
}

void* dequeue(Queue *queue) {
	void *dequeuedValue = NULL;

	if (queue->size > 0) {
		dequeuedValue = queue->last->value;

		free(queue->last);
		queue->last = NULL;

		size--;
	}

	return dequeuedValue;
}

void* getValue(Queue *queue, unsigned int index) {
	Node *wantedValue = NULL;

	if ( (index > 0)&&(index < queue->size) ) {
		int i;
		Node *wantedNode = queue->first;

		for (i=0; i<index; i++)
			wantedNode = wantedNode->next;

		wantedValue = wantedNode->value;
	}

	return wantedValue;
}