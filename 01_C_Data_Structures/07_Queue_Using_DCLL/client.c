/*
    @file: client.c
    @brief: Client side file for Queue using DCLL usage
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 26 June 2023 (Monday) 09:55 AM     
*/

//Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_queue.h"

//Global Objects
p_mv_queue_t queue1 = NULL;

void delete_data(data_t data)
{
	fprintf(stdout, "Deleting Data = %lld\n", (long long)data);
}

void print_data(data_t data)
{
	fprintf(stdout, " %lld ", (long long)data);
}

int main(void)
{
	//Code
	queue1 = MVCreateQueue();

	for(long long le = 1; le <= 10; ++le)
	{
		MVQueueEnQueue(queue1, (data_t)(le * 9));
	}
	fprintf(stdout, "Queue after EnQueue:\n");
	MVQueuePrint(queue1, print_data);
    fprintf(stdout, "Size of Queue = %lld\n\n",(long long)MVQueueSize(queue1));

	delete_data(MVQueueDeQueue(queue1));
	delete_data(MVQueueDeQueue(queue1));
    delete_data(MVQueueDeQueue(queue1));
    delete_data(MVQueueDeQueue(queue1));
    delete_data(MVQueueDeQueue(queue1));
	fprintf(stdout, "Queue after DeQueue:\n");
	MVQueuePrint(queue1, print_data);
    fprintf(stdout, "Size of Queue = %lld\n\n",(long long)MVQueueSize(queue1));

	fprintf(stdout, "===== CLEANING THE HEAP MEMORY =====\n\n");
	MVQueueDestroy(&queue1, delete_data);

	exit(SUCCESS);
}
