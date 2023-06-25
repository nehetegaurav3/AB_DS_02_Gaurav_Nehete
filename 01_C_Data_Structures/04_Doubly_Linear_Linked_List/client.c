
/*
	@file: client.c
	@brief: Client Side file for Doubly Linear Linked List Usage
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 21 June 2023 (Wednesday) 07:40 PM
*/

//	Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_dll.h"

//	Global Objects
p_dll_t 	list1;

//	Client Functions
void print_list(p_dll_t list)
{
	fprintf(stdout,"{START}->");
	for(long long le = 0; le < ListSize(list); ++le)
	{
		fprintf(stdout, "{%lld}->", (long long)ListDataAt(list, le));
	}
	fprintf(stdout,"{END}\n\n");
}

status_t compare_data(data_t data1, data_t data2)
{
	if((long long)data1 == (long long)data2)
		return(SUCCESS);

	return(FAILURE);
}

void delete_data(data_t data)
{
	// Code
	fprintf(stdout, "Data Deleted = %lld\n", (long long)data);
}

int main(void)
{
	// Code
	list1 = CreateDLL();

	ListInsertFront(list1, (data_t)11);
	ListInsertFront(list1, (data_t)22);
	ListInsertFront(list1, (data_t)33);

	fprintf(stdout, "After Insert Front:\n");
	print_list(list1);
	
	ListInsertBack(list1, (data_t)100);
	ListInsertBack(list1, (data_t)200);
	ListInsertBack(list1, (data_t)300);

	fprintf(stdout, "After Insert Back:\n");
	print_list(list1);

	ListInsertAt(list1, (data_t)1001, 2);
	fprintf(stdout, "After Insert At:\n");
	print_list(list1);

	ListInsertAt(list1, (data_t)111, 1);
	fprintf(stdout, "After Insert At:\n");
	print_list(list1);

	ListInsertAt(list1, (data_t)1818, 4);
	fprintf(stdout, "After Insert At:\n");
	print_list(list1);

	ListInsertBefore(list1, (data_t)1001, (data_t)9898, compare_data);
	ListInsertBefore(list1, (data_t)111, (data_t)666, compare_data);
	ListInsertBefore(list1, (data_t)1818, (data_t)1616, compare_data);
	ListInsertBefore(list1, (data_t)468431468468, (data_t)2002, compare_data);
	fprintf(stdout, "After Insert Before :\n");
	print_list(list1);

	ListInsertAfter(list1, (data_t)22, (data_t)28, compare_data);
	ListInsertAfter(list1, (data_t)11, (data_t)57, compare_data);
	ListInsertAfter(list1, (data_t)666, (data_t)772, compare_data);
	ListInsertAfter(list1, (data_t)9343835, (data_t)1001, compare_data);
	fprintf(stdout, "After Insert After :\n");
	print_list(list1);

	delete_data(ListRemoveFront(list1));
	delete_data(ListRemoveFront(list1));
	delete_data(ListRemoveFront(list1));
	fprintf(stdout, "After Remove Front :\n");
	print_list(list1);

	delete_data(ListRemoveBack(list1));
	delete_data(ListRemoveBack(list1));
	delete_data(ListRemoveBack(list1));
	fprintf(stdout, "After Remove Back :\n");
	print_list(list1);

	delete_data(ListRemoveAfter(list1, (data_t)57, compare_data));
	fprintf(stdout, "After Remove After :\n");
	print_list(list1);

	delete_data(ListRemoveBefore(list1, (data_t)28, compare_data));
	fprintf(stdout, "After Remove Before :\n");
	print_list(list1);

	delete_data(ListRemoveAt(list1, 0));
	delete_data(ListRemoveAt(list1, ListSize(list1)-1));
	delete_data(ListRemoveAt(list1, 2));
	delete_data(ListRemoveAt(list1, 772));
	fprintf(stdout, "After List Remove At :\n");
	print_list(list1);

	fprintf(stdout, "\n===== CLEANING THE HEAP MEMORY =====\n\n");
	ListDestroy(&list1, delete_data);
	print_list(list1);

	exit(SUCCESS);
}
