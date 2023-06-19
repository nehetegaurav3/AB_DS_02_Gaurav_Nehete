
/*
	@file: client.c
	@brief: Client Side file for Single Linear List Usage
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 19 June 2023 (Monday) 02:22 PM
*/

//	Headers
#include <stdio.h>
#include <stdlib.h>

#include "gn_sll.h"

//	Global Objects
p_sll_t 	list1;

//	Client Functions
void print_list(p_sll_t list)
{
	fprintf(stdout,"{START}->");
	for(long long le = 0; le < ListSize(list); ++le)
	{
		fprintf(stdout, "{%lld}->", (long long)ListDataAt(list, le));
	}
	fprintf(stdout,"{END}\n\n\n");
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
	list1 = create_sll();

	ListInsertFront(list1, (data_t)11);
	ListInsertFront(list1, (data_t)22);
	ListInsertFront(list1, (data_t)33);

	fprintf(stdout, "After InsertFront:\n");
	print_list(list1);

	ListInsertBack(list1, (data_t)100);
	ListInsertBack(list1, (data_t)200);
	ListInsertBack(list1, (data_t)300);

	fprintf(stdout, "After InsertBack:\n");
	print_list(list1);

	ListInsertAt(list1, (data_t)1001, 2);
	fprintf(stdout, "After InsertAt:\n");
	print_list(list1);

	ListInsertAt(list1, (data_t)111, 1);
	fprintf(stdout, "After InsertAt:\n");
	print_list(list1);

	ListInsertAt(list1, (data_t)1818, 4);
	fprintf(stdout, "After InsertAt:\n");
	print_list(list1);

	ListInsertBefore(list1, (data_t)1001, (data_t)9898, compare_data);
	ListInsertBefore(list1, (data_t)111, (data_t)666, compare_data);
	ListInsertBefore(list1, (data_t)1818, (data_t)1616, compare_data);
	ListInsertBefore(list1, (data_t)468431468468, (data_t)2002, compare_data);
	fprintf(stdout, "After InsertBefore :\n");
	print_list(list1);

	ListInsertAfter(list1, (data_t)22, (data_t)28, compare_data);
	ListInsertAfter(list1, (data_t)11, (data_t)57, compare_data);
	ListInsertAfter(list1, (data_t)666, (data_t)772, compare_data);
	ListInsertAfter(list1, (data_t)9343835, (data_t)1001, compare_data);
	fprintf(stdout, "After InsertAfter :\n");
	print_list(list1);

	delete_data(ListRemoveFront(list1));
	delete_data(ListRemoveFront(list1));
	delete_data(ListRemoveFront(list1));
	fprintf(stdout, "After RemoveFront :\n");
	print_list(list1);

	delete_data(ListRemoveBack(list1));
	delete_data(ListRemoveBack(list1));
	delete_data(ListRemoveBack(list1));
	fprintf(stdout, "After RemoveBack :\n");
	print_list(list1);

	delete_data(ListRemoveAfter(list1, (data_t)57, compare_data));
	fprintf(stdout, "After RemoveAfter :\n");
	print_list(list1);

	delete_data(ListRemoveBefore(list1, (data_t)28, compare_data));
	fprintf(stdout, "After RemoveBefore :\n");
	print_list(list1);

	delete_data(ListRemoveAt(list1, 0));
	delete_data(ListRemoveAt(list1, ListSize(list1)-1));
	delete_data(ListRemoveAt(list1, 2));
	delete_data(ListRemoveAt(list1, 772));
	fprintf(stdout, "After ListRemoveAt :\n");
	print_list(list1);

	ListDestroy(&list1, delete_data);
	print_list(list1);

	exit(SUCCESS);
}
