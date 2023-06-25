
/*
    @file: client.c
    @brief: Client side file for Doubly Circular Linked List usage
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 24 June 2023 (Saturday) 01:55 PM    
*/

//Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_dcll.h"

//Global Objects
p_mv_dcll_t list1 = NULL;

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

status_t compare_data(data_t data1, data_t data2)
{
	//Code
	if((long long)data1 == (long long)data2)
		return(SUCCESS);

	return(FAILURE);
}

void delete_data(data_t data)
{
	fprintf(stdout, "Deleting Data = %lld\n", (long long)data);
}

int main(void)
{
	// Code
	list1 = MVCreateDCLL();

	MVDCLLInsertFront(list1, (data_t)10);
	MVDCLLInsertFront(list1, (data_t)20);
	MVDCLLInsertFront(list1, (data_t)30);

	fprintf(stdout, "After Insert Front:\n");
	PrintList(list1);

	MVDCLLInsertBack(list1, (data_t)101);
	MVDCLLInsertBack(list1, (data_t)202);
	MVDCLLInsertBack(list1, (data_t)303);

	fprintf(stdout, "After Insert Back:\n");
	PrintList(list1);

	MVDCLLInsertAt(list1, (data_t)555, 1);
	fprintf(stdout, "After Insert At:\n");
	PrintList(list1);

	MVDCLLInsertAt(list1, (data_t)919, 3);
	fprintf(stdout, "After Insert At:\n");
	PrintList(list1);

	MVDCLLInsertAt(list1, (data_t)1212, 5);
	fprintf(stdout, "After Insert At:\n");
	PrintList(list1);

	MVDCLLInsertBefore(list1, (data_t)1212, (data_t)9999, compare_data);
	MVDCLLInsertBefore(list1, (data_t)919, (data_t)111, compare_data);
	MVDCLLInsertBefore(list1, (data_t)555, (data_t)3232, compare_data);
	MVDCLLInsertBefore(list1, (data_t)129431231233, (data_t)9999, compare_data);
	fprintf(stdout, "After Insert Before :\n");
	PrintList(list1);

	MVDCLLInsertAfter(list1, (data_t)20, (data_t)22, compare_data);
	MVDCLLInsertAfter(list1, (data_t)10, (data_t)55, compare_data);
	MVDCLLInsertAfter(list1, (data_t)111, (data_t)222, compare_data);
	MVDCLLInsertAfter(list1, (data_t)999, (data_t)10, compare_data);
	fprintf(stdout, "After Insert After :\n");
	PrintList(list1);

	delete_data(MVDCLLRemoveFront(list1));
	delete_data(MVDCLLRemoveFront(list1));
	delete_data(MVDCLLRemoveFront(list1));
	fprintf(stdout, "After Remove Front :\n");
	PrintList(list1);

	delete_data(MVDCLLRemoveBack(list1));
	delete_data(MVDCLLRemoveBack(list1));
	delete_data(MVDCLLRemoveBack(list1));
	fprintf(stdout, "After Remove Back :\n");
	PrintList(list1);

    delete_data(MVDCLLRemoveAt(list1, 0));
	delete_data(MVDCLLRemoveAt(list1, MVDCLLSize(list1)-1) );
	delete_data(MVDCLLRemoveAt(list1, 2));
	delete_data(MVDCLLRemoveAt(list1, 999));
	fprintf(stdout, "After List Remove At :\n");
	PrintList(list1);

    delete_data(MVDCLLRemoveBefore(list1, (data_t)919, compare_data));
	fprintf(stdout, "After Remove Before :\n");
	PrintList(list1);
    
	delete_data(MVDCLLRemoveAfter(list1, (data_t)919, compare_data));
	fprintf(stdout, "After Remove After :\n");
	PrintList(list1);
    
    fprintf(stdout, "\n===== CLEANING THE HEAP MEMORY =====\n\n");
	MVDCLLDestroy(&list1, delete_data);
	PrintList(list1);

	exit(SUCCESS);
}

