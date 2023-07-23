
/*
    @file: client.c
    @brief: Client side file for usage of Merge Sort Algorithm
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 23 July 2023 (Sunday) 06:42 PM  
*/
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dcll.h"

p_mv_dcll_t list1 = NULL;
p_mv_dcll_t list2 = NULL;
p_mv_dcll_t list3 = NULL;

void print_list(p_mv_dcll_t list)
{
	//Code
	fprintf(stdout, "List: {START}->");
	for(long long le = 0; le < MVDCLLSize(list); ++le)
	{
		fprintf(stdout, "{%lld}->", (long long)MVDCLLDataAt(list, le));
	}
	fprintf(stdout, "{END}\n\n");
}

status_t compare_equality(data_t data1, data_t data2)
{
	//Code
	if((long long)data1 == (long long)data2)
	{
		return(SUCCESS);
	}

	return(FAILURE);
}

status_t compare_inequality(data_t data1, data_t data2)
{
	//Code
	if((long long)data1 < (long long)data2)
	{
		return(SUCCESS);
	}

	return(FAILURE);
}

void delete_data(data_t data)
{
	fprintf(stdout, "Deleting Data = %lld\n", (long long)data);
}

int main(void)
{
	//Code
	list1 = MVCreateDCLL();
	list2 = MVCreateDCLL();
	list3 = MVCreateDCLL();

	for(long long le = 1; le <= 10; ++le)
	{
		MVDCLLInsertFront(list1, (data_t)(le * 10));
		MVDCLLInsertFront(list2, (data_t)(le * 10));
		MVDCLLInsertFront(list3, (data_t)(le * 10));
	}
	fprintf(stdout, "After MVDCLLInsertFront:\n");
	fprintf(stdout, "List 1: ");
	print_list(list1);
	fprintf(stdout, "List 2: ");
	print_list(list2);
	fprintf(stdout, "List 3: ");
	print_list(list3);

	MVDCLLQuickSort(list1, compare_inequality);
	fprintf(stdout, "After List1 Sort:\n");
	print_list(list1);

	MVDCLLQuickSortN(list2, compare_inequality, 5);
	fprintf(stdout, "After List2 Sort:\n");
	print_list(list2);

	MVDCLLQuickSortSE(list3, compare_inequality, 2, 7);
	fprintf(stdout, "After List3 Sort:\n");
	print_list(list3);

	exit(SUCCESS);
}

