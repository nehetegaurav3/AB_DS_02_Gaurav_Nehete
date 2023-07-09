
/*
	@file: mv_insertionsort.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Insertion Sort Algorithm
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 09 July 2023 (Sunday) 05:32 PM
*/

//Conditional Compilation
#ifndef     _MV_INSERTIONSORT_H
#define     _MV_INSERTIONSORT_H

#ifndef	    DEFS
#define	    DEFS

#define	    SUCCESS     0
#define     FAILURE     1

typedef	    void*	data_t;
typedef     int 	status_t;

#endif      // DEFS

typedef     status_t(*COMPAREDATAPROC)(data_t, data_t);
typedef	    data_t(*GETDATAPROC)(void* ds, long long index);
typedef	    data_t(*SETDATAPROC)(void* ds, data_t data, long long index);

/*
    @function: Sorting a Linear Data Structure using Insertion Sort 
    @identifier: MVInsertionSort
    @params: 1. data_structure
        	 2. size
             3. GetDataProc Callback Function
    @returns: void
*/
extern void MVInsertionSort(void* data_structure, long long size, COMPAREDATAPROC, GETDATAPROC, SETDATAPROC);

#endif // _MV_INSERTIONSORT_H
