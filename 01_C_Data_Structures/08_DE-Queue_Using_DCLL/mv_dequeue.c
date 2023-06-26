
/*
    @file: mv_dcll.c
    @brief: Source code file for definitions of Interface functions of Doubly Ended Queue using DCLL Server
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 26 June 2023 (Monday) 06:18 PM    
*/

//  Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_dequeue.h"

// Interface Functions
/*
    @function: To Create DEQueue
    @identifier: MVCreateDEQueue
    @return: Created DEQueue
*/
extern p_mv_dequeue_t MVCreateDEQueue()
{
    //Code
    return(MVCreateDCLL());
}

/*
    @function: Insert Data At Front
    @identifier: MVDEQueueEnQueueFront
    @params: 1. DEQueue
             2. Data
    @return: Status 
*/
extern status_t MVDEQueueEnQueueFront(p_mv_dequeue_t queue, data_t new_data)
{
    //Code
    return(MVDCLLInsertFront(queue, new_data));
}

/*
    @function: Insert Data At Back
    @identifier: MVDEQueueEnQueueBack
    @params: 1. DEQueue
             2. Data
    @return: Status
*/
extern status_t MVDEQueueEnQueueBack(p_mv_dequeue_t queue, data_t new_data)
{
    //Code
    return(MVDCLLInsertBack(queue, new_data));
}

/*
    @function: Remove Data from Front
    @identifier: MVDEQueueDeQueueFront
    @params: 1. DEQueue
    Return: Removed Data
*/
extern data_t MVDEQueueDeQueueFront(p_mv_dequeue_t queue)
{
    //Code
    return(MVDCLLRemoveFront(queue));
}

/*
    @function: Remove Data from Back
    @identifier: MVDEQueueDeQueueBack
    @params: 1. DEQueue
    Return: Removed Data
*/
extern data_t MVDEQueueDeQueueBack(p_mv_dequeue_t queue)
{
    //Code
    return(MVDCLLRemoveBack(queue));
}

/*
    @function: Print Data from Queue
    @identifier: MVDEQueuePrint
    @params: 1. DEQueue
			 2. Print Data Proc Callback
*/
extern void	MVDEQueuePrint(p_mv_dequeue_t queue, printdataproc_t pprintdata)
{
	//Code
	fprintf(stdout, "{START}->");
	for(long long le = 0; le < MVDEQueueSize(queue); ++le)
	{
		fprintf(stdout, "{");
		pprintdata(MVDEQueueDataAt((p_mv_dcll_t)queue, le));
		fprintf(stdout, "}->");
	}
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Destroying the DEQueue
    @identifier: MVDEQueueDestroy
    @params: 1. Pointer to DEQueue
             2. Delete Data Proc Callback
    @return: Status
*/
extern status_t MVDEQueueDestroy(pp_mv_dequeue_t p_queue, deletedataproc_t pdeletedataproc)
{
    //Code
    return(MVDCLLDestroy(p_queue, pdeletedataproc));
}

/*
    @function: Get Data from DEQueue
    @identifier: MVDEQueueDataAt
    @params: 1. DEQueue
             2. Index
    @return: Data
*/
extern data_t MVDEQueueDataAt(p_mv_dequeue_t queue, long long index)
{
    //Code
    return(MVDCLLDataAt(queue, index));
}

/*
    @function: Get Size of DEQueue
    @identifier: MVDEQueueSize
    @params: 1. DEQueue
    @return: Size of DEQueue
*/
extern size_t MVDEQueueSize(p_mv_dequeue_t queue)
{
    //Code
    return(MVDCLLSize(queue));
}
