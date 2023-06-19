
/*
	@file: gn_sll.c
	@brief: Source code file for Definitions of Interface functions of Singly Linear Linked List
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 18 June 2023 (Sunday) 06:32 PM
*/

// Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"gn_sll.h"

#define	CHECK_LIST_ERRORS(list, errors)	{														\
									    	if(FAILURE == CheckListErrors(list, errors))		\
											return(FAILURE);									\
										}

#define	CHECK_LIST_ERRORS_NULL(list, errors) {														\
												if( FAILURE == CheckListErrors(list, errors) )		\
												return(NULL);									    \
											 }

#define		CHECK_LIST		0x00000001
#define		CHECK_SIZE		0x00000002

//	Helper Functions
static void* xmalloc(size_t	no_of_bytes)
{
	// Code
	void *p = malloc(no_of_bytes);

	if( NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory\n");
		exit(EXIT_FAILURE);
	}
	return(p);
}

static p_node_t create_node(data_t new_data)
{
	// Code
	p_node_t node = xmalloc(SIZE_NODE);
	node->data = new_data;
	node->next = NULL;
	return(node);
}

static status_t GenericInsert(p_sll_t list, p_node_t first, p_node_t mid, p_node_t last)
{
	mid->next = last;
	first->next = mid;

	list->size++;

	return(SUCCESS);
}

static data_t GenericRemove(p_sll_t list, p_node_t node)
{
	// Code
	p_node_t d_node = node->next;

	// Changing the link
	node->next = d_node->next;

	// Taking the data to return to client
	data_t to_remove_data = d_node->data;

	// Deleting the node
	free(d_node);
	d_node = NULL;

	// Decrement size
	list->size--;

	return(to_remove_data);
}

static status_t CheckListErrors(p_sll_t list, int errors)
{
	// Code
	if(errors & CHECK_LIST)
	{
		if(NULL == list)
		{
			fprintf(stderr, "ERROR: List not exists\n");
			return(FAILURE);
		}
	}

	if(errors & CHECK_SIZE)
	{
		if(0 == list->size)
		{
			fprintf(stderr, "ERROR: list is empty\n");
			return(FAILURE);
		}
	}

	return(SUCCESS);
}

// Definitions of Interface Functions

extern p_sll_t create_sll()
{
	// Code
	p_sll_t list = (p_sll_t)xmalloc(SIZE_SLL);

	list->head = create_node(NULL);
	list->size = 0;

	return(list);
}

extern status_t ListInsertFront(p_sll_t list, data_t new_data)
{
	// Code
	CHECK_LIST_ERRORS(list, CHECK_LIST);

	GenericInsert(list, list->head, create_node(new_data), list->head->next);

	return(SUCCESS);
}

extern status_t ListInsertBack(p_sll_t list, data_t new_data)
{
	// Code
	CHECK_LIST_ERRORS(list, CHECK_LIST);

	p_node_t runner = list->head;

	while(NULL != runner->next)
		runner = runner->next;

	GenericInsert(list, runner, create_node(new_data), runner->next);

	return(SUCCESS);
}

extern status_t ListInsertAt(p_sll_t list, data_t new_data, long long index)
{
	// Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	// Find the index-1 node
	p_node_t runner = list->head;

	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	return(GenericInsert(list, runner, create_node(new_data), runner->next));
}

extern status_t ListInsertBefore(p_sll_t list, data_t e_data, data_t new_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	while(NULL != runner->next)
	{
		if(SUCCESS ==  p_compareproc(runner->next->data, e_data))
			return(GenericInsert(list, runner, create_node(new_data), runner->next));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not Found\n");
	return(FAILURE);
}

extern status_t ListInsertAfter(p_sll_t list, data_t e_data, data_t new_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head->next;

	while(NULL != runner)
	{
		if(SUCCESS ==  p_compareproc(runner->data, e_data))
			return(GenericInsert(list, runner, create_node(new_data), runner->next));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not Found\n");
	return(FAILURE);
}

extern data_t ListDataAt(p_sll_t list, long long index)
{
	// Code
	// CHECK_LIST_ERRORS(list);

	p_node_t runner = list->head->next;

	for(long long le = 0; le < index; ++le)
		runner = runner->next;

	return(runner->data);
}

extern size_t ListSize(p_sll_t list)
{
	// Code
	if(NULL == list)
		return(0);

	return(list->size);
}

extern data_t ListRemoveFront(p_sll_t list)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	return(GenericRemove(list, runner));
}

extern data_t ListRemoveBack(p_sll_t list)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	while(NULL != runner->next->next)
		runner = runner->next;

	return(GenericRemove(list, runner));
}

extern data_t ListRemoveAt(p_sll_t list, long long index)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	if(index < 0 || index >= list->size)
	{
		fprintf(stderr, "ERROR : Index Out Of Bound\n");
		return(NULL);
	}
	else if(0 == index)
		return(ListRemoveFront(list));
	else if(index == list->size-1)
		return(ListRemoveBack(list));

	p_node_t runner = list->head;

	for(long long le = 0; le < index; ++le)
		runner = runner->next;

	return(GenericRemove(list, runner));
}

extern data_t ListRemoveBefore(p_sll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	while(NULL != runner->next->next)
	{
		if(SUCCESS ==  p_compareproc(runner->next->next->data, e_data))
			return(GenericRemove(list, runner));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not Found\n");
	return(NULL);
}

extern data_t ListRemoveAfter(p_sll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head->next;

	while(NULL != runner->next)
	{
		if(SUCCESS ==  p_compareproc(runner->data, e_data))
			return(GenericRemove(list, runner));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not Found\n");
	return(NULL);
}

extern status_t ListDestroy(pp_sll_t plist, delete_proc_t p_deletedataproc)
{
	// Code
	if(NULL == plist)
	{
		fprintf(stderr, "ERROR: List not exists\n");
		return(FAILURE);
	}

	p_sll_t list = *plist;
	CHECK_LIST_ERRORS(list, CHECK_LIST);

	p_node_t runner = NULL;
	p_node_t runner_next = NULL;

	if(list->size > 0)
	{
		runner = list->head->next;
		runner_next = runner->next;
	}

	while(NULL != runner)
	{
		if(p_deletedataproc)
		{
			p_deletedataproc(runner->data);
		}

		free(runner);
		runner = NULL;

		runner = runner->next;

		if(NULL == runner)
			break;

		runner_next = runner->next;
	}

	if(list->head)
	{
		free(list->head);
		list->head = NULL;
	}

	if(list)
	{
		free(list);
		list = NULL;
	}

	*plist = NULL;

	return(SUCCESS);
}
