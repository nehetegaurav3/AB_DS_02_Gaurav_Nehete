
/*
	@file: mv_quicksort.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Quick Sort Algorithm Implementation
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 23 July 2023 (Sunday) 10:02 AM
*/

// Conditional Compilation
#ifndef	    _MV_QUICKSORT_H
#define	    _MV_QUICKSORT_H

#ifndef     DEFS
#define     DEFS

#define	    SUCCESS     0
#define     FAILURE     1

typedef	    void*	data_t;
typedef	    int 	status_t;

typedef	    status_t(*COMPAREDATAPROC)(data_t, data_t);
typedef	    data_t(*GETDATAPROC)(void* ds, long long index);
typedef	    data_t(*SETDATAPROC)(void* ds, data_t new_data, long long index);

#endif

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
                        SETDATAPROC psetdataproc);

#endif /* _MV_QUICKSORT_H */

