#include <stdlib.h>
#include <memory.h>
#include "LinkList.h"
#include "errno.h"


#define CHECK_PTR_NULL(ptr) if ((ptr) == NULL) {errno=EINVAL;return -1;}
#define CHECK_PTR_NULL2(ptr) if ((ptr) == NULL) {errno=EINVAL;return NULL;}
#define CHECK_PTR_NULL3(ptr) if ((ptr) == NULL) {errno=EINVAL;return ;}

int linklist_init(struct LinkList* list)
{
	CHECK_PTR_NULL(list);
	memset(list, 0, sizeof(struct LinkList));
	return 0;
}

void* linklist_get_iterator(struct LinkList* list)
{
	CHECK_PTR_NULL2(list);
	return list->head;
}


int linklist_iterator_finish(void* iterator)
{
	struct LinkListNode* node = (struct LinkListNode*)iterator;
	if (node == NULL)
		return 1;
	else
		return 0;		
}

int linklist_iterator_at_start(struct LinkList* list, void* iterator)
{
	struct LinkListNode* node = (struct LinkListNode*)iterator;
	if (node == list->head)
		return 1;
	else
		return 0;
}

int linklist_next(struct LinkList* list, void** iterator)
{
	CHECK_PTR_NULL(list);
	CHECK_PTR_NULL(iterator);

	struct LinkListNode* node = (struct LinkListNode*)*iterator;
	if (node == NULL)
		return 0;
	struct LinkListNode* next = node->next;
	*iterator = next;
	return 0;
}

void* linklist_get_data(struct LinkList* list, void* iterator)
{
	CHECK_PTR_NULL2(list);

	struct LinkListNode* node = (struct LinkListNode*)iterator;
	if (node == NULL)
		return 0;
	return node->data;
}

int linklist_add_tail(struct LinkList* list, void* data)
{
	CHECK_PTR_NULL(list);
	CHECK_PTR_NULL(data);
	struct LinkListNode* node = (struct LinkListNode*)calloc(1, sizeof(struct LinkListNode));
	if (!node) {		
		errno=ENOMEM;
		return -1;
	}
	node->data = data;
	if (list->head == NULL) {
		node->next = node->prev = node;
		list->head = node;
	}
	else if(list->head->next == list->head) {
		list->head->next = list->head->prev = node;
		node->next = node->prev = list->head;
	}
	else {
		struct LinkListNode* tail = list->head->prev;
		node->next = list->head;
		node->prev = tail;
		tail->next = node;
		list->head->prev = node;
	}
	list->count++;
	return 0;
}

void* linklist_pop(struct LinkList* list, void** iterator)
{
	CHECK_PTR_NULL2(list);
	CHECK_PTR_NULL2(iterator);

	struct LinkListNode* node = (struct LinkListNode*)*iterator;
	if (node == NULL)
		return NULL;
	
	void *pridata = node->data;

	if(list->head == list->head->next) {
		free(node);
		list->head = NULL;
		list->count = 0;
		*iterator = NULL;
		return pridata;
	}

	struct LinkListNode* prev = node->prev;
	struct LinkListNode* next = node->next;

	prev->next = next;
	next->prev = prev;
	
	if (node == list->head)
		list->head = next;
	free(node);
	list->count--;
	*iterator = next;
	return pridata;
}

void* linklist_pop_head(struct LinkList* list)
{
	CHECK_PTR_NULL2(list);
	void* data = NULL;
	void* iterator = linklist_get_iterator(list);
	if (linklist_iterator_finish(iterator) > 0) {
		data = NULL;
		return data;
	}
	data = linklist_pop(list, &iterator);
	return data;
}

int linklist_get_count(struct LinkList* list)
{
	CHECK_PTR_NULL(list);
	return list->count;
}

void linklist_deinit(struct LinkList *list, void freefunc(void*))
{
	CHECK_PTR_NULL3(list);
	void* iterator = linklist_get_iterator(list);
	while(linklist_iterator_finish(iterator) == 0) {
		void *da = linklist_pop(list, &iterator);
		if (freefunc)
			freefunc(da);
	}
	return ;
}

