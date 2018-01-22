linklist:linklist.c linklist.h test_linklist.c output_dir
	gcc linklist.c linklist.h test_linklist.c  -o $@ -Wall 
	mv $@ output_dir/

QUEUE_SRC=queue.c queue.h linklist.c test_queue.c
QUEUE_OBJ=$(patsubst %.c,%.o,$(wildcard $(QUEUE_SRC)))
queue: $(QUEUE_OBJ) output_dir
	gcc $(QUEUE_OBJ) -o $@ -Wall 
	mv $@ output_dir/

output_dir:
	mkdir output_dir

clean:
	rm output_dir -rf; rm *.o
