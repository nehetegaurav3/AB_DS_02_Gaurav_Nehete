
/*
    @file: client.c
    @brief: Client side file for usage of Quick Sort Algorithm
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 21 July 2023 (Friday) 06:17 PM  
*/
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dcll.h"

p_mv_dcll_t list = NULL;

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
	list = MVCreateDCLL();

	for(long long le = 1; le <= 10; ++le)
	{
		MVDCLLInsertFront(list, (data_t)(le * 10));
	}
	fprintf(stdout, "After MVDCLLInsertFront:\n");
	print_list(list);

	MVDCLLQuickSort(list, compare_inequality);
	fprintf(stdout, "After List Sort:\n");
	print_list(list);

	exit(SUCCESS);
}

