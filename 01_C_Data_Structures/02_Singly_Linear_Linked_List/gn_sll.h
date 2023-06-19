

/*
	@file: gn_sll.h
	@brief: Header file for declarations of Interface functions and type definition of Singly Linear Linked List
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 18 June 2023 (Sunday) 03:22 PM
*/

#ifndef	_GN_SLL_H
#define	_GN_SLL_H

//	Typedefs
#define		SUCCESS		0
#define		FAILURE		1

struct sll_node;
typedef		struct sll_node		node_t;
typedef		struct sll_node*	p_node_t;
typedef		struct sll_node**	pp_node_t;

struct singly_linked_list;
typedef		struct singly_linked_list	sll_t;
typedef		struct singly_linked_list*	p_sll_t;
typedef		struct singly_linked_list**	pp_sll_t;

typedef		void*	data_t;
typedef		int 	status_t;

//	Parameters to comparison function : data_t, data_t
//	Returns status of comparison : status_t
typedef   status_t  (*compare_proc_t) (data_t, data_t);
typedef   void  (*delete_proc_t) (data_t);

//	Struct Type Definition
struct sll_node
{
	data_t		data;
	p_node_t 	next;
};
#define		SIZE_NODE	(sizeof(node_t))

struct singly_linked_list
{
	p_node_t 	head;
	size_t		size;
};
#define		SIZE_SLL	(sizeof(sll_t))

//	Interface Functions
/*
	Function: To Create list
	Identifier:	create_sll
	Return: Created List
*/
extern p_sll_t create_sll();

/*
	Function: Insert Data At Front
	Identifier: ListInsertFront
	Parameters: 1. List
				2. Data
	Return: Status
*/
extern status_t ListInsertFront(p_sll_t, data_t);

/*
	Function: Insert Data At Back
	Identifier: ListInsertBack
	Parameters:	1. List
				2. Data
	Return: Status
*/
extern status_t ListInsertBack(p_sll_t, data_t);

/*
	Function: Insert Data at a particular position
	Identifier:  ListInsertAt
	Parameters: 1. List
				2. Data
				3. Index
	Return:  Status
*/
extern status_t ListInsertAt(p_sll_t, data_t, long long);

/*
	Function: Insert Data before existing data
	Identifier: ListInsertBefore
	Parameter: 1. List
			   2. Existing Data
		       3. New Data
			   4. Compare Proc
	Return: Status
*/
extern status_t ListInsertBefore(p_sll_t, data_t, data_t, compare_proc_t);

/*
	Function: Insert Data after existing data
	Identifier:  ListInsertAfter
	Parameter: 1. List
			   2. Existing Data
		       3. New Data
			   4. Compare Proc
	Return:   Status
*/
extern status_t ListInsertAfter(p_sll_t, data_t, data_t, compare_proc_t);

/*
	Function: Get Data From List
	Identifier: ListDataAt
	Parameters: 1. List
				2. Index
	Return:  Data
*/
extern data_t ListDataAt(p_sll_t, long long index);

/*
	Function: Get Size from list
	Identifier: ListSize
	Parameter: 1. List
	Return: Size of List
*/
extern size_t ListSize(p_sll_t);

/*
	Function: Remove Data from front
	Identifier: ListRemoveFront
	Parameter: 1. List
	Return: Removed Data 
*/
extern data_t ListRemoveFront(p_sll_t);

/*
	Function: Remove Data from Back
	Identifier: ListRemoveBack
	Parameter: 1. List
	Return: Removed Data 
*/
extern data_t ListRemoveBack(p_sll_t);

/*
	Function: Remove Data from specific index
	Identifier: ListRemoveAt
	Parameter: 1. List
			   2. Index
	Return: Removed Data 
*/
extern data_t ListRemoveAt(p_sll_t, long long);

/*
	Function: Remove Data Before
	Identifier: ListRemoveBefore
	Parameter: 1. List
		       2. Existing Data
		       3. Compare Proc
	Return: Removed Data 
*/
extern data_t ListRemoveBefore(p_sll_t, data_t, compare_proc_t);

/*
	Function: Remove Data After
	Identifier: ListRemoveAfter
	Parameter: 1. List
			   2. Existing Data
			   3. Compare Proc
	Return: Removed Data 
*/
extern data_t ListRemoveAfter(p_sll_t, data_t, compare_proc_t);

/*
	Function: Destroy the List
	Identifier: ListDestroy
	Parameter: 1. Pointer to List
			   2. Delete Data Proc
*/
extern status_t ListDestroy(pp_sll_t plist, delete_proc_t);

#endif	// _GN_SLL_H
