
/*
    @file: client.c
    @brief: Client side file for usage of Insertion Sort Algorithm
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 09 July 2023 (Sunday) 10:03 PM  
*/

#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_dcll.h"

p_mv_dcll_t list = NULL;

void PrintList(p_mv_dcll_t list)
{
	//Code
	fprintf(stdout, "List: {START}->");
	for(long long le = 0; le < MVDCLLSize(list); ++le)
	{
		fprintf(stdout, "{%lld}->", (long long)MVDCLLDataAt(list, le));
	}
	fprintf(stdout, "{END}\n\n");
}

status_t CompareEquality(data_t data1, data_t data2)
{
	//Code
	if((long long)data1 == (long long)data2)
		return(SUCCESS);

	return(FAILURE);
}

status_t CompareInequality(data_t data1, data_t data2)
{
	//Code
	if((long long)data1 < (long long)data2)
		return(SUCCESS);

	return(FAILURE);
}

void DeleteData(data_t data)
{
	fprintf(stdout, "Deleting Data = %lld\n", (long long) data);
}

int main(void)
{
	//Code
	list = MVCreateDCLL();

	for(long long le = 1; le <= 10; ++le)
	{
		MVDCLLInsertBack(list, (data_t)(le * 10) );
	}
	fprintf(stdout, "After MVDCLLInsertBack:\n");
	PrintList(list);

	MVDCLLInsertionSortN(list, CompareInequality, MVDCLLSize(list) / 2);

	fprintf(stdout, "After List Sort:\n");
	PrintList(list);

	MVDCLLInsertionSort(list, CompareInequality);

	fprintf(stdout, "After List Sort:\n");
	PrintList(list);

	exit(SUCCESS);
}

