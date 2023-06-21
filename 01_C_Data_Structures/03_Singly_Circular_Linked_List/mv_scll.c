
/*
    @file: mv_scll.c
    @brief: Source code file for definitions of Interface functions of Singly Circular Linked List
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 21 June 2023 (Wednesday) 01:05 PM    
*/

//Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_scll.h"

#define CHECK_LIST_ERRORS(list, errors)     {                                                       \
                                                if(FAILURE == CheckListErrors(list, errors))        \
                                                return(FAILURE);                                    \
                                            }

#define CHECK_LIST_ERRORS_NULL(list, errors)    {                                                   \
                                                    if(FAILURE == CheckListErrors(list, errors))    \
                                                    return(NULL);                                   \
                                                }

#define     CHECK_LIST      0x00000001
#define     CHECK_SIZE      0x00000002

//Helper Functions
/*
    @function: To allocate dynamic memory and perform error check
    @identifier: xmalloc
    @params: 1. Number of bytes to allocate
    @return: Allocated memory
*/
static void* xmalloc(size_t no_of_bytes)
{
    //Code
    void *p = malloc(no_of_bytes);

    if(NULL == p)
    {
        fprintf(stderr, "ERROR: Out Of Memory\n");
        exit(FAILURE);
    }
    return(p);
}

/*
    @function: To create new Data Node
    @identifier: CreateNode
    @params: 1. New Data
    @return: Created Node
*/
static p_node_t CreateNode(data_t new_data)
{
    p_node_t new_node = (p_node_t)xmalloc(SIZE_SCLL_NODE);

    new_node->data = new_data;
    new_node->next = NULL;

    return(new_node);
}

/*
    @function: To check possible list related errors
    @identifier: CheckListErrors
    @params: 1. List
             2. Hexadecimal Value of Error
    @return: Created Node
*/
static status_t CheckListErrors(p_scll_t list, int errors)
{
    //Code
    if(errors & CHECK_LIST)     // Check List Present
    {
        if(NULL == list)
        {
            fprintf(stderr, "ERROR: List not found\n");
            return(FAILURE);
        }
    }

    if(errors & CHECK_SIZE)     //Check List Empty 
    {
        if(0 == list->size)
        {
            fprintf(stderr, "ERROR: List is Empty\n");
            return(FAILURE);
        }
    }

    return(SUCCESS);
}

/*
    @function: To Insert node in list
    @identifier: GenericInsert
    @params: 1. List for Insertion
             2. Node Before Insertion Node
             3. Actual Node to Insert
             4. Node After Insertion Node
    @return: Status
*/
static status_t GenericInsert(p_scll_t list, p_node_t first, p_node_t mid, p_node_t last)
{
    //Code

    //Manipulating Next Pointers
    mid->next = last;
    first->next = mid;

    list->size++;

    return(SUCCESS);
}

/*
    @function: To Remove node from list
    @identifier: GenericInsert
    @params: 1. List for Insertion
             2. Node to Remove
    @return: Removed Data
*/
static data_t GenericRemove(p_scll_t list, p_node_t node)
{
	// Code
	p_node_t d_node = node->next;

	// Change the link
	node->next = d_node->next;

	// Take the data to return to client
	data_t removed_data = d_node->data;

	// Actually deleting the node
	free(d_node);
	d_node = NULL;

	// Decrementing the size
	list->size--;

	return(removed_data);
}

//Interface Functions

/*
    @function: To Create List
    @identifier: CreateSCLL
    @return: created list
*/
extern p_scll_t CreateSCLL()
{
    //Code
    p_scll_t list = (p_scll_t)xmalloc(SIZE_SCLL);

    list->head = CreateNode(NULL);
    list->head->next = list->head;
    list->size = 0;

    return(list);
}

/*
    @function: Insert Data At Front
    @identifier: ListInsertFront
    @params: 1. List
             2. Data
    @return: Status 
*/
extern status_t ListInsertFront(p_scll_t list, data_t new_data)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST);

    return(GenericInsert(list, list->head, CreateNode(new_data), list->head->next));
}

/*
    @function: Insert Data At Back
    @identifier: ListInsertBack
    @params: 1. List
             2. Data
    @return: Status
*/
extern status_t ListInsertBack(p_scll_t list, data_t new_data)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST);

    p_node_t runner = list->head;

    while(NULL != runner->next->data)
    {
        runner = runner->next;
    }

    GenericInsert(list, runner, CreateNode(new_data), runner->next);

    return(SUCCESS);
}

/*
    @function: Insert Data At Particular Position
    @identifier: ListInsertAt
    @params: 1. List
             2. Data
             3. Index
    @return: Status
*/
extern status_t ListInsertAt(p_scll_t list, data_t new_data, long long index)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

    //Find the index-1 node
    p_node_t runner = list->head;

    for(long long le = 0; le < index; ++le)
    {
        runner = runner->next;
    }

    return(GenericInsert(list, runner, CreateNode(new_data), runner->next));
}

/*
    @function: Insert Data before existing data
    @identifier: ListInsertBefore
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t ListInsertBefore(p_scll_t list, data_t e_data, data_t new_data, compare_proc_t p_compareproc)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

    p_node_t runner = list->head;

    while(NULL != runner->next->data)
    {
        if(SUCCESS == p_compareproc(runner->next->data, e_data))
        {
            return(GenericInsert(list, runner, CreateNode(new_data), runner->next));
        }

        runner = runner->next;
    }

    fprintf(stderr, "ERROR: Existing Data Not Found\n");
    return(FAILURE);
}

/*
    @function: Insert Data after existing data
    @identifier: ListInsertAfter
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t ListInsertAfter(p_scll_t list, data_t e_data, data_t new_data, compare_proc_t p_compare_proc)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head->next;

	while(NULL != runner->data)
	{
		if(SUCCESS ==  p_compare_proc(runner->data, e_data))
			return(GenericInsert(list, runner, CreateNode(new_data), runner->next));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not found\n");
	return(FAILURE);
}

/*
    @function: Get Data from List
    @identifier: ListDataAt
    @params: 1. List
             2. Index
    @return: Data
*/
extern data_t ListDataAt(p_scll_t list, long long index)
{
    //Code
    //Error Check Remains

    p_node_t runner = list->head->next;

    for(long long le = 0; le < index; ++le)
    {
        runner = runner->next;
    }

    return(runner->data);
}

/*
    @function: Get Size from List
    @identifier: ListSize
    @params: 1. List
    @return: Size of List
*/
extern size_t ListSize(p_scll_t list)
{
    //Code
    if(NULL == list)
    {
        return(0);
    }

    return(list->size);
}

/*
    @function: Remove Data from Front
    @identifier: ListRemoveFront
    @params: 1. List
    Return: Removed Data
*/
extern data_t ListRemoveFront(p_scll_t list)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	return(GenericRemove(list, runner));
}

/*
    @function: Remove Data from Back
    @identifier: ListRemoveBack
    @params: 1. List
    Return: Removed Data
*/
extern data_t ListRemoveBack(p_scll_t list)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	while(NULL != runner->next->next->data)
		runner = runner->next;

	return(GenericRemove(list, runner));
}

/*
    @function: Remove Data At Specific Index
    @identifier: ListRemoveAt
    @params: 1. List
             2. Index
    @return: Removed Data
*/
extern data_t ListRemoveAt(p_scll_t list, long long index)
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

/*
    @function: Remove Data Before
    @identifier: ListRemoveBefore
    @params: 1. List
             2. Existing Data
             3. Compare proc
    @return: Removed Data
*/
extern data_t ListRemoveBefore(p_scll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head;

	while(NULL != runner->next->next->data)
	{
		if(SUCCESS == p_compareproc(runner->next->next->data, e_data))
			return(GenericRemove(list, runner));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not Found\n");
	return(NULL);
}

/*
    @function: Remove Data After
    @identifier: ListRemoveAfter
    @params: 1. List
             2. Existing Data
             3. Compare Proc
    @return: Removed Data
*/
extern data_t ListRemoveAfter(p_scll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_node_t runner = list->head->next;

	while(NULL != runner->next->data)
	{
		if(SUCCESS == p_compareproc(runner->data, e_data))
			return(GenericRemove(list, runner));

		runner = runner->next;
	}

	fprintf(stderr, "ERROR: Existing Data Not Found\n");
	return(NULL);
}

/*
    @function: Destroying the List
    @identifier: ListDestroy
    @params: 1. Pointer to List
             2. Delete Data Proc
    @return: Status
*/
extern status_t ListDestroy(pp_scll_t plist, delete_proc_t p_deletedataproc)
{
	// Code
	if(NULL == plist)
	{
		fprintf(stderr, "ERROR: List not exists\n");
		return(FAILURE);
	}

	p_scll_t list = *plist;
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

		runner = runner_next;

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
