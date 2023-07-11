
/*
	@file: mv_bst.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Binary Search Tree
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 11 July 2023 (Tuesday) 10:33 AM 
*/

//Conditional Compilation
#ifndef		_MV_BST_H
#define		_MV_BST_H


//Constant Literals and Macros
#ifndef 	STATUS_VALUE
#define		SUCCESS 	0
#define 	FAILURE 	1
#endif

#define		MATCH_SMALL		1
#define		MATCH_BIG		2
#define		MATCH_SAME		3


//Typedefs
typedef void*	data_t;
typedef	int 	status_t;

struct mv_binary_search_tree;
typedef	struct mv_binary_search_tree	mv_bst_t;
typedef struct mv_binary_search_tree*	p_mv_bst_t;
typedef struct mv_binary_search_tree**	pp_mv_bst_t;

struct mv_bst_node;
typedef	struct mv_bst_node		bst_node_t;
typedef struct mv_bst_node*		p_bst_node_t;
typedef struct mv_bst_node**	pp_bst_node_t;


//Callback Functions
typedef	status_t(*COMPAREDATAPROC)(data_t, data_t);
typedef void(*PRINTDATAPROC)(data_t);
typedef void(*DELETEDATAPROC)(data_t);


//Struct Definition
struct mv_bst_node
{
	data_t	data;
	p_bst_node_t 	left;
	p_bst_node_t 	right;
	p_bst_node_t 	parent;
};
#define		SIZE_BST_NODE	(sizeof(bst_node_t))

struct mv_binary_search_tree
{
	p_bst_node_t 	root;
	size_t 			size;
};
#define		SIZE_BST	(sizeof(mv_bst_t))


//Interface functions
/*
    @function: To Create Binary Search Tree
    @identifier: MVCreateBST
    @return: Created BST
*/
extern p_mv_bst_t MVCreateBST(void);

/*
    @function: Insert Data in BST
    @identifier: MVBSTInsert
    @params: 1. Tree
             2. New Data
			 3. Compare Callback Proc
    @return: Status 
*/
extern status_t MVBSTInsert(p_mv_bst_t, data_t, COMPAREDATAPROC);

/*
    @function: Remove Data from BST
    @identifier: MVBSTRemove
    @params: 1. Tree
             2. Existing Data
			 3. Compare Callback Proc
    @return: Removed Data
*/
extern data_t MVBSTRemove(p_mv_bst_t, data_t, COMPAREDATAPROC);

/*
    @function: Inorder BST Traversal
    @identifier: MVBSTInOrderRecursive
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void MVBSTInOrderRecursive(p_mv_bst_t tree, PRINTDATAPROC);

/*
    @function: PreOrder BST Traversal
    @identifier: MVBSTPreOrderRecursive
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void MVBSTPreOrderRecursive(p_mv_bst_t tree, PRINTDATAPROC);

/*
    @function: Postorder BST Traversal
    @identifier: MVBSTPostOrderRecursive
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTPostOrderRecursive(p_mv_bst_t tree, PRINTDATAPROC);

/*
    @function: Postorder BST Traversal
    @identifier: MVBSTInOrderIterative
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void MVBSTInOrderIterative(p_mv_bst_t tree, PRINTDATAPROC);

/*
    @function: Postorder BST Traversal
    @identifier: MVBSTPreOrderIterative
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void MVBSTPreOrderIterative(p_mv_bst_t tree, PRINTDATAPROC);

/*
    @function: BST Destroy
    @identifier: MVBSTDestroy
    @params: 1. Tree
             2. Delete Data Callback Proc
*/
extern void MVBSTDestroy(pp_mv_bst_t ptree, DELETEDATAPROC);

#endif 		// _MV_BST_H
