
/*
    @file: mv_mergesort.c
    @brief: Source code file for definitions of Interface functions of Merge Sort Algorithm
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 20 July 2023 (Thursday) 12:03 PM 
*/

#include <stdio.h>
#include <stdlib.h>

#include "mv_mergesort.h"


//Helper Functions
static void Merge(  void* ds, long long first, long long mid, long long last,
				    COMPAREDATAPROC pcompareproc, GETDATAPROC pgetdataproc, SETDATAPROC psetdataproc, 
					CREATECOPYPROC pcreatecopyproc, DELETEPROC pdeletproc)
{
	//Code
	void* left = pcreatecopyproc(ds, first, mid);
	void* right = pcreatecopyproc(ds, mid+1, last);

	long long left_index = 0;
	long long right_index = 0;

	long long left_size = (mid - first) + 1;
	long long right_size = (last - (mid+1)) + 1;

	long long index = first;

	while(left_index < left_size && right_index < right_size)
	{
		data_t left_data = pgetdataproc(left, left_index);
		data_t right_data = pgetdataproc(right, right_index);

		if(SUCCESS == pcompareproc(left_data, right_data))
		{
			psetdataproc(ds, left_data, index);
			left_index++;
		}
		else
		{
			psetdataproc(ds, right_data, index);
			right_index++;
		}
		index++;
	}

	while(left_index < left_size)
	{
		data_t left_data = pgetdataproc(left, left_index);
		
		psetdataproc(ds, left_data, index);
		index++;
		left_index++;
	}

	while(right_index < right_size)
	{
		data_t right_data = pgetdataproc(right, right_index);

		psetdataproc(ds, right_data, index);
		index++;
		right_index++;
	}

	pdeletproc(&left);
	pdeletproc(&right);
}

//Interface Function
/*
    @function: To Implement Merge Sort Algorithm
    @identifier: MVMergeSort
    @params:	1. Data Struct
  		    	2. First Index
  			    3. Last Index
     			4. Compare Data Proc
  	    		5. Get Data Proc
  	    		6. Set Data Proc
  		    	7. Copy Proc
  			    8. Delete Data Structure Proc
    @returns: void
*/
extern void MVMergeSort(void* ds, long long first, long long last, 
						COMPAREDATAPROC pcompareproc, GETDATAPROC pgetdataproc, SETDATAPROC psetdataproc, 
						CREATECOPYPROC pcreatecopyproc, DELETEPROC pdeletproc)
{
	//Code
	if (last > first)
	{
		long long mid = ((last - first) / 2) + first;

		MVMergeSort(ds, first, mid, pcompareproc, pgetdataproc, psetdataproc, pcreatecopyproc, pdeletproc);
		MVMergeSort(ds, mid+1, last, pcompareproc, pgetdataproc, psetdataproc, pcreatecopyproc, pdeletproc);

		Merge(ds, first, mid, last, pcompareproc, pgetdataproc, psetdataproc, pcreatecopyproc, pdeletproc);
	}
}

