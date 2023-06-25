
/*
	@file: mv_dcll.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Doubly Circular Linked List
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 24 June 2023 (Saturday) 02:32 PM
*/

//Conditional Compilation
#ifndef		_MV_DCLL_H
#define		_MV_DCLL_H

//Constant Literals and Macros
#ifndef		SUCCESS
#define		SUCCESS		0
#endif

#ifndef		FAILURE
#define		FAILURE		1
#endif

//Typedefs
typedef		void*	data_t;
typedef		int 	status_t;

struct dcll_node;
typedef		struct dcll_node	dcll_node_t;
typedef		struct dcll_node*	p_dcll_node_t;
typedef		struct dcll_node**	pp_dcll_node_t;

struct mv_doubly_circular_linked_list;
typedef		struct mv_doubly_circular_linked_list		mv_dcll_t;
typedef		struct mv_doubly_circular_linked_list*		p_mv_dcll_t;
typedef 	struct mv_doubly_circular_linked_list**		pp_mv_dcll_t;

//Callback Functions
typedef		status_t (*compare_proc_t)(data_t, data_t);
typedef		void (*deletedataproc_t)(data_t);

//Struct Definitions
struct dcll_node
{
	data_t			data;
	p_dcll_node_t 	next;
	p_dcll_node_t 	prev;
};
#define		SIZE_DCLL_NODE		(sizeof(dcll_node_t))

struct mv_doubly_circular_linked_list
{
	p_dcll_node_t	head;
	p_dcll_node_t   tail;
	long long		size;
};
#define		SIZE_DCLL 		(sizeof(mv_dcll_t))

//Interface Function Declarations
/*
    @function: To Create List
    @identifier: MVCreateDCLL
    @return: created list
*/
extern p_mv_dcll_t MVCreateDCLL();

/*
    @function: Insert Data At Front
    @identifier: MVDCLLInsertFront
    @params: 1. List
             2. Data
    @return: Status 
*/
extern status_t MVDCLLInsertFront(p_mv_dcll_t, data_t);

/*
    @function: Insert Data At Back
    @identifier: MVDCLLInsertBack
    @params: 1. List
             2. Data
    @return: Status
*/
extern status_t MVDCLLInsertBack(p_mv_dcll_t, data_t);

/*
    @function: Insert Data At Particular Position
    @identifier: MVDCLLInsertAt
    @params: 1. List
             2. Data
             3. Index
    @return: Status
*/
extern status_t MVDCLLInsertAt(p_mv_dcll_t, data_t, long long);

/*
    @function: Insert Data before existing data
    @identifier: MVDCLLInsertBefore
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t MVDCLLInsertBefore(p_mv_dcll_t, data_t, data_t, compare_proc_t);

/*
    @function: Insert Data after existing data
    @identifier: MVDCLLInsertAfter
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t MVDCLLInsertAfter(p_mv_dcll_t, data_t, data_t, compare_proc_t);

/*
    @function: Remove Data from Front
    @identifier: MVDCLLRemoveFront
    @params: 1. List
    Return: Removed Data
*/
extern data_t MVDCLLRemoveFront(p_mv_dcll_t);

/*
    @function: Remove Data from Back
    @identifier: MVDCLLRemoveBack
    @params: 1. List
    Return: Removed Data
*/
extern data_t MVDCLLRemoveBack(p_mv_dcll_t);

/*
    @function: Remove Data At Specific Index
    @identifier: MVDCLLRemoveAt
    @params: 1. List
             2. Index
    @return: Removed Data
*/
extern data_t MVDCLLRemoveAt(p_mv_dcll_t, long long);

/*
    @function: Remove Data Before
    @identifier: MVDCLLRemoveBefore
    @params: 1. List
             2. Existing Data
             3. Compare proc
    @return: Removed Data
*/
extern data_t MVDCLLRemoveBefore(p_mv_dcll_t, data_t, compare_proc_t);

/*
    @function: Remove Data After
    @identifier: MVDCLLRemoveAfter
    @params: 1. List
             2. Existing Data
             3. Compare Proc
    @return: Removed Data
*/
extern data_t MVDCLLRemoveAfter(p_mv_dcll_t, data_t, compare_proc_t);

/*
    @function: Get Size from List
    @identifier: MVDCLLSize
    @params: 1. List
    @return: Size of List
*/
extern long long MVDCLLSize(p_mv_dcll_t);

/*
    @function: Get Data from List
    @identifier: MVDCLLDataAt
    @params: 1. List
             2. Index
    @return: Data
*/
extern data_t MVDCLLDataAt(p_mv_dcll_t list , long long index);

/*
    @function: Destroying the List
    @identifier: MVDCLLDestroy
    @params: 1. Pointer to List
             2. Delete Data Proc
    @return: Status
*/
extern status_t	MVDCLLDestroy(pp_mv_dcll_t, deletedataproc_t);

#endif	    //_MV_DCLL_H
