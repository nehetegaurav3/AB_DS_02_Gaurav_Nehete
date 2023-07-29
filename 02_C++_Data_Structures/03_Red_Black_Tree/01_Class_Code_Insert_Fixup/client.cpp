
/*
    @file: client.cpp
    @brief: Usage of Red Black Tree implementation using CPP
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 29 July 2023 (Saturday) 07:18 PM 
*/

//Headers
#include	<iostream>

#include	"mv_rbt.hpp"

MV_RBT<long long>* tree = nullptr;

int main(int argc, char** argv, char** envp)
{
	//Code
	tree = new MV_RBT<long long>();

	tree->MVRBTInsert(100);
	tree->MVRBTInsert(150);
	tree->MVRBTInsert(50);
	tree->MVRBTInsert(10);
	tree->MVRBTInsert(75);
	tree->MVRBTInsert(200);
	tree->MVRBTInsert(125);
	tree->MVRBTInsert(250);
	tree->MVRBTInsert(175);

	std::cout << "RBT After Insert: " << std::endl;
	tree->MVRBTInOrder();
	tree->MVRBTPreOrder();
	tree->MVRBTPostOrder();

	std::cout << "RBT After Remove: " << std::endl;
	tree->MVRBTRemove(100);

	tree->MVRBTInOrder();
	tree->MVRBTPreOrder();
	tree->MVRBTPostOrder();

	delete(tree);
	tree = nullptr;

	exit(0);
}

