
/*
	@file: mv_dll.h
	@brief: Header file for declarations of Interface functions and type definition of Doubly Linear Linked List
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 21 June 2023 (Wednesday) 06:45 PM
*/

#ifndef	_MV_DLL_H
#define	_MV_DLL_H

//	Typedefs
#define		SUCCESS		0
#define		FAILURE		1

struct dll_node;
typedef		struct dll_node		dll_node_t;
typedef		struct dll_node*	p_dll_node_t;
typedef		struct dll_node**	pp_dll_node_t;

struct doubly_linked_list;
typedef		struct doubly_linked_list	dll_t;
typedef		struct doubly_linked_list*	p_dll_t;
typedef		struct doubly_linked_list**	pp_dll_t;

typedef		void*	data_t;
typedef		int 	status_t;

//	Parameters to comparison function : data_t, data_t
//	Returns status of comparison : status_t
typedef   status_t  (*compare_proc_t) (data_t, data_t);
typedef   void  (*delete_proc_t) (data_t);

//	Struct Type Definition
struct dll_node
{
	data_t			data;

	p_dll_node_t 	next;
	p_dll_node_t	prev;
};
#define		SIZE_DLL_NODE	(sizeof(dll_node_t))

struct doubly_linked_list
{
	p_dll_node_t 	head;
	p_dll_node_t 	tail;
	size_t			size;
};
#define		SIZE_DLL	(sizeof(dll_t))

//	Interface Functions
/*
	Function: To Create list
	Identifier:	CreateDLL
	Return: Created List
*/
extern p_dll_t CreateDLL();

/*
	Function: Insert Data At Front
	Identifier: ListInsertFront
	Parameters: 1. List
				2. Data
	Return: Status
*/
extern status_t ListInsertFront(p_dll_t, data_t);

/*
	Function: Insert Data At Back
	Identifier: ListInsertBack
	Parameters:	1. List
				2. Data
	Return: Status
*/
extern status_t ListInsertBack(p_dll_t, data_t);

/*
	Function: Insert Data at a particular position
	Identifier:  ListInsertAt
	Parameters: 1. List
				2. Data
				3. Index
	Return:  Status
*/
extern status_t ListInsertAt(p_dll_t, data_t, long long);

/*
	Function: Insert Data before existing data
	Identifier: ListInsertBefore
	Parameter: 1. List
			   2. Existing Data
		       3. New Data
			   4. Compare Proc
	Return: Status
*/
extern status_t ListInsertBefore(p_dll_t, data_t, data_t, compare_proc_t);

/*
	Function: Insert Data after existing data
	Identifier:  ListInsertAfter
	Parameter: 1. List
			   2. Existing Data
		       3. New Data
			   4. Compare Proc
	Return:   Status
*/
extern status_t ListInsertAfter(p_dll_t, data_t, data_t, compare_proc_t);

/*
	Function: Get Data From List
	Identifier: ListDataAt
	Parameters: 1. List
				2. Index
	Return:  Data
*/
extern data_t ListDataAt(p_dll_t, long long index);

/*
	Function: Get Size from list
	Identifier: ListSize
	Parameter: 1. List
	Return: Size of List
*/
extern size_t ListSize(p_dll_t);

/*
	Function: Remove Data from front
	Identifier: ListRemoveFront
	Parameter: 1. List
	Return: Removed Data 
*/
extern data_t ListRemoveFront(p_dll_t);

/*
	Function: Remove Data from Back
	Identifier: ListRemoveBack
	Parameter: 1. List
	Return: Removed Data 
*/
extern data_t ListRemoveBack(p_dll_t);

/*
	Function: Remove Data from Specific Index
	Identifier: ListRemoveAt
	Parameter: 1. List
			   2. Index
	Return: Removed Data 
*/
extern data_t ListRemoveAt(p_dll_t, long long);

/*
	Function: Remove Data Before
	Identifier: ListRemoveBefore
	Parameter: 1. List
		       2. Existing Data
		       3. Compare Proc
	Return: Removed Data 
*/
extern data_t ListRemoveBefore(p_dll_t, data_t, compare_proc_t);

/*
	Function: Remove Data After
	Identifier: ListRemoveAfter
	Parameter: 1. List
			   2. Existing Data
			   3. Compare Proc
	Return: Removed Data 
*/
extern data_t ListRemoveAfter(p_dll_t, data_t, compare_proc_t);

/*
	Function: Destroy the List
	Identifier: ListDestroy
	Parameter: 1. Pointer to List
			   2. Delete Data Proc
*/
extern status_t ListDestroy(pp_dll_t plist, delete_proc_t);

#endif	// _MV_DLL_H
