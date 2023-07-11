
/*
	@file: mv_stack.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Stack using DCLL Server
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 10 July 2023 (Monday) 02:13 PM 
*/

//Conditional Compilation
#ifndef	_MV_STACK_H
#define	_MV_STACK_H

//Headers
#include    "mv_dcll.h"

//Constant Literals
typedef		p_mv_dcll_t		p_mv_stack_t;
typedef		pp_mv_dcll_t	pp_mv_stack_t;

typedef	    void (*printdataproc_t)(data_t);

//Interface Funtions
/*
    @function: To Create Stack
    @identifier: MVCreateStack
    @return: Created Stack
*/
extern p_mv_stack_t MVCreateStack();

/*
    @function: Add Data in Stack(PUSH)
    @identifier: MVStackPush
    @params: 1. Stack
             2. Data
    @return: Status 
*/
extern status_t MVStackPush(p_mv_stack_t, data_t);

/*
    @function: Remove Data from Stack(POP)
    @identifier: MVStackPop
    @params: 1. Stack
    Return: Removed Data
*/
extern data_t MVStackPop(p_mv_stack_t);

/*
    @function: Get Data from Stack
    @identifier: MVStackPeek
    @params: 1. Stack
    @return: Data
*/
extern data_t MVStackPeek(p_mv_stack_t);

/*
    @function: Get Size of Stack
    @identifier: MVStackSize
    @params: 1. Stack
    @return: Size of Stack
*/
extern long long MVStackSize(p_mv_stack_t);

/*
    @function: Print Data from Stack
    @identifier: MVStackPrint
    @params: 1. Stack
			 2. Print Data Proc Callback
*/
extern void MVStackPrint(p_mv_stack_t, printdataproc_t);

/*
    @function: Destroying the Stack
    @identifier: MVStackDestroy
    @params: 1. Pointer to Stack
             2. Delete Data Proc Callback
    @return: Status
*/
extern status_t MVStackDestroy(pp_mv_stack_t, deletedataproc_t);

#endif		// _MV_STACK_H
