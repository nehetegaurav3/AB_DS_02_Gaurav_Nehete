/*
    @file: client.c
    @brief: Client side file for Doubly Ended Queue using DCLL usage
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 26 June 2023 (Monday) 07:41 PM 
*/

//Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dequeue.h"

//Global Objects
p_mv_dequeue_t dequeue1 = NULL;

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
	dequeue1 = MVCreateDEQueue();

	for(long long le = 1; le <= 10; ++le)
	{	
		if(le <= 5)
		{
			MVDEQueueEnQueueFront(dequeue1, (data_t)(le * 9));
		}
		else
		{
			MVDEQueueEnQueueBack(dequeue1, (data_t)(le * 6));
		}
	}
	fprintf(stdout, "DEQueue after EnQueue:\n");
	MVDEQueuePrint(dequeue1, print_data);
    fprintf(stdout, "Size of DEQueue = %lld\n\n",(long long)MVDEQueueSize(dequeue1));

	delete_data(MVDEQueueDeQueueFront(dequeue1));
	delete_data(MVDEQueueDeQueueFront(dequeue1));
    delete_data(MVDEQueueDeQueueFront(dequeue1));
    delete_data(MVDEQueueDeQueueBack(dequeue1));
    delete_data(MVDEQueueDeQueueBack(dequeue1));
	delete_data(MVDEQueueDeQueueBack(dequeue1));
	fprintf(stdout, "DEQueue after DeQueue:\n");
	MVDEQueuePrint(dequeue1, print_data);
    fprintf(stdout, "Size of DEQueue = %lld\n\n",(long long)MVDEQueueSize(dequeue1));

	fprintf(stdout, "===== CLEANING THE HEAP MEMORY =====\n\n");
	MVDEQueueDestroy(&dequeue1, delete_data);

	exit(SUCCESS);
}
