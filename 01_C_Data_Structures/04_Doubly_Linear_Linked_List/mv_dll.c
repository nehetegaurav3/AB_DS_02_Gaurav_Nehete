
/*
	@file: mv_dll.c
	@brief: Source code file for Definitions of Interface functions of Doubly Linear Linked List
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 21 June 2023 (Sunday) 07:15 PM
*/

// Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dll.h"

#define	CHECK_LIST_ERRORS(list, errors)	{														\
									    	if(FAILURE == CheckListErrors(list, errors))		\
											return(FAILURE);									\
										}

#define	CHECK_LIST_ERRORS_NULL(list, errors) {														\
												if(FAILURE == CheckListErrors(list, errors))		\
												return(NULL);									    \
											 }

#define		CHECK_LIST		0x00000001
#define		CHECK_SIZE		0x00000002

//	Helper Functions
/*
    @function: To allocate dynamic memory and perform error check
    @identifier: Xmalloc
    @params: 1. Number of bytes to allocate
    @return: Allocated memory
*/
static void* Xmalloc(size_t no_of_bytes)
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
static p_dll_node_t CreateNode(data_t new_data)
{
    p_dll_node_t new_node = (p_dll_node_t)Xmalloc(SIZE_DLL_NODE);

    new_node->data = new_data;
    new_node->next = NULL;
	new_node->prev = NULL;

    return(new_node);
}

/*
    @function: To check possible list related errors
    @identifier: CheckListErrors
    @params: 1. List
             2. Hexadecimal Value of Error
    @return: Created Node
*/
static status_t CheckListErrors(p_dll_t list, int errors)
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
    @function: To Locate node in list
    @identifier: LocateNode
    @params: 1. List
             2. Existing Data
             3. Compare Proc Function
    @return: Located Node
*/
static p_dll_node_t LocateNode(p_dll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	if(NULL == p_compareproc)
	{
		fprintf(stderr, "ERROR: CompareProc Callback Missing\n");
		return(NULL);
	}

	p_dll_node_t runner = list->head->next;

	while(1)
	{
		if(SUCCESS == p_compareproc(runner->data, e_data))
		{
			return(runner);
		}

		runner = runner->next;

		if(NULL == runner->next)
		{
			break;
		}
	}

	fprintf(stderr, "ERROR: Existing Data not found\n");
	return(NULL);
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
static status_t GenericInsert(p_dll_t list, p_dll_node_t first, p_dll_node_t mid, p_dll_node_t last)
{
    //Code
    
    mid->next = last;
    mid->prev = first;

    if(NULL != last) 
    {
        last->prev = mid;
    }
    first->next = mid;

    //Increment size
    list->size++;

    //Modify the tail
    if(first == list->tail)
    {
        list->tail = mid;
    }

    return(SUCCESS);
}

/*
    @function: To Remove node from list
    @identifier: GenericInsert
    @params: 1. List for Insertion
             2. Node to Remove
    @return: Removed Data
*/
static data_t GenericRemove(p_dll_t list, p_dll_node_t d_node)
{
	//Code
    p_dll_node_t d_node_prev = d_node->prev;
    p_dll_node_t d_node_next = d_node->next;

    //Connecting adjecent links of node to delete
    d_node_prev->next = d_node->next;
    if(list->tail != d_node)
    {
        d_node_next->prev = d_node->prev;
    }

    data_t removed_data = d_node->data;

    //Tail Modification
    if(d_node == list->tail)
    {
        list->tail = d_node_prev;
    }

    //Clearing Memory
    free(d_node); 
    d_node = NULL;

    //Decrement size of list
    list->size--;

	return(removed_data);
}

//Interface Functions

/*
    @function: To Create List
    @identifier: CreateDLL
    @return: created list
*/
extern p_dll_t CreateDLL()
{
    //Code
    p_dll_t list = (p_dll_t)Xmalloc(SIZE_DLL);

    list->head = list->tail = CreateNode(NULL);

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
extern status_t ListInsertFront(p_dll_t list, data_t new_data)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST);

	status_t status = GenericInsert(list, list->head, CreateNode(new_data), list->head->next);

    return(status);
}

/*
    @function: Insert Data At Back
    @identifier: ListInsertBack
    @params: 1. List
             2. Data
    @return: Status
*/
extern status_t ListInsertBack(p_dll_t list, data_t new_data)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST);

    p_dll_node_t runner = list->head;

    while(NULL != runner->next)
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
extern status_t ListInsertAt(p_dll_t list, data_t new_data, long long index)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	if(0 == index)
	{
		return(ListInsertFront(list, new_data));
	}
	else if(list->size-1 == index)
	{
		return(ListInsertBack(list, new_data));
	}
	else if(0 > index || index >= list->size)
	{
		fprintf(stderr, "ERROR: Index Out of Bound\n");
		return(FAILURE);
	}

    //Find the index-1 node
    p_dll_node_t runner = list->head;

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
extern status_t ListInsertBefore(p_dll_t list, data_t e_data, data_t new_data, compare_proc_t p_compareproc)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

    p_dll_node_t e_node = LocateNode(list, e_data, p_compareproc);

	if(NULL != e_node)
	{
		return(GenericInsert(list, e_node->prev, CreateNode(new_data), e_node));
	}

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
extern status_t ListInsertAfter(p_dll_t list, data_t e_data, data_t new_data, compare_proc_t p_compareproc)
{
    //Code
    CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	p_dll_node_t e_node = LocateNode(list, e_data, p_compareproc);

	if(NULL != e_node)
	{
		return(GenericInsert(list, e_node, CreateNode(new_data), e_node->next));
	}

    return(FAILURE);
}

/*
    @function: Get Data from List
    @identifier: ListDataAt
    @params: 1. List
             2. Index
    @return: Data
*/
extern data_t ListDataAt(p_dll_t list, long long index)
{
    //Code
    //Error Check Remains

    p_dll_node_t runner = list->head->next;

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
extern size_t ListSize(p_dll_t list)
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
extern data_t ListRemoveFront(p_dll_t list)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	return(GenericRemove(list, list->head->next));
}

/*
    @function: Remove Data from Back
    @identifier: ListRemoveBack
    @params: 1. List
    Return: Removed Data
*/
extern data_t ListRemoveBack(p_dll_t list)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_dll_node_t runner = list->head;

	while(NULL != runner->next)
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
extern data_t ListRemoveAt(p_dll_t list, long long index)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	if(0 == index)
	{
		return(ListRemoveFront(list));
	}
	else if(index == list->size-1)
	{
		return(ListRemoveBack(list));
	}
	else if(index < 0 || index >= list->size)
	{
		fprintf(stderr, "ERROR : Index Out Of Bound\n");
		return(NULL);
	}
	p_dll_node_t runner = list->head->next;

	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

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
extern data_t ListRemoveBefore(p_dll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_dll_node_t e_node = LocateNode(list, e_data, p_compareproc);

	if(NULL != e_node)
		return(GenericRemove(list, e_node->prev));

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
extern data_t ListRemoveAfter(p_dll_t list, data_t e_data, compare_proc_t p_compareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_dll_node_t e_node = LocateNode(list, e_data, p_compareproc);

	if(NULL != e_node)
	{
		return(GenericRemove(list, e_node->next));
	}

	return(NULL);
}

/*
    @function: Destroying the List
    @identifier: ListDestroy
    @params: 1. Pointer to List
             2. Delete Data Proc
    @return: Status
*/
extern status_t ListDestroy(pp_dll_t plist, delete_proc_t p_deletedataproc)
{
	// Code
	if(NULL == plist)
	{
		fprintf(stderr, "ERROR: List not exists\n");
		return(FAILURE);
	}

	p_dll_t list = *plist;
	CHECK_LIST_ERRORS(list, CHECK_LIST);

	p_dll_node_t runner = NULL;
	p_dll_node_t runner_next = NULL;

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
