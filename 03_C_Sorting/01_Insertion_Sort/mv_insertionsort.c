
/*
    @file: mv_insertion.c
    @brief: Source code file for definitions of Interface functions of Insertion Sort Algorithm
    @author: Gaurav Nehete(nehetegaurav3@gmail.com)
    @date: 09 July 2023 (Sunday) 06:03 PM  
*/

//Headers
#include "mv_insertionsort.h"

extern void MVInsertionSort(void* data_structure, 
							long long size, 
							COMPAREDATAPROC CompareProc, 
							GETDATAPROC GetDataProc, 
							SETDATAPROC SetDataProc)
{
	//Code
	//ole -> Outer Loop Enumerator
	for( long long ole = 1; ole < size; ++ole )
	{
		data_t key = GetDataProc(data_structure, ole);

		long long ile = ole-1;
										// data_structure[ile]
		while( ile >= 0 && SUCCESS == CompareProc( GetDataProc(data_structure, ile), key ) )
		{
			// data_structure[ile + 1] = data_structure[ile]
			SetDataProc(data_structure, GetDataProc(data_structure, ile), ile+1);
			ile--;
		}

		SetDataProc(data_structure, key, ile+1);
	}
}
