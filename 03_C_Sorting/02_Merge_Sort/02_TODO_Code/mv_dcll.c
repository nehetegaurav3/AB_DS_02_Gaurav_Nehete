
/*
    @file: mv_dcll.c
    @brief: Source code file for definitions of Interface functions of Doubly Circular Linked List
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 19 July 2023 (Wednesday) 12:03 PM 
*/

//Headers
#include	<stdio.h>
#include 	<stdlib.h>

#include	"mv_dcll.h"
#include	"mv_insertionsort.h"
#include	"mv_mergesort.h"

//Constant Literals	and Macros
#define	CHECK_LIST_ERRORS(list,	errors)	{														\
											if(FAILURE ==  CheckListErrors(list, errors))		\
												return(FAILURE);								\
										}

#define	CHECK_LIST_ERRORS_NULL(list, errors) {														\
												if(FAILURE ==  CheckListErrors(list, errors)) 	 	\
													return(NULL);									\
											 }

#define		CHECK_LIST		0x00000001
#define		CHECK_SIZE		0x00000002

enum ERRORS
{
	E_NONE = 0,
	E_OOM,		//Out Of Memory
	E_LNF,		//List Not Found
	E_LE,		//List is Empty
	E_CCM,		//Compare Callback procedure Missing
	E_EDNF,		//Existing Data Not Found	
	E_IOOB,		//Index Out Of Bound
};
static enum ERRORS dcll_error = E_NONE;

//Helper Functions
/*
    @function: To allocate dynamic memory and perform error check
    @identifier: Xmalloc
    @params: 1. Number of bytes to allocate
    @return: Allocated memory
*/
static void* Xmalloc(size_t no_of_bytes)
{
	//Code
	void* p = malloc(no_of_bytes);

	if(NULL == p)
	{
		dcll_error = E_OOM;
		exit(FAILURE);
	}

	dcll_error = E_NONE;
	return(p);
}

/*
    @function: To create new Data Node
    @identifier: CreateNode
    @params: 1. New Data
    @return: Created Node
*/
static p_dcll_node_t CreateNode(data_t new_data)
{
	//Code
	p_dcll_node_t new_node = (p_dcll_node_t)Xmalloc(SIZE_DCLL_NODE);

	new_node->data = new_data;
	new_node->next = new_node;
	new_node->prev = new_node;

	dcll_error = E_NONE;
	return(new_node);
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
static status_t	GenericInsert(p_mv_dcll_t list, p_dcll_node_t first, p_dcll_node_t mid, p_dcll_node_t last)
{
	//Code
	//Manipulate all next pointers
	first->next = mid;
	mid->next = last;

	//Manipulate all prev pointers
	last->prev = mid;
	mid->prev = first;

	//Increment the size
	list->size++;

	list->tail = list->head->prev;

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: To Remove node from list
    @identifier: GenericRemove
    @params: 1. List for Insertion
             2. Node to Remove
    @return: Removed Data
*/
static data_t GenericRemove(p_mv_dcll_t list, p_dcll_node_t d_node)
{
	//Code
	p_dcll_node_t first = d_node->prev;
	p_dcll_node_t last = d_node->next;

	first->next = last;
	last->prev = first;

	data_t to_return_data = d_node->data;

	free(d_node);
	d_node = NULL;

	//Decrement size
	list->size--;

	list->tail = list->head->prev;

	dcll_error = E_NONE;
	return(to_return_data);
}

/*
    @function: To check possible list related errors
    @identifier: CheckListErrors
    @params: 1. List
             2. Hexadecimal Value of Error
    @return: Status
*/
static status_t CheckListErrors(p_mv_dcll_t list, int errors)
{
	//Code
	if(errors & CHECK_LIST)		//Check List Present
	{
		if(NULL == list)
		{
			dcll_error = E_LNF;
			return(FAILURE);
		}
	}

	if(errors & CHECK_SIZE) 	//Check List Empty
	{
		if(0 == list->size)
		{
			dcll_error = E_LE;
			return(FAILURE);
		}
	}

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: To locate node in list
    @identifier: LocateNode
    @params: 1. List
             2. Existing Data
			 3. Compare Proc Callback
    @return: Located Node
*/
static p_dcll_node_t LocateNode(p_mv_dcll_t list, data_t e_data, compare_proc_t pcompareproc)
{
	//Code
	if(NULL == pcompareproc)
	{
		dcll_error = E_CCM;
		return(NULL);
	}

	p_dcll_node_t runner = list->head->next;

	while(1)
		{
			if(SUCCESS == pcompareproc(runner->data, e_data))
			{
				dcll_error = E_NONE;
				return(runner);
			}

			runner = runner->next;

			if(runner == list->head)
			{
				break;
			}
		}

		dcll_error = E_EDNF;
		return(NULL);
}

/*
    @function: Destroy DCLL
    @identifier: _MVDCLLDestroy
    @params: 1. Pointer to List
    @return: void
*/
static void _MVDCLLDestroy(void** plist)
{
	MVDCLLDestroy((pp_mv_dcll_t)plist, NULL);
}

//Interface Function Definitions
/*
    @function: To Create List
    @identifier: MVCreateDCLL
    @return: created list
*/
extern p_mv_dcll_t MVCreateDCLL()
{
	//Code
	p_mv_dcll_t list = (p_mv_dcll_t)Xmalloc(SIZE_DCLL);

	list->head = CreateNode(NULL);
	list->tail = list->head;
	list->size = 0;

	dcll_error = E_NONE;
	return(list);
}

/*
    @function: Insert Data At Front
    @identifier: MVDCLLInsertFront
    @params: 1. List
             2. Data
    @return: Status 
*/
extern status_t MVDCLLInsertFront(p_mv_dcll_t list, data_t new_data)
{
	//Code
	CHECK_LIST_ERRORS(list, CHECK_LIST);

	return(GenericInsert(list, list->head, CreateNode(new_data), list->head->next));
}

/*
    @function: Insert Data At Back
    @identifier: MVDCLLInsertBack
    @params: 1. List
             2. Data
    @return: Status
*/
extern status_t MVDCLLInsertBack(p_mv_dcll_t list, data_t new_data)
{
	//Code
	CHECK_LIST_ERRORS(list, CHECK_LIST);

	return(GenericInsert(list, list->tail, CreateNode(new_data), list->tail->next));
}

/*
    @function: Insert Data At Particular Position
    @identifier: MVDCLLInsertAt
    @params: 1. List
             2. Data
             3. Index
    @return: Status
*/
extern status_t MVDCLLInsertAt(p_mv_dcll_t list, data_t new_data, long long index)
{
	//Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	if(0 == index)
	{
		return(MVDCLLInsertFront(list, new_data));
	}
	else if(list->size-1 == index)
	{
		return(MVDCLLInsertBack(list, new_data));
	}
	else if(0 > index || index >= list->size)
	{
		dcll_error = E_IOOB;
		return(FAILURE);
	}

	p_dcll_node_t runner = list->head;

	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	return(GenericInsert(list, runner, CreateNode(new_data), runner->next));
}

/*
    @function: Insert Data before existing data
    @identifier: MVDCLLInsertBefore
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t MVDCLLInsertBefore(p_mv_dcll_t list, data_t e_data, data_t new_data, compare_proc_t pcompareproc)
{
	// Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	p_dcll_node_t e_node = LocateNode(list, e_data, pcompareproc);

	if(NULL != e_node)
	{
		return(GenericInsert(list, e_node->prev, CreateNode(new_data), e_node));
	}

	return(FAILURE);
}

/*
    @function: Insert Data after existing data
    @identifier: MVDCLLInsertAfter
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t MVDCLLInsertAfter(p_mv_dcll_t list, data_t e_data, data_t new_data, compare_proc_t pcompareproc)
{
	//Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	p_dcll_node_t e_node = LocateNode(list, e_data, pcompareproc);

	if(NULL != e_node)
	{
		return(GenericInsert(list, e_node, CreateNode(new_data), e_node->next));
	}

	return(FAILURE);
}

/*
    @function: Remove Data from Front
    @identifier: MVDCLLRemoveFront
    @params: 1. List
    Return: Removed Data
*/
extern data_t MVDCLLRemoveFront(p_mv_dcll_t list)
{
	//Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	return(GenericRemove(list, list->head->next));
}

/*
    @function: Remove Data from Back
    @identifier: MVDCLLRemoveBack
    @params: 1. List
    Return: Removed Data
*/
extern data_t MVDCLLRemoveBack(p_mv_dcll_t list)
{
	//Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	return(GenericRemove(list, list->tail));
}

/*
    @function: Remove Data At Specific Index
    @identifier: MVDCLLRemoveAt
    @params: 1. List
             2. Index
    @return: Removed Data
*/
extern data_t MVDCLLRemoveAt(p_mv_dcll_t list, long long index)
{
	//Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	if(0 == index)
	{
		return(MVDCLLRemoveFront(list));
	}
	else if( list->size-1 == index )
	{
		return(MVDCLLRemoveBack(list));
	}
	else if(0 > index || index >= list->size)
	{
		dcll_error = E_IOOB;
		return(NULL);
	}

	p_dcll_node_t runner = list->head->next;

	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	return(GenericRemove(list, runner));
}

/*
    @function: Remove Data Before
    @identifier: MVDCLLRemoveBefore
    @params: 1. List
             2. Existing Data
             3. Compare proc
    @return: Removed Data
*/
extern data_t MVDCLLRemoveBefore(p_mv_dcll_t list, data_t e_data, compare_proc_t pcompareproc)
{
	// Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_dcll_node_t e_node = LocateNode(list, e_data, pcompareproc);

	if(NULL != e_node)
		return(GenericRemove(list, e_node->prev));

	return(NULL);
}

/*
    @function: Remove Data After
    @identifier: MVDCLLRemoveAfter
    @params: 1. List
             2. Existing Data
             3. Compare Proc
    @return: Removed Data
*/
extern data_t MVDCLLRemoveAfter(p_mv_dcll_t list, data_t e_data, compare_proc_t pcompareproc)
{
	//Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	p_dcll_node_t e_node = LocateNode(list, e_data, pcompareproc);

	if(NULL != e_node)
		return(GenericRemove(list, e_node->next));

	return(NULL);
}

/*
    @function: Get Size from List
    @identifier: MVDCLLSize
    @params: 1. List
    @return: Size of List
*/
extern long long MVDCLLSize(p_mv_dcll_t list)
{
	//Code
	if(NULL == list)
	{
		dcll_error = E_LNF;
		return(0);
	}

	dcll_error = E_NONE;
	return(list->size);
}

/*
    @function: Get Data from List
    @identifier: MVDCLLDataAt
    @params: 1. List
             2. Index
    @return: Data
*/
extern data_t MVDCLLDataAt(p_mv_dcll_t list , long long index)
{
	//Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	if(0 > index || index >= list->size)
	{
		dcll_error = E_IOOB;
		return(NULL);
	}

	p_dcll_node_t runner = list->head->next;

	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	dcll_error = E_NONE;
	return(runner->data);
}

/*
    @function: Set Data at Particular Index
    @identifier: MVDCLLSetDataAt
    @params: 1. List
             2. New Data
             3. Index
    @return: Existing Data at Index
*/
extern data_t MVDCLLSetDataAt(p_mv_dcll_t list, data_t new_data, long long index)
{
	//Code
	CHECK_LIST_ERRORS_NULL(list, CHECK_LIST | CHECK_SIZE);

	if(0 > index || index >= list->size)
	{
		dcll_error = E_IOOB;
		return(NULL);
	}

	p_dcll_node_t runner = list->head->next;

	for(long long le = 0; le < index; ++le)
	{
		runner = runner->next;
	}

	dcll_error = E_NONE;

	data_t to_return_data = runner->data;
	runner->data = new_data;

	return(to_return_data);
}

/*
    @function: Apply Insertion Sort to DCLL
    @identifier: MVDCLLInsertionSort
    @params: 1. List
             2. Compare Data Proc CallBack
    @return: Status
*/
extern status_t MVDCLLInsertionSort(p_mv_dcll_t list, compare_proc_t pcompareproc)
{
	//Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	MVInsertionSort(list, MVDCLLSize(list), pcompareproc, MVDCLLDataAt, MVDCLLSetDataAt);

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: Apply Insertion Sort to DCLL having integers
    @identifier: MVDCLLInsertionSortN
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Number of Elements to Sort
    @return: Status
*/
extern status_t MVDCLLInsertionSortN(p_mv_dcll_t list, compare_proc_t pcompareproc, long long no_of_elements)
{
	//Code
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	if(no_of_elements == MVDCLLSize(list))
	{
		MVDCLLInsertionSort(list, pcompareproc);
	}
	else if(no_of_elements > MVDCLLSize(list))
	{
		dcll_error = E_IOOB;
		return(FAILURE);
	}

	MVInsertionSort(list, no_of_elements, pcompareproc, MVDCLLDataAt, MVDCLLSetDataAt);

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: Apply Merge Sort to DCLL
    @identifier: MVDCLLMergeSort
    @params: 1. List
             2. Compare Data Proc CallBack
    @return: Status
*/
extern  status_t MVDCLLMergeSort(p_mv_dcll_t list, compare_proc_t pcompareproc)
{
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	MVMergeSort(list, 0, MVDCLLSize(list)-1, 
				pcompareproc, MVDCLLDataAt, MVDCLLSetDataAt, 
				MVDCLLCreateCopySE, _MVDCLLDestroy);

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: Apply Merge Sort to DCLL for given number of elements
    @identifier: MVDCLLMergeSortN
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Number of Elements
    @return: Status
*/
extern  status_t MVDCLLMergeSortN(p_mv_dcll_t list, compare_proc_t pcompareproc, long long no_of_elements)
{
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	MVMergeSort(list, 0, (no_of_elements - 1), 
				pcompareproc, MVDCLLDataAt, MVDCLLSetDataAt, 
				MVDCLLCreateCopySE, _MVDCLLDestroy);

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: Apply Merge Sort to DCLL for given number of elements
    @identifier: MVDCLLMergeSortSE
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Starting Index
             4. End Index
    @return: Status
*/
extern  status_t MVDCLLMergeSortSE(p_mv_dcll_t list, compare_proc_t pcompareproc, long long start, long long end)
{
	CHECK_LIST_ERRORS(list, CHECK_LIST | CHECK_SIZE);

	MVMergeSort(list, start, end, 
				pcompareproc, MVDCLLDataAt, MVDCLLSetDataAt, 
				MVDCLLCreateCopySE, _MVDCLLDestroy);

	dcll_error = E_NONE;
	return(SUCCESS);
}

/*
    @function: Create Copy of DCLL
    @identifier: MVDCLLCreateCopy
    @params: 1. List
    @return: Created DCLL Copy
*/
extern p_mv_dcll_t MVDCLLCreateCopy(p_mv_dcll_t list)
{
	//Code
	return(MVDCLLCreateCopySE(list, 0, (MVDCLLSize(list) - 1)));
}

/*
    @function: Create Copy of DCLL
    @identifier: MVDCLLCreateCopyN
    @params: 1. List
             2. Number of Elements to Copy
    @return: Created DCLL Copy
*/
extern p_mv_dcll_t MVDCLLCreateCopyN(p_mv_dcll_t list, long long no_of_elements)
{
	//Code
	return(MVDCLLCreateCopySE(list, 0, no_of_elements - 1));
}

/*
    @function: Create Copy of DCLL
    @identifier: MVDCLLCreateCopySE
    @params: 1. List
             2. Starting Index
             3. End Index
    @return: Created DCLL Copy
*/
extern p_mv_dcll_t MVDCLLCreateCopySE(p_mv_dcll_t list, long long start, long long end)
{
	//Code
	p_mv_dcll_t new_list = MVCreateDCLL();

	for(long long le = start; le <= end; ++le)
	{
		if(FAILURE == MVDCLLInsertBack(new_list, MVDCLLDataAt(list, le)))
		{
			return(NULL);
		}
	}

	dcll_error = E_NONE;
	return(new_list);
}


/*
    @function: Display Error Message to Corresponding Error Type
    @identifier: MVDCLLGetError
*/
extern void MVDCLLGetError(void)
{
	//Code
	switch(dcll_error)
	{

	case E_NONE:
	default:
		fprintf(stderr, "No Error Found\n");
		break;
		
	case E_OOM:
		fprintf(stderr, "ERROR: Out Of Memory\n");
		break;

	case E_LNF:
		fprintf(stderr, "ERROR: List Not Found\n");
		break;

	case E_IOOB:
		fprintf(stderr, "ERROR: Index Out Of Bound\n");
		break;

	case E_LE:
		fprintf(stderr, "ERROR: List is Empty\n");
		break;

	case E_CCM:
		fprintf(stderr, "ERROR: Compare Callback Missing\n");
		break;

	case E_EDNF:
		fprintf(stderr, "ERROR: Existing Data Not Found\n");
		break;

	}
}

/*
    @function: Destroying the List
    @identifier: MVDCLLDestroy
    @params: 1. Pointer to List
             2. Delete Data Proc
    @return: Status
*/
extern status_t MVDCLLDestroy(pp_mv_dcll_t plist, deletedataproc_t deletedataproc)
{
	//Code
	if(NULL == plist)
	{
		fprintf(stderr, "ERROR: List not found\n");
		return(FAILURE);
	}

	CHECK_LIST_ERRORS(*plist, CHECK_LIST);

	p_mv_dcll_t list = *plist;

	p_dcll_node_t runner = list->head->next;
	p_dcll_node_t runner_next = runner->next;

	while(list->head != runner)
	{
		if(deletedataproc)
		{
			deletedataproc(runner->data);
			runner->data = NULL;
		}

		free(runner);
		runner = NULL;

		runner = runner_next;

		if(runner == list->head)
			break;

		runner_next = runner->next;
	}

	free(list->head);
	list->head = NULL;

	free(list);
	*plist = NULL;

	return(SUCCESS);
}
