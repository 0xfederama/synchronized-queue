#ifndef FIFOQ_H
#define FIFOQ_H

#include <pthread.h>

//Support struct
typedef struct node {
	void *info;			//Void pointer to use the queue with everything
	struct node *next;	//Pointer to the following element of the queue
} node;

//Queue struct
typedef struct queue {
	size_t size;		//Queue dimension
	struct node *first; 	//Pointer to the first element of the queue
	struct node *last;		//Pointer to the last element of the queue
	pthread_mutex_t lock;	//Mutex semaphore within the queue
	pthread_cond_t cond;	//Condition variable within the queue
} queue;

/**
 * Creates and initializes a new queue
 * \returns queue - if everything is ok
 * \returns NULL  - if errors occurred
 */
queue *initQueue ();

/**
 * Creates a new element and pushes it to the tail of the queue
 * \returns 0 - if everything is ok
 * \returns 1 - if errors occurred
 */
int push (queue *q, void *data);

/**
 * Removes the head of the queue
 * \returns head's info - if everything is ok
 * \returns NULL - if the queue is empty
 */
void* pop (queue *q);

/**
 * Returns the size of the queue
 * \returns queue size - if everything ok
 * \returns -1 - if errors occurred
 */
size_t getSize (queue *q);

// Deletes and frees the queue
void deleteQueue (queue *q);

#endif