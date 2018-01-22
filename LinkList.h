/********************************************************************************
**	COPYRIGHT (c) 2016 huangzibin
**	author        :  hzb <hzbhlz@163.com>
**	date           :  2016.06.17
**	description  : 双向循环链表的封装。
					出错时由errno指出错误
					使用方法：
						使用前先把队列先清0；
						调用linklist_init；
						如在多线程下使用，需自行上锁（因原子操作跨接口，不可能在内部上锁）
********************************************************************************/

#ifndef LINKLIST_H
#define LINKLIST_H


struct LinkListNode {
	void* data;
	struct LinkListNode* next;
	struct LinkListNode* prev;
};

struct LinkList {
	int count;
	struct LinkListNode* head;
};

int linklist_init(struct LinkList* list);
void* linklist_get_iterator(struct LinkList* list);
int linklist_iterator_finish(void* iterator);
int linklist_iterator_at_start(struct LinkList* list, void* iterator);
int linklist_next(struct LinkList* list, void** iterator);
void* linklist_get_data(struct LinkList* list, void* iterator);
int linklist_add_tail(struct LinkList* list, void* data);
void* linklist_pop(struct LinkList* list, void** iterator);
void* linklist_pop_head(struct LinkList* list);
int linklist_get_count(struct LinkList* list);
void linklist_deinit(struct LinkList *list, void func(void*));

#endif
