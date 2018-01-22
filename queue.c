#include <stdlib.h>
#include <memory.h>
#include "queue.h"
#include "errno.h"
#include <pthread.h>

#define QUEUE_LOCK(obj) pthread_mutex_lock(&((obj)->mutex))
#define QUEUE_UNLOCK(obj) pthread_mutex_unlock(&((obj)->mutex))


#define CHECK_PTR_NULL(ptr) if ((ptr) == NULL) {errno=EINVAL;return -1;}
#define CHECK_PTR_NULL2(ptr) if ((ptr) == NULL) {errno=EINVAL;return NULL;}
#define CHECK_PTR_NULL3(ptr) if ((ptr) == NULL) {errno=EINVAL;return ;}

int queue_init(struct queue* queue)
{
	CHECK_PTR_NULL(queue);
	int ret = 0;
	memset(queue, 0, sizeof(struct queue));
	if ( (ret = linklist_init(&queue->list)) < 0) {
		goto out;
	}
	if ( (ret = pthread_mutex_init(&queue->mutex, NULL)) < 0) {
		goto out;
	}
out:
	return ret;
}

void queue_deinit(struct queue* queue, void freefunc(void*))
{
	CHECK_PTR_NULL3(queue);
	int ret = 0;
	linklist_deinit(&queue->list, freefunc);
	if ( (ret = pthread_mutex_destroy(&queue->mutex)) < 0) {
		goto out;
	}
	memset(queue, 0, sizeof(struct queue));
out:
	return ;
}


int queue_push(struct queue* queue, void* data)
{
	CHECK_PTR_NULL(queue);
	CHECK_PTR_NULL(data);
	
	QUEUE_LOCK(queue);
	int ret = 0;
	if ( (ret = linklist_add_tail(&queue->list, data)) < 0) {
		goto out;
	}
out:
	QUEUE_UNLOCK(queue);
	return ret;
}

void* queue_pop(struct queue* queue)
{
	CHECK_PTR_NULL2(queue);
	void* data = NULL;
	QUEUE_LOCK(queue);
	data = linklist_pop_head(&queue->list);
	
	QUEUE_UNLOCK(queue);
	return data;	
}

int queue_get_count(struct queue* queue)
{
	CHECK_PTR_NULL(queue);
	int ret = 0;
	QUEUE_LOCK(queue);
	ret = linklist_get_count(&queue->list);
	QUEUE_UNLOCK(queue);
	return ret;
}

