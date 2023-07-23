
/*
    @file: mv_quicksort.c
    @brief: Source code file for definitions of Interface functions of Quick Sort Algorithm
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 21 July 2023 (Friday) 02:34 PM 
*/

#include    <stdio.h>
#include    <stdlib.h>

#include    "mv_quicksort.h"

//Helper Function
long long Partition(void* ds, long long first, long long last, COMPAREDATAPROC pcomparedataproc, GETDATAPROC pgetdataproc, SETDATAPROC psetdataproc)
{
	//Code
    data_t pivot = pgetdataproc(ds, last);

	long long i = first;
	long long j = first;

	for(i = first; i < last; ++i)
	{
		if(SUCCESS == pcomparedataproc(pgetdataproc(ds, i), pivot))
		{
			data_t temp = pgetdataproc(ds, i);			    //	temp = a[i]
			psetdataproc(ds, pgetdataproc(ds, j), i);	    //	a[i] = a[j]
			psetdataproc(ds, temp, j);					    //	a[j] = temp
			j++;
		}
	}

	data_t temp = pgetdataproc(ds, j);				        //	temp = a[j]
	psetdataproc(ds, pgetdataproc(ds, last), j);	        //	a[j] = a[last]
	psetdataproc(ds, temp, last);					        //	a[last] = temp

	return(j);
}

//Interface Function
/*
    @function: To Sort Using Quick Sort Algorithm
    @identifier: MVQuickSort
    @params: 1. Pointer to Data Stucture
             2. Start Index
             3. End Index
             4. Compare Proc 
             5. Get Data Proc
             6. Set Data Proc
    @return: Status
*/
extern void MVQuickSort(void* ds, long long start, long long end, 
                        COMPAREDATAPROC pcomparedataproc, GETDATAPROC pgetdataproc, 
                        SETDATAPROC psetdataproc)
{
    //Code
    if(end > start)
	{
        long long mid = Partition(ds, start, end, pcomparedataproc, pgetdataproc, psetdataproc);
        
        MVQuickSort(ds, start, mid-1, pcomparedataproc, pgetdataproc, psetdataproc);
        MVQuickSort(ds, mid+1, end, pcomparedataproc, pgetdataproc, psetdataproc);
	}
}
