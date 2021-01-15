#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include "fifoQ.h"

queue* initQueue () {
	queue *q=malloc(sizeof(queue));
	if (!q) return NULL;
	q->first=malloc(sizeof(node));
	if (!q->first) return NULL;
	q->first->info = NULL; 
    q->first->next = NULL;
    q->last = q->first; 
	q->size=0;
	if (pthread_mutex_init(&q->lock, NULL) != 0) {
		perror("Error inizializing mutex in queue");
		free(q);
		free(q->first);
		return NULL;
    }
    if (pthread_cond_init(&q->cond, NULL) != 0) {
		perror("Error initializing varcond in queue");
		if (&q->lock) pthread_mutex_destroy(&q->lock);
		free(q);
		free(q->first);
		return NULL;
    }
	return q;
}

int push (queue*q, void *data) {
	node *ins=malloc(sizeof(node));
	if (!q || !data || !ins) return -1;
	ins->info=data;
	ins->next=NULL;
	pthread_mutex_lock(&q->lock);
	if (q->size==0) {
		q->first->next=ins;
		q->last=ins;
	} else {
		q->last->next=ins;
		q->last=ins;
	}
	(q->size)++;
	pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->lock);
	return 0;
}

void* pop (queue*q) {
	if (q==NULL) return NULL;
	pthread_mutex_lock(&q->lock);
	while (q->size == 0) {
		pthread_cond_wait(&q->cond, &q->lock);
	}
	assert(q->first->next);
	node*n=(node*)q->first;
	void*data=(q->first->next)->info;
	q->first=q->first->next;
	(q->size)--;
	assert(q->size>=0);
	pthread_mutex_unlock(&q->lock);
	free(n);
	return data;
}

size_t getSize (queue*q) {
	if (q==NULL) return -1;
	size_t size=-1;
	pthread_mutex_lock(&q->lock);
	size=q->size;
	pthread_mutex_unlock(&q->lock);
	return size;
}

void deleteQueue (queue*q) {
	while (q->first != q->last) {
		node *killer=(node*)q->first;
		q->first=q->first->next;
		free(killer);
	}
	if (q->first) free(q->first);
	if (&q->lock) pthread_mutex_destroy(&q->lock);
    if (&q->cond) pthread_cond_destroy(&q->cond);
    free(q);
}
