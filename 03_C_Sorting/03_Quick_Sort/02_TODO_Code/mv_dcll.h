
/*
	@file: mv_dcll.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Doubly Circular Linked List
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 21 July 2023 (Friday) 01:32 PM
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

/*
    @function: Set Data at Particular Index
    @identifier: MVDCLLSetDataAt
    @params: 1. List
             2. New Data
             3. Index
    @return: Existing Data at Index
*/
extern data_t MVDCLLSetDataAt(p_mv_dcll_t, data_t, long long);

/*
    @function: Apply Insertion Sort to DCLL
    @identifier: MVDCLLInsertionSort
    @params: 1. List
             2. Compare Data Proc CallBack
    @return: Status
*/
extern status_t MVDCLLInsertionSort(p_mv_dcll_t, compare_proc_t);

/*
    @function: Apply Insertion Sort to DCLL having integers
    @identifier: MVDCLLInsertionSortN
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Number of Elements
    @return: Status
*/
extern status_t MVDCLLInsertionSortN(p_mv_dcll_t, compare_proc_t, long long);

/*
    @function: Apply Merge Sort to DCLL
    @identifier: MVDCLLMergeSort
    @params: 1. List
             2. Compare Data Proc CallBack
    @return: Status
*/
extern  status_t MVDCLLMergeSort(p_mv_dcll_t, compare_proc_t);

/*
    @function: Apply Merge Sort to DCLL for given number of elements
    @identifier: MVDCLLMergeSort
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Number of Elements
    @return: Status
*/
extern  status_t MVDCLLMergeSortN(p_mv_dcll_t, compare_proc_t, long long no_of_elements);

/*
    @function: Apply Merge Sort to DCLL for given number of elements
    @identifier: MVDCLLMergeSort
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Starting Index
             4. End Index
    @return: Status
*/
extern  status_t MVDCLLMergeSortSE(p_mv_dcll_t, compare_proc_t, long long start, long long end);

/*
    @function: Apply Quick Sort to DCLL
    @identifier: MVDCLLQuickSort
    @params: 1. List
             2. Compare Data Proc CallBack
    @return: Status
*/
extern  status_t MVDCLLQuickSort(p_mv_dcll_t, compare_proc_t);

/*
    @function: Apply Quick Sort to DCLL for Number of Elements
    @identifier: MVDCLLQuickSortN
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Number of Elements
    @return: Status
*/
extern  status_t MVDCLLQuickSortN(p_mv_dcll_t, compare_proc_t, long long no_of_elements);

/*
    @function: Apply Quick Sort to DCLL for Starting to Ending Indexes
    @identifier: MVDCLLQuickSortSE
    @params: 1. List
             2. Compare Data Proc CallBack
             3. Start Index
             4. End Index
    @return: Status
*/
extern  status_t MVDCLLQuickSortSE(p_mv_dcll_t, compare_proc_t, long long start, long long end);

/*
    @function: Create Copy of DCLL
    @identifier: MVDCLLCreateCopy
    @params: 1. List
    @return: Created DCLL Copy
*/
extern p_mv_dcll_t MVDCLLCreateCopy(p_mv_dcll_t);

/*
    @function: Create Copy of DCLL
    @identifier: MVDCLLCreateCopy
    @params: 1. List
             2. Number of Elements to Copy
    @return: Created DCLL Copy
*/
extern p_mv_dcll_t MVDCLLCreateCopyN(p_mv_dcll_t, long long no_of_elements);

/*
    @function: Create Copy of DCLL
    @identifier: MVDCLLCreateCopy
    @params: 1. List
             2. Starting Index
             3. End Index
    @return: Created DCLL Copy
*/
extern p_mv_dcll_t MVDCLLCreateCopySE(p_mv_dcll_t, long long start, long long end);

/*
    @function: Display Error Message to Corresponding Error Type
    @identifier: MVDCLLGetError
*/
extern void MVDCLLGetError(void);

#endif			/*_MV_DCLL_H */
