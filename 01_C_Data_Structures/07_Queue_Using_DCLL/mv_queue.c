
/*
    @file: mv_queue.c
    @brief: Source code file for definitions of Interface functions of Queue using DCLL Server.
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 26 June 2023 (Monday) 09:22 AM    
*/


//Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_queue.h"


//Interface Functions
/*
    @function: To Create Queue
    @identifier: MVCreateQueue
    @return: Created Queue
*/
extern p_mv_queue_t MVCreateQueue()
{
    //Code
    return(MVCreateDCLL());
}

/*
    @function: Insert Data At Back of Queue
    @identifier: MVQueueEnQueue
    @params: 1. Queue
             2. Data
    @return: Status
*/
extern status_t MVQueueEnQueue(p_mv_queue_t queue, data_t new_data)
{
    //Code
    return(MVDCLLInsertBack(queue, new_data));
}

/*
    @function: Remove Data from Front of Queue
    @identifier: MVQueueDeQueue
    @params: 1. Queue
    @return: Removed Data
*/
extern data_t MVQueueDeQueue(p_mv_queue_t queue)
{
    //Code
    return(MVDCLLRemoveFront(queue));
}

/*
    @function: Print Data from Queue
    @identifier: MVQueuePrint
    @params: 1. Queue
			 2. Print Data Proc Callback
*/
extern void	MVQueuePrint(p_mv_queue_t queue, printdataproc_t pprintdata)
{
	//Code
	fprintf(stdout, "{START}->");
	for(long long le = 0; le < MVQueueSize(queue); ++le)
	{
		fprintf(stdout, "{");
		pprintdata(MVQueueDataAt((p_mv_dcll_t)queue, le));
		fprintf(stdout, "}->");
	}
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Destroying the Queue
    @identifier: MVQueueDestroy
    @params: 1. Pointer to Queue
             2. Delete Data Proc Callback
    @return: Status
*/
extern status_t MVQueueDestroy(pp_mv_queue_t p_queue, deletedataproc_t pdeletedataproc)
{
    //Code
    return(MVDCLLDestroy(p_queue, pdeletedataproc));
}

/*
    @function: Get Data from Queue
    @identifier: MVQueueDataAt
    @params: 1. Queue
             2. Index
    @return: Data
*/
extern data_t MVQueueDataAt(p_mv_queue_t queue, long long index)
{
    //Code
    return(MVDCLLDataAt(queue, index));
}

/*
    @function: Get Size of Queue
    @identifier: MVQueueSize
    @params: 1. Queue
    @return: Size of Queue
*/
extern size_t MVQueueSize(p_mv_queue_t queue)
{
    //Code
    return(MVDCLLSize(queue));
}
