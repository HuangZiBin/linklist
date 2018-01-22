/********************************************************************************
**	COPYRIGHT (c) 2016 huangzibin
**	author        :  hzb <635568706@qq.com>
**	date           :  2016.08.24
**	description  : thread-safe
********************************************************************************/

#ifndef H_QUEUE_H
#define H_QUEUE_H
#include "linklist.h"
#include <pthread.h>
struct queue {
	struct LinkList list;
	pthread_mutex_t mutex;
};

int queue_init(struct queue* queue);
void queue_deinit(struct queue* queue, void freefunc(void*));
int queue_push(struct queue* queue, void* data);
void* queue_pop(struct queue* queue);
int queue_get_count(struct queue* queue);



#endif
