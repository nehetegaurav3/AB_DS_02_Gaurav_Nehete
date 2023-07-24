
/*
    @file: client.cpp
    @brief: Usage of Binary Search Tree implementation using CPP
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 24 July 2023 (Monday) 06:08 PM 
*/

//Headers
#include	<iostream>

#include	"mv_bst.hpp"

MV_BST<long long>* tree = nullptr;

int main(int argc, char** argv, char** envp)
{
	//Code
	tree = new MV_BST<long long>();

	tree->MVBSTInsert(100);
	tree->MVBSTInsert(150);
	tree->MVBSTInsert(50);
	tree->MVBSTInsert(10);
	tree->MVBSTInsert(75);
	tree->MVBSTInsert(200);
	tree->MVBSTInsert(125);
	tree->MVBSTInsert(250);
	tree->MVBSTInsert(175);

	std::cout << "BST After Insert: " << std::endl;
	tree->MVBSTInOrder();
	tree->MVBSTPreOrder();
	tree->MVBSTPostOrder();

	std::cout << "BST After Remove: " << std::endl;
	tree->MVBSTRemove(100);

	tree->MVBSTInOrder();
	tree->MVBSTPreOrder();
	tree->MVBSTPostOrder();

	delete(tree);
	tree = nullptr;

	exit(0);
}

