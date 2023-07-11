
/*
    @file: mv_stack.c
    @brief: Source code file for definitions of Interface functions of Stack Server using DCLL
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 10 July 2023 (Monday) 2:30 PM 
*/

//Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dcll.h"
#include	"mv_stack.h"

//Interface Functions
/*
    @function: To Create Stack
    @identifier: MVCreateStack
    @return: Created Stack
*/
extern p_mv_stack_t MVCreateStack()
{
	//Code
	return(MVCreateDCLL());
}

/*
    @function: Add Data in Stack(PUSH)
    @identifier: MVStackPush
    @params: 1. Stack
             2. Data
    @return: Status 
*/
extern status_t MVStackPush(p_mv_stack_t stack, data_t new_data)
{
	//Code
	return(MVDCLLInsertBack(stack, new_data));
}

/*
    @function: Remove Data from Stack(POP)
    @identifier: MVStackPop
    @params: 1. Stack
    Return: Removed Data
*/
extern data_t MVStackPop(p_mv_stack_t stack)
{
	//Code
	return(MVDCLLRemoveBack(stack));
}

/*
    @function: Get Data from Stack
    @identifier: MVStackPeek
    @params: 1. Stack
    @return: Data
*/
extern data_t MVStackPeek(p_mv_stack_t stack)
{
	//Code
	return(MVDCLLDataAt(stack, (long long)MVDCLLSize(stack)-1));
}

/*
    @function: Print Data from Stack
    @identifier: MVStackPrint
    @params: 1. Stack
			 2. Print Data Proc Callback
*/
extern void	MVStackPrint(p_mv_stack_t stack, printdataproc_t pprintdata)
{
	//Code
	fprintf(stdout, "{START}->");
	for(long long le = 0; le < MVDCLLSize(stack); ++le)
	{
		fprintf(stdout, "{");
		pprintdata(MVDCLLDataAt((p_mv_dcll_t)stack, le));
		fprintf(stdout, "}->");
	}
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Destroying the Stack
    @identifier: MVStackDestroy
    @params: 1. Pointer to Stack
             2. Delete Data Proc Callback
    @return: Status
*/
extern status_t MVStackDestroy(pp_mv_stack_t pstack, deletedataproc_t pdeletedataproc)
{
	//Code
	return(MVDCLLDestroy(pstack, pdeletedataproc));
}
