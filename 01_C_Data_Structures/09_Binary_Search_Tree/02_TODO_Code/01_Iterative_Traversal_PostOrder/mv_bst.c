
/*
    @file: mv_bst.c
    @brief: Source code file for definitions of Interface functions of Binary Search Tree
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 11 July 2023 (Tuesday) 04:34 PM 
*/

//Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_bst.h"
#include "mv_stack.h"


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
		fprintf(stderr, "ERROR: Out Of Memory\n");
		exit(FAILURE);
	}
	return(p);
}

static p_bst_node_t CreateNode(data_t new_data)
{
	//Code
	p_bst_node_t node = (p_bst_node_t)Xmalloc(SIZE_BST_NODE);

	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;

	node->data = new_data;

	return(node);
}

static void InOrderRecursive(p_bst_node_t node, PRINTDATAPROC printdata)
{
	//Code
	if(node->left)
		InOrderRecursive(node->left, printdata);

	fprintf(stdout, "{");
	printdata(node->data);
	fprintf(stdout, "}--");

	if(node->right)
		InOrderRecursive(node->right, printdata);
}


static void PreOrderRecursive(p_bst_node_t node, PRINTDATAPROC printdata)
{
	//Code
	fprintf(stdout, "{");
	printdata(node->data);
	fprintf(stdout, "}--");

	if(node->left)
		PreOrderRecursive(node->left, printdata);

	if(node->right)
		PreOrderRecursive(node->right, printdata);
}

static void PostOrderRecursive(p_bst_node_t node, PRINTDATAPROC printdata)
{
	//Code
	if(node->left)
		PostOrderRecursive(node->left, printdata);

	if(node->right)
		PostOrderRecursive(node->right, printdata);

	fprintf(stdout, "{");
	printdata(node->data);
	fprintf(stdout, "}--");
}

static void PostOrderDestroy(p_bst_node_t node, DELETEDATAPROC deletedataproc)
{
	//Code
	if(node->left)
		PostOrderDestroy(node->left, deletedataproc);

	if(node->right)
		PostOrderDestroy(node->right, deletedataproc);

	fprintf(stdout, "Deleting: ");
	
	deletedataproc(node->data);
	fprintf(stdout, "\n");

	node->data = NULL;
	free(node);

}

static void PreOrderIterative(p_bst_node_t node, PRINTDATAPROC printdata)
{
	//Code
	p_bst_node_t runner = node;

	p_mv_stack_t stack = MVCreateStack();

	while(1)
	{
		while(runner)
		{
			//Print
			fprintf(stdout, "{");
			printdata(runner->data);
			fprintf(stdout, "}--");
			
			//Push
			MVStackPush(stack, runner);

			if(runner->left)
				runner = runner->left;
			else
				break;
		}

		runner = MVStackPop(stack);

		if(runner)
			runner = runner->right;
		else
			break;
	}

	MVStackDestroy(&stack, NULL);	
}

static void InOrderIterative(p_bst_node_t node, PRINTDATAPROC printdata)
{
	//Code
	p_bst_node_t runner = node;

	p_mv_stack_t stack = MVCreateStack();

	while(1)
	{
		while(runner)
		{
			//Push
			MVStackPush(stack, runner);

			if(runner->left)
				runner = runner->left;
			else
				break;
		}

		runner = MVStackPop(stack);

		if( runner )
		{
			//Print
			fprintf(stdout, "{");
			printdata(runner->data);
			fprintf(stdout, "}--");
			
			runner = runner->right;
		}
		else
			break;
	}

	MVStackDestroy(&stack, NULL);	
}

static void PostOrderIterative(p_bst_node_t node, PRINTDATAPROC printdata)
{
	//Code
	p_bst_node_t runner = node;

	p_mv_stack_t stack1 = MVCreateStack();
	p_mv_stack_t stack2 = MVCreateStack();
	
    MVStackPush(stack1, runner);

    while(MVStackSize(stack1) > 0)
	{
        runner = MVStackPop(stack1);
        MVStackPush(stack2, runner);

        if(runner->left)
		{
            MVStackPush(stack1, runner->left);
		}
		if(runner->right)
        {
			MVStackPush(stack1, runner->right);
		}
	}

    while(MVStackSize(stack2) > 0)
	{
        runner = MVStackPop(stack2);
        
		fprintf(stdout, "{");
		printdata(runner->data);
		fprintf(stdout, "}--");
    }

	MVStackDestroy(&stack1, NULL);	
	MVStackDestroy(&stack2, NULL);
}

static status_t BSTGenericInsert(p_mv_bst_t tree, data_t new_data, COMPAREDATAPROC pcompareproc)
{
	//Code
	p_bst_node_t runner = tree->root;

	while(1)
	{
		status_t status = pcompareproc(new_data, runner->data);
		
		if(MATCH_SMALL == status) // Check to go on left side
		{
			if(NULL == runner->left)
			{
				runner->left = CreateNode(new_data);
				runner->left->parent = runner;
				break;
			}
			runner = runner->left;
		}
		else if(MATCH_BIG == status) // Check to go on right side
		{
			if(NULL == runner->right)
			{
				runner->right = CreateNode(new_data);
				runner->right->parent = runner;
				break;
			}
			runner = runner->right;
		}
		else
		{
			fprintf(stderr, "ERROR: Data already exists\n");
			return(FAILURE);
		}
	}

	tree->size++;
	return(SUCCESS);
}

static p_bst_node_t BSTPredecessor(p_bst_node_t node)
{
	//Code
	p_bst_node_t runner = node->left;

	while(runner->right)
		runner = runner->right;

	return(runner);
}

static p_bst_node_t BSTSuccessor(p_bst_node_t node)
{
	//Code
	p_bst_node_t runner = node->right;

	while(runner->left)
		runner = runner->left;

	return(runner);
}

static data_t BSTGenericRemove(p_mv_bst_t tree, p_bst_node_t node)
{
	//Code

	data_t to_return_data = node->data;

	while(1)
	{
		if(node->left)
		{
			p_bst_node_t predec = BSTPredecessor(node);

			node->data = predec->data;

			node = predec;
		}
		else if(node->right)
		{
			p_bst_node_t succ = BSTSuccessor(node);

			node->data = succ->data;

			node = succ;
		}
		else 			//Here we will reach when there is no child to node
			break;
	}

	//Check for parents side
	if(NULL == node->parent)
	{
		tree->root = NULL;
	}
	else if(node == node->parent->left)
	{
		node->parent->left = NULL;
	}
	else
	{
		node->parent->right = NULL;
	}

	free(node);
	node = NULL;

	tree->size--;

	return(to_return_data);
}


//Interface Functions
/*
    @function: To Create Binary Search Tree
    @identifier: MVCreateBST
    @return: Created BST
*/
extern p_mv_bst_t MVCreateBST(void)
{
	//Code
	p_mv_bst_t tree = (p_mv_bst_t)Xmalloc(SIZE_BST);

	tree->root = NULL;
	tree->size = 0;

	return(tree);
}

/*
    @function: Insert Data in BST
    @identifier: MVBSTInsert
    @params: 1. Tree
             2. New Data
			 3. Compare Callback Proc
    @return: Status 
*/
extern status_t MVBSTInsert(p_mv_bst_t tree, data_t new_data, COMPAREDATAPROC pcompareproc)
{
	//Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: Tree not found\n");
		return(FAILURE);
	}

	if(NULL == pcompareproc)
	{
		fprintf(stderr, "ERROR: Compare callback must be provided\n");
		return(FAILURE);
	}

	if(NULL == tree->root)
	{
		tree->root = CreateNode(new_data);
	}
	else
	{
		return(BSTGenericInsert(tree, new_data, pcompareproc));
	}

	tree->size++;
	return(SUCCESS);
}

/*
    @function: Remove Data from BST
    @identifier: MVBSTRemove
    @params: 1. Tree
             2. Existing Data
			 3. Compare Callback Proc
    @return: Removed Data
*/
extern data_t MVBSTRemove(p_mv_bst_t tree, data_t existing_data, COMPAREDATAPROC pcompareproc)
{
	//Code
	if(NULL == tree)
	{
		fprintf(stderr, "ERROR: Tree not found\n");
		return(NULL);
	}

	if(0 == tree->size)
	{
		fprintf(stderr, "ERROR: Tree is empty\n");
		return(NULL);
	}

	if(NULL == pcompareproc)
	{
		fprintf(stderr, "ERROR: Callback must be provided\n");
		return(NULL);
	}

	p_bst_node_t runner = tree->root;

	//Search the data to be removed
	while(1)
	{
		status_t status = pcompareproc(existing_data, runner->data);

		if(MATCH_SAME == status)
		{
			break;
		}
		else if(MATCH_SMALL == status)
		{
			runner = runner->left;
		}
		else
		{
			runner = runner->right;
		}

		if(NULL == runner)
		{
			fprintf(stderr, "ERROR: Data not found\n");
			return(NULL);
		}
	}

	return(BSTGenericRemove(tree, runner));
}

/*
    @function: Inorder BST Traversal
    @identifier: MVBSTInOrderRecursive
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTInOrderRecursive(p_mv_bst_t tree, PRINTDATAPROC printdata)
{
	//Code
	fprintf(stdout, "InOrder BST:\n{START}->");
	InOrderRecursive(tree->root, printdata);
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: PreOrder BST Traversal
    @identifier: MVBSTPreOrderRecursive
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTPreOrderRecursive(p_mv_bst_t tree, PRINTDATAPROC printdata)
{
	//Code
	fprintf(stdout, "PreOrder BST:\n{START}->");
	PreOrderRecursive(tree->root, printdata);
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Postorder BST Traversal
    @identifier: MVBSTPostOrderRecursive
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTPostOrderRecursive(p_mv_bst_t tree, PRINTDATAPROC printdata)
{
	//Code
	fprintf(stdout, "PostOrder BST:\n{START}->");
	PostOrderRecursive(tree->root, printdata);
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Inorder BST Traversal
    @identifier: MVBSTInOrderIterative
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTInOrderIterative(p_mv_bst_t tree, PRINTDATAPROC printdata)
{
	// Code
	fprintf(stdout, "InOrder Iterative BST:\n{START}->");
	InOrderIterative(tree->root, printdata);
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Preorder BST Traversal
    @identifier: MVBSTPreOrderIterative
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTPreOrderIterative(p_mv_bst_t tree, PRINTDATAPROC printdata)
{
	// Code
	fprintf(stdout, "PreOrder Iterative BST:\n{START}->");
	PreOrderIterative(tree->root, printdata);
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: Postorder BST Traversal
    @identifier: MVBSTPostOrderIterative
    @params: 1. Tree
             2. Print Data Callback Proc
*/
extern void	MVBSTPostOrderIterative(p_mv_bst_t tree, PRINTDATAPROC printdata)
{
	// Code
	fprintf(stdout, "PostOrder Iterative BST:\n{START}->");
	PostOrderIterative(tree->root, printdata);
	fprintf(stdout, "{END}\n\n");
}

/*
    @function: BST Destroy
    @identifier: MVBSTDestroy
    @params: 1. Tree
             2. Delete Data Callback Proc
*/
extern void	MVBSTDestroy(pp_mv_bst_t ptree, DELETEDATAPROC deletedataproc)
{
	//Code
	if(NULL == ptree || NULL == *ptree)
	{
		fprintf(stderr, "ERROR: Tree not found\n");
		return;
	}

	fprintf(stdout, "Destroying BST:\n");
	PostOrderDestroy((*ptree)->root, deletedataproc);

	free(*ptree);
	*ptree = NULL;
}
