
/*
    @file: client.c
    @brief: Client side file for Singly Circular Linked List usage
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 21 June 2023 (Wednesday) 05:55 PM    
*/

//Headers
#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_scll.h"

//Global Objects
p_scll_t list1;

//Client Functions
static void PrintList(p_scll_t list)
{
    fprintf(stdout, "{START}->");
    for(long long le = 0; le < ListSize(list); ++le)
    {
        fprintf(stdout, "{%lld}->", (long long)ListDataAt(list, le));
    }
    fprintf(stdout, "->{END}\n\n");
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
	fprintf(stdout, "Data Deleted = %lld\n\n", (long long)data);
}

//Main Function
int main(void)
{
	// Code
	list1 = CreateSCLL();

	ListInsertFront(list1, (data_t)10);
	ListInsertFront(list1, (data_t)20);
	ListInsertFront(list1, (data_t)30);

	fprintf(stdout, "After Insert Front:\n");
	PrintList(list1);

	ListInsertBack(list1, (data_t)101);
	ListInsertBack(list1, (data_t)202);
	ListInsertBack(list1, (data_t)303);

	fprintf(stdout, "After Insert Back:\n");
	PrintList(list1);

	ListInsertAt(list1, (data_t)555, 1);
	fprintf(stdout, "After Insert At:\n");
	PrintList(list1);

	ListInsertAt(list1, (data_t)919, 3);
	fprintf(stdout, "After Insert At:\n");
	PrintList(list1);

	ListInsertAt(list1, (data_t)1212, 5);
	fprintf(stdout, "After Insert At:\n");
	PrintList(list1);

	ListInsertBefore(list1, (data_t)1212, (data_t)9999, compare_data);
	ListInsertBefore(list1, (data_t)919, (data_t)111, compare_data);
	ListInsertBefore(list1, (data_t)555, (data_t)3232, compare_data);
	ListInsertBefore(list1, (data_t)129431231233, (data_t)9999, compare_data);
	fprintf(stdout, "After Insert Before :\n");
	PrintList(list1);

	ListInsertAfter(list1, (data_t)20, (data_t)22, compare_data);
	ListInsertAfter(list1, (data_t)10, (data_t)55, compare_data);
	ListInsertAfter(list1, (data_t)111, (data_t)222, compare_data);
	ListInsertAfter(list1, (data_t)999, (data_t)10, compare_data);
	fprintf(stdout, "After Insert After :\n");
	PrintList(list1);

	delete_data(ListRemoveFront(list1));
	delete_data(ListRemoveFront(list1));
	delete_data(ListRemoveFront(list1));
	fprintf(stdout, "After Remove Front :\n");
	PrintList(list1);

	delete_data(ListRemoveBack(list1));
	delete_data(ListRemoveBack(list1));
	delete_data(ListRemoveBack(list1));
	fprintf(stdout, "After Remove Back :\n");
	PrintList(list1);

    delete_data(ListRemoveAt(list1, 0));
	delete_data(ListRemoveAt(list1, ListSize(list1)-1) );
	delete_data(ListRemoveAt(list1, 2));
	delete_data(ListRemoveAt(list1, 999));
	fprintf(stdout, "After List Remove At :\n");
	PrintList(list1);

    delete_data(ListRemoveBefore(list1, (data_t)919, compare_data));
	fprintf(stdout, "After Remove Before :\n");
	PrintList(list1);
    
	delete_data(ListRemoveAfter(list1, (data_t)919, compare_data));
	fprintf(stdout, "After Remove After :\n");
	PrintList(list1);
    
    fprintf(stdout, "\n===== CLEANING THE HEAP MEMORY =====\n\n");
	ListDestroy(&list1, delete_data);
	PrintList(list1);

	exit(SUCCESS);
}
