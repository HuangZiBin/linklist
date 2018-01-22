#include <stdio.h>
#include <stdlib.h>
#include "LinkList.h"

struct data{
	int d1;
	int d2;
};

void freedata(void* data)
{
	free(data);
	return ;
}

int main()
{
	int i = 0;
	struct LinkList list = {0};
	linklist_init(&list);
	for (i = 0; i < 800; ++i) {
		struct data *da = (struct data*)malloc(sizeof(struct data));
		da->d1 = i;
		da->d2 = i;
		linklist_add_tail(&list, da);
	}

	void* iterator = linklist_get_iterator(&list);
	while(linklist_iterator_finish(iterator) == 0) {
		struct data* _da = (struct data*)linklist_get_data(&list, iterator);
		printf("%d %d\r\n", _da->d1, _da->d2);
		linklist_next(&list, &iterator);
		if (linklist_iterator_at_start(&list, iterator) > 0) {
			break;
		}
	}
	iterator = linklist_get_iterator(&list);
	while(linklist_iterator_finish(iterator) == 0) {
		struct data *da = (struct data*)linklist_pop(&list, &iterator);
		free(da);
	}
	linklist_deinit(&list, freedata);
	return 0;
}

