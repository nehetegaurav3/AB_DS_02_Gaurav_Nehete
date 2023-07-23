
/*
	@file: mv_mergesort.h
	@brief: Header file for declaration of Type Definitions and Interface Functions For Merge Sort Implementation
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 20 July 2023 (Thursday) 11:33 AM
*/

//Conditional Compilation
#ifndef     _MV_MERGE_SORT_H	
#define     _MV_MERGE_SORT_H

#ifndef     DEFS
#define     DEFS

#define     SUCCESS     0
#define     FAILURE     1

//Typedefs
typedef 	void*	data_t;
typedef 	int 	status_t;

typedef     status_t(*COMPAREDATAPROC)(data_t, data_t);
typedef     data_t(*GETDATAPROC)(void* ds, long long index);
typedef     data_t(*SETDATAPROC)(void* ds, data_t data, long long index);

#endif      /* DEFS */

typedef		void*(*CREATECOPYPROC)(void*, ...);
typedef		void(*DELETEPROC)(void** ds);

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
				 		CREATECOPYPROC pcreatecopyproc, DELETEPROC pdeletproc);

#endif      /* _MV_MERGE_SORT_H */
