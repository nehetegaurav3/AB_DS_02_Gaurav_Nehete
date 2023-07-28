
/*
    @file: client.cpp
    @brief: Usage of AVL Tree implementation using CPP
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 28 July 2023 (Friday) 06:08 PM 
*/

//Headers
#include	<iostream>

#include	"mv_avl.hpp"

MV_AVL<long long>* tree = nullptr;

int main(int argc, char** argv, char** envp)
{
	//Code
	tree = new MV_AVL<long long>();

	tree->MVAVLInsert(100);
	tree->MVAVLInsert(150);
	tree->MVAVLInsert(50);
	tree->MVAVLInsert(10);
	tree->MVAVLInsert(75);
	tree->MVAVLInsert(200);
	tree->MVAVLInsert(125);
	tree->MVAVLInsert(250);
	tree->MVAVLInsert(175);

	std::cout << "AVL After Insert: " << std::endl;
	tree->MVAVLInOrder();
	tree->MVAVLPreOrder();
	tree->MVAVLPostOrder();

	std::cout << "AVL After Remove: " << std::endl;
	tree->MVAVLRemove(100);

	tree->MVAVLInOrder();
	tree->MVAVLPreOrder();
	tree->MVAVLPostOrder();

	delete(tree);
	tree = nullptr;

	exit(0);
}

