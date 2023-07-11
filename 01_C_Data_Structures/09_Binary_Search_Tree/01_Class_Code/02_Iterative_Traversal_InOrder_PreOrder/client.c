
/*
	@file: client.c
	@brief: Client side file for usage of Binary Search Tree
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 11 July 2023 (Tuesday) 03:34 PM 
*/

//Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_bst.h"

//Global Objects
p_mv_bst_t tree = NULL;

status_t comparedata(data_t data1, data_t data2)
{
	//Code
	if((long long)data1 == (long long)data2)
	{
		return(MATCH_SAME);
	}
	else if((long long)data1 <= (long long)data2)
	{
		return(MATCH_SMALL);
	}
	else
	{
		return(MATCH_BIG);
	}
}

void print_data(data_t data)
{
	fprintf(stdout, "%lld", (long long)data);
}

int main(void)
{
	//Code
	tree = MVCreateBST();

	MVBSTInsert(tree, (data_t)500, comparedata);
	MVBSTInsert(tree, (data_t)200, comparedata);
	MVBSTInsert(tree, (data_t)800, comparedata);
	MVBSTInsert(tree, (data_t)100, comparedata);
	MVBSTInsert(tree, (data_t)355, comparedata);
	MVBSTInsert(tree, (data_t)250, comparedata);
	MVBSTInsert(tree, (data_t)240, comparedata);
	MVBSTInsert(tree, (data_t)350, comparedata);
	MVBSTInsert(tree, (data_t)600, comparedata);
	MVBSTInsert(tree, (data_t)900, comparedata);
	MVBSTInsert(tree, (data_t)700, comparedata);
	MVBSTInsert(tree, (data_t)800, comparedata);


	MVBSTPreOrderRecursive(tree, print_data);
	MVBSTPreOrderIterative(tree, print_data);
	
	MVBSTInOrderRecursive(tree, print_data);
	MVBSTInOrderIterative(tree, print_data);

	MVBSTRemove(tree, (data_t)355, comparedata);

	MVBSTPreOrderRecursive(tree, print_data);
	MVBSTPreOrderIterative(tree, print_data);
	
	MVBSTInOrderRecursive(tree, print_data);
	MVBSTInOrderIterative(tree, print_data);

	MVBSTRemove(tree, (data_t)500, comparedata);

	MVBSTPreOrderRecursive(tree, print_data);
	MVBSTPreOrderIterative(tree, print_data);
	
	MVBSTInOrderRecursive(tree, print_data);
	MVBSTInOrderIterative(tree, print_data);

	MVBSTDestroy(&tree, print_data);

	exit(SUCCESS);
}