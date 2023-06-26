
/*
	@file: mv_dequeue.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Doubly Ended Queue using DCLL Server
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 26 June 2023 (Monday) 05:53 PM
*/


//Conditional Compilation
#ifndef	    _MV_DEQUEUE_H
#define	    _MV_DEQUEUE_H	


//Headers
#include    "mv_dcll.h"


//Constant Literals and Macros
#ifndef 	SUCCESS	
#define	    SUCCESS     0
#endif

#ifndef 	FAILURE
#define	    FAILURE     1
#endif


//Typedefs
typedef	    mv_dcll_t		mv_queue_t;
typedef	    p_mv_dcll_t		p_mv_dequeue_t;
typedef	    pp_mv_dcll_t	pp_mv_dequeue_t;

typedef	    void (*printdataproc_t)(data_t);

//Interface Function Declarations
/*
    @function: To Create DEQueue
    @identifier: MVCreateDEQueue
    @return: Created DEQueue
*/
extern p_mv_dequeue_t MVCreateDEQueue();

/*
    @function: Insert Data At Front
    @identifier: MVDEQueueEnQueueFront
    @params: 1. DEQueue
             2. Data
    @return: Status 
*/
extern status_t MVDEQueueEnQueueFront(p_mv_dequeue_t, data_t);

/*
    @function: Insert Data At Back
    @identifier: MVDEQueueEnQueueBack
    @params: 1. DEQueue
             2. Data
    @return: Status
*/
extern status_t MVDEQueueEnQueueBack(p_mv_dequeue_t, data_t);

/*
    @function: Remove Data from Front
    @identifier: MVDEQueueDeQueueFront
    @params: 1. DEQueue
    Return: Removed Data
*/
extern data_t MVDEQueueDeQueueFront(p_mv_dequeue_t);

/*
    @function: Remove Data from Back
    @identifier: MVDEQueueDeQueueBack
    @params: 1. DEQueue
    Return: Removed Data
*/
extern data_t MVDEQueueDeQueueBack(p_mv_dequeue_t);

/*
    @function: Print Data from Queue
    @identifier: MVDEQueuePrint
    @params: 1. Queue
			 2. Print Data Proc Callback
*/
extern void	MVDEQueuePrint(p_mv_dequeue_t, printdataproc_t);

/*
    @function: Destroying the DEQueue
    @identifier: MVDEQueueDestroy
    @params: 1. Pointer to DEQueue
             2. Delete Data Proc Callback
    @return: Status
*/
extern status_t MVDEQueueDestroy(pp_mv_dequeue_t, deletedataproc_t);

/*
    @function: Get Data from DEQueue
    @identifier: MVDEQueueDataAt
    @params: 1. DEQueue
             2. Index
    @return: Data
*/
extern data_t MVDEQueueDataAt(p_mv_dequeue_t, long long);

/*
    @function: Get Size of DEQueue
    @identifier: MVDEQueueSize
    @params: 1. DEQueue
    @return: Size of DEQueue
*/
extern size_t MVDEQueueSize(p_mv_dequeue_t);

#endif	    // _MV_DEQUEUE_H
