
/*
    @file: client.c
    @brief: Client side file for Stack using DCLL usage
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 25 June 2023 (Sunday) 01:05 PM     
*/

//Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_stack.h"

//Global Objects
p_mv_stack_t stack = NULL;

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
	stack = MVCreateStack();

	for(long long le = 1; le <= 15; ++le)
	{
		MVStackPush(stack, (data_t)(le * 9));
	}
	fprintf(stdout, "Stack After Push:\n");
	MVStackPrint(stack, print_data);

	fprintf(stdout, "Stack Peek: { %lld }\n", (long long)MVStackPeek(stack));
	
	delete_data(MVStackPop(stack));
	delete_data(MVStackPop(stack));
	delete_data(MVStackPop(stack));
	delete_data(MVStackPop(stack));
	delete_data(MVStackPop(stack));
	fprintf(stdout, "Stack After Pop:\n");
	MVStackPrint(stack, print_data);

	fprintf(stdout, "Stack Peek: { %lld }\n", (long long)MVStackPeek(stack));

	fprintf(stdout, "\n===== CLEANING THE HEAP MEMORY =====\n\n");
	MVStackDestroy(&stack, delete_data);

	exit(SUCCESS);
}
