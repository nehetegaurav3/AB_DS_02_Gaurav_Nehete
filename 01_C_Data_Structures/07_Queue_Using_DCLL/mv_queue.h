
/*
	@file: mv_queue.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Queue implementation using DCLL Server
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 26 June 2023 (Monday) 09:08 AM
*/


//Conditional Compilation
#ifndef	    _MV_QUEUE_H
#define	    _MV_QUEUE_H	


//Headers
#include    "mv_dcll.h"


//Constant Literals and Macros
#ifndef	    SUCCESS	
#define	    SUCCESS     0
#endif

#ifndef	    FAILURE
#define	    FAILURE     1
#endif


//Typedefs
typedef	    mv_dcll_t		mv_queue_t;
typedef	    p_mv_dcll_t		p_mv_queue_t;
typedef 	pp_mv_dcll_t	pp_mv_queue_t;

typedef	    void (*printdataproc_t)(data_t);

//Interface Functions
/*
    @function: To Create Queue
    @identifier: MVCreateQueue
    @return: Created Queue
*/
extern p_mv_queue_t MVCreateQueue();

/*
    @function: Insert Data At Back of Queue
    @identifier: MVQueueEnQueue
    @params: 1. Queue
             2. Data
    @return: Status
*/
extern status_t MVQueueEnQueue(p_mv_queue_t, data_t);

/*
    @function: Remove Data from Front of Queue
    @identifier: MVQueueDeQueue
    @params: 1. Queue
    @return: Removed Data
*/
extern data_t MVQueueDeQueue(p_mv_queue_t);

/*
    @function: Print Data from Queue
    @identifier: MVQueuePrint
    @params: 1. Queue
			 2. Print Data Proc Callback
*/
extern void MVQueuePrint(p_mv_queue_t, printdataproc_t);

/*
    @function: Destroying the Queue
    @identifier: MVQueueDestroy
    @params: 1. Pointer to Queue
             2. Delete Data Proc Callback
    @return: Status
*/
extern status_t MVQueueDestroy(pp_mv_queue_t, deletedataproc_t);

/*
    @function: Get Data from Queue
    @identifier: MVQueueDataAt
    @params: 1. Queue
             2. Index
    @return: Data
*/
extern data_t MVQueueDataAt(p_mv_queue_t, long long);

/*
    @function: Get Size of Queue
    @identifier: MVQueueSize
    @params: 1. Queue
    @return: Size of Queue
*/
extern size_t MVQueueSize(p_mv_queue_t);

#endif	    //_MV_QUEUE_H
