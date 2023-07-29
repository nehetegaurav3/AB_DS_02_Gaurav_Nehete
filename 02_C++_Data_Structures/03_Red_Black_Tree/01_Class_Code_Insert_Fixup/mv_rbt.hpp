
/*
    @file: mv_RBT.hpp
    @brief: Implementation of Binary Search Tree + Set B of rules that gives Red Black Tree using CPP
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 29 July 2023 (Saturday) 09:08 AM 
*/

//Conditional Compilation
#pragma	once

//Headers
#include <iostream>

//Typedefs
#ifndef	    DEFS
#define	    DEFS

#define	    SUCCESS	    0
#define	    FAILURE	    1

typedef	    int     status_t;

#endif      /* DEFS */

#define		BLACK		0
#define		RED			1

//Class Declarations
template<class DATA_T>
class TreeNode
{
	//Data Members
    DATA_T      m_data;
    TreeNode*	m_left;
    TreeNode*	m_right;
    TreeNode*	m_parent;
	int 		m_color;

	//Member Functions
	//Default Constructor: Initilization List
    TreeNode() : m_data(nullptr), m_left(nullptr), m_right(nullptr), m_parent(nullptr), m_color(RED)
    {}

	//Parameterized Constructor
    TreeNode(DATA_T init_data) : m_data(init_data), m_color(RED)
    {
    	m_left = nullptr;
    	m_right = nullptr;
    	m_parent = nullptr;
    }

    template <class DATA_T>
    friend class MV_RBT;
};

template <class DATA_T>
class MV_RBT
{
private:
	typedef	TreeNode<DATA_T>* P_TreeNode;

	//Exception Handler Class
	class OutOfMemory 
	{};

	//Data Members
	P_TreeNode	m_root;
	long long   m_size;

	P_TreeNode CreateNode(DATA_T new_data)
	{
        //Code
		P_TreeNode node = new TreeNode<DATA_T>(new_data);	
		
		if(nullptr == node)
			throw OutOfMemory();

		return(node);
	}

	P_TreeNode LocateNode(DATA_T e_data)
	{
		//Code
		P_TreeNode runner = m_root;

		while(true)
		{
			if(runner->m_data == e_data)
				return(runner);

			if(e_data < runner->m_data)
				runner = runner->m_left;
			else
				runner = runner->m_right;

			if(nullptr == runner)
				return(nullptr);
		}
	}

	P_TreeNode Predecessor(P_TreeNode node)
	{
		//Code
		node = node->m_left;

		while(node->m_right)
			node = node->m_right;

		return(node);
	}

	P_TreeNode Successor(P_TreeNode node)
	{
		//Code

		node = node->m_right;

		while(node->m_left)
			node = node->m_left;

		return(node); 
	}

	status_t GenericInsert(DATA_T new_data)
	{
		//Code

		P_TreeNode runner = m_root;
		P_TreeNode new_node = nullptr;

		while(true)
		{
			if(new_data < runner->m_data)
			{
				if(runner->m_left)
				{
					runner = runner->m_left;
				}
				else
				{
					new_node = CreateNode(new_data);
					runner->m_left = new_node;
					runner->m_left->m_parent = runner;
					break;
				}
			}
			else
			{
				if(runner->m_right)
				{
					runner = runner->m_right;
				}
				else
				{
					new_node = CreateNode(new_data);
					runner->m_right = new_node;
					runner->m_right->m_parent = runner;
					break;
				}
			}
		}

		RBTInsertFixup(new_node);

		m_size++;
		return(SUCCESS);
	}

	void RBTInsertFixup(P_TreeNode node)
	{
		//Code
		P_TreeNode parent = nullptr;
		P_TreeNode uncle = nullptr;
		P_TreeNode g_parent = nullptr;

		if(node->m_parent)
			parent = node->m_parent;
		else
			return;

		if(parent->m_parent)
			g_parent = parent->m_parent;
		else
			return;

		while(RED == parent->m_color)
		{
			//If Parent on left side
			if (parent == g_parent->m_left)
			{
				uncle = g_parent->m_right;

				//Case 2 and case 3
				if(nullptr == uncle || BLACK == uncle->m_color)
				{
					//Case 3
					//Node and Uncle on same side
					//Rotate Parent on its side
					if(node == parent->m_right)
						parent = LeftRotate(parent);
					

					//Case 2
					//Node and Uncle on Opposize side
					//Rotate G.Parent on Uncle's side
					RightRotate(g_parent);
					parent->m_color = BLACK;
					g_parent->m_color = RED;
				}
				else //Case 1
				{
					if(uncle)
						uncle->m_color = BLACK;
					parent->m_color = BLACK;
					g_parent->m_color = RED;

					node = g_parent;
				}
			}
			else //Parent is on right side
			{
				uncle = g_parent->m_left;

				//Case 2 and Case 3
				if(nullptr == uncle || BLACK == uncle->m_color)
				{
					//Case 3
					//Node and Uncle on same side
					//Rotate Parent on its side
					if(node == parent->m_left)
						parent = RightRotate(parent);

					//Case 2
					//Node and Uncle on Opposite side
					//Rotate G.Parent on Uncle's side
					LeftRotate(g_parent);
					parent->m_color = BLACK;
					g_parent->m_color = RED;
				}
				else //Case 1
				{
					if(uncle)
						uncle->m_color = BLACK;
					
					parent->m_color = BLACK;
					g_parent->m_color = RED;
					node = g_parent;
				}
			}

			if(node->m_parent)
				parent = node->m_parent;
			else
			{
				m_root = node;
				break;
			}

			if(parent->m_parent)
				g_parent = parent->m_parent;
			else
			{
				m_root = parent;
				break;
			}
		}

		m_root->m_color = BLACK;
	}

	DATA_T GenericRemove(DATA_T e_data)
	{
		//Code

		P_TreeNode node = LocateNode(e_data);

		if(nullptr == node)
		{
			std::cout << "ERROR: Existing Data Not Found" << std::endl;
			return((DATA_T)nullptr);
		}

		DATA_T to_return_data = node->m_data;

		while(true)
		{
			if(node->m_left)
			{
				P_TreeNode predecessor = Predecessor(node);

				node->m_data = predecessor->m_data;

				node = predecessor;
			}
			else if(node->m_right) 
			{
				P_TreeNode successor = Successor(node);

				node->m_data = successor->m_data;

				node = successor;
			}
			else
			{
				break;
			}
		}

		if(nullptr == node->m_parent)
		{
			m_root = nullptr;
		}
		else if(node == node->m_parent->m_left)
		{
			node->m_parent->m_left = nullptr;
		}
		else
		{
			node->m_parent->m_right = nullptr;
		}

		delete(node);

		m_size--;
		return(to_return_data);
	}

	P_TreeNode RightRotate(P_TreeNode node)
	{
		//Code
		P_TreeNode left = node->m_left;

		node->m_left = left->m_right;
		if(node->m_left)
			node->m_left->m_parent = node;

		left->m_right = node;
		left->m_parent = node->m_parent;

		if(node->m_parent)
		{
			if(node == node->m_parent->m_right)
				node->m_parent->m_right = left;
			else
				node->m_parent->m_left = left;
		}
		node->m_parent = left;

		return(left);
	}

	P_TreeNode LeftRotate(P_TreeNode node)
	{
		//Code
		P_TreeNode right = node->m_right;

		node->m_right = right->m_left;
		
		if(node->m_right)
			node->m_right->m_parent = node;

		right->m_left = node;
		right->m_parent = node->m_parent;

		if(node->m_parent)
		{
			if(node == node->m_parent->m_left)
				node->m_parent->m_left = right;
			else
				node->m_parent->m_right = right;
		}

		node->m_parent = right;

		return(right);
	}

	void InOrder(P_TreeNode node)
	{
		//Code
		if(node->m_left)
			InOrder(node->m_left);
	
		std::cout << "{";
		std::cout << node->m_data;
		std::cout << "|" << ( node->m_color ? "RED" : "BLACK");
		std::cout << "}->";

		if(node->m_right)
			InOrder(node->m_right);
	}

	void PreOrder(P_TreeNode node)
	{
		//Code
		std::cout << "{";
		std::cout << node->m_data;
		std::cout << "|" << ( node->m_color ? "RED" : "BLACK");
		std::cout << "}->";

		if(node->m_left)
			PreOrder(node->m_left);

		if(node->m_right)
			PreOrder(node->m_right);
	}

	void PostOrder(P_TreeNode node)
	{
		//Code
		if(node->m_left)
			PostOrder(node->m_left);

		if(node->m_right)
			PostOrder(node->m_right);
	
		std::cout << "{";
		std::cout << node->m_data;
		std::cout << "|" << ( node->m_color ? "RED" : "BLACK");
		std::cout << "}->";
	}

	void PostOrderDestroy(P_TreeNode node)
	{
		//Code
		if(node->m_left)
			PostOrderDestroy(node->m_left);

		if(node->m_right)
			PostOrderDestroy(node->m_right);
	
		std::cout << "Deleting: ";
		std::cout << node->m_data;
		std::cout << std::endl;

		delete(node);
		node = nullptr;
	}

public:

    //Constructor
	MV_RBT() : m_root(nullptr), m_size(0)
	{}

    //Destructor
	~MV_RBT()
	{
		//Code
		std::cout << std::endl;
		PostOrderDestroy(m_root);
	}

    /*
        @function: Insert Data in RBT
        @identifier: MVRBTInsert
        @params: 1.New Data
        @return: Status 
    */
	status_t MVRBTInsert(DATA_T new_data)
	{
		//Code

		try 
		{
			if(nullptr == m_root)
			{
				m_root = CreateNode(new_data);
				m_root->m_parent = nullptr;
				m_size++;
			}
			else
			{
				GenericInsert(new_data);
			}
		}
		catch(OutOfMemory e)
		{
			std::cout << "Exception : Out Of Memory" << std::endl;
		}

		return(SUCCESS);
	}

    /*
        @function: Remove Data from RBT
        @identifier: MVRBTRemove
        @params: 1. Existing Data to be Removed
        @return: Deleted Data
    */
	DATA_T MVRBTRemove(DATA_T e_data)
	{
		//Code

		if(0 == m_size)
		{
			std::cout << "ERROR: No data to remove in RBT." << std::endl;
			return((DATA_T)nullptr);
		}

		return(GenericRemove(e_data));
	}

    /*
        @function: Inorder RBT Traversal
        @identifier: MVRBTInOrder
        @return: void
    */
	void MVRBTInOrder()
	{
		//Code
		std::cout << std::endl << "Inorder Traversal : " << std::endl;
		std::cout << "{START}->";
		InOrder(m_root);
		std::cout << "{END}" << std::endl;
	}

    /*
        @function: Preorder RBT Traversal
        @identifier: MVRBTPreOrder
        @return: void
    */
	void MVRBTPreOrder()
	{
		//Code
		std::cout << std::endl << "Preorder Traversal : " << std::endl;
		std::cout << "{START}->";
		PreOrder(m_root);
		std::cout << "{END}" << std::endl;
	}

    /*
        @function: Postorder RBT Traversal
        @identifier: MVRBTPostOrder
        @return: void
    */
	void MVRBTPostOrder()
	{
		//Code
		std::cout << std::endl << "Postorder Traversal : " << std::endl;
		std::cout << "{START}->";
		PostOrder(m_root);
		std::cout << "{END}" << std::endl;
	}
};

