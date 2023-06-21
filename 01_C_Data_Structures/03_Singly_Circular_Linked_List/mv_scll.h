
/*
    @file: mv_scll.h
    @brief: Header file for declarations of Interface functions and type definition of Singly Circular Linked List
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 21 June 2023 (Wednesday) 12:15 PM    
*/

#ifndef _MV_SCLL_H
#define _MV_SCLL_H

//Typedefs
#define     SUCCESS     0
#define     FAILURE     1

struct scll_node;
typedef     struct scll_node    node_t;
typedef     struct scll_node*   p_node_t;
typedef     struct scll_node**  pp_node_t;

struct singly_circular_linked_list;
typedef     struct singly_circular_linked_list      scll_t;
typedef     struct singly_circular_linked_list*     p_scll_t;
typedef     struct singly_circular_linked_list**    pp_scll_t;

typedef     void*   data_t;
typedef     int     status_t;

// Parameters to comparison function : data_t, data_t
// Returns status of comparison : status_t
typedef     status_t (*compare_proc_t) (data_t, data_t);
typedef     void (*delete_proc_t) (data_t);

// Struct Type Definition
struct scll_node
{
    data_t      data;
    p_node_t    next;       //Self Referential Pointer
};
#define     SIZE_SCLL_NODE   (sizeof(node_t))

struct singly_circular_linked_list
{
    p_node_t    head;
    size_t      size;
};
#define     SIZE_SCLL   (sizeof(scll_t))

//Interface Functions
/*
    @function: To Create List
    @identifier: CreateSCLL
    @return: created list
*/
extern p_scll_t CreateSCLL();

/*
    @function: Insert Data At Front
    @identifier: ListInsertFront
    @params: 1. List
             2. Data
    @return: Status 
*/
extern status_t ListInsertFront(p_scll_t, data_t);

/*
    @function: Insert Data At Back
    @identifier: ListInsertBack
    @params: 1. List
             2. Data
    @return: Status
*/
extern status_t ListInsertBack(p_scll_t, data_t);

/*
    @function: Insert Data At Particular Position
    @identifier: ListInsertAt
    @params: 1. List
             2. Data
             3. Index
    @return: Status
*/
extern status_t ListInserAt(p_scll_t, data_t, long long);

/*
    @function: Insert Data before existing data
    @identifier: ListInsertBefore
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t ListInsertBefore(p_scll_t, data_t, data_t, compare_proc_t);

/*
    @function: Insert Data after existing data
    @identifier: ListInsertAfter
    @params: 1. List
             2. Existing Data
             3. New Data
             4. Compare Proc
    @return: Status
*/
extern status_t ListInsertAfter(p_scll_t, data_t, data_t, compare_proc_t);

/*
    @function: Get Data from List
    @identifier: ListDataAt
    @params: 1. List
             2. Index
    @return: Data
*/
extern data_t ListDataAt(p_scll_t, long long index);

/*
    @function: Get Size from List
    @identifier: ListSize
    @params: 1. List
    @return: Size of List
*/
extern size_t ListSize(p_scll_t);

/*
    @function: Remove Data from Front
    @identifier: ListRemoveFront
    @params: 1. List
    Return: Removed Data
*/
extern data_t ListRemoveFront(p_scll_t);

/*
    @function: Remove Data from Back
    @identifier: ListRemoveBack
    @params: 1. List
    Return: Removed Data
*/
extern data_t ListRemoveBack(p_scll_t);

/*
    @function: Remove Data At Specific Index
    @identifier: ListRemoveAt
    @params: 1. List
             2. Index
    @return: Removed Data
*/
extern data_t ListRemoveAt(p_scll_t, long long);

/*
    @function: Remove Data Before
    @identifier: ListRemoveBefore
    @params: 1. List
             2. Existing Data
             3. Compare proc
    @return: Removed Data
*/
extern data_t ListRemoveBefore(p_scll_t, data_t, compare_proc_t);

/*
    @function: Remove Data After
    @identifier: ListRemoveAfter
    @params: 1. List
             2. Existing Data
             3. Compare Proc
    @return: Removed Data
*/
extern data_t ListRemoveAfter(p_scll_t, data_t, compare_proc_t);

/*
    @function: Destroying the List
    @identifier: ListDestroy
    @params: 1. Pointer to List
             2. Delete Data Proc
    @return: Status
*/
extern status_t ListDestroy(pp_scll_t plist, delete_proc_t);

#endif //_MV_SCLL_H
