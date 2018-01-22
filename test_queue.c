#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct data{
	int d1;
	int d2;
};

void freedata(void* data)
{
	free(data);
	return;
}

int main()
{
	int i = 0;
	struct queue queue = {0};
	queue_init(&queue);
	for (i = 0; i < 800; ++i) {
		struct data *da = (struct data*)malloc(sizeof(struct data));
		da->d1 = i;
		da->d2 = i;
		queue_push(&queue, da);
	}
	
	struct data * data = NULL;
	while(queue_get_count(&queue) > 0) {
		data = queue_pop(&queue);
		printf("%d %d\r\n", data->d1, data->d2);
		free(data);
	}
	queue_deinit(&queue, freedata);
	return 0;
}

