
/*
	@file: nd_array.c
	@brief:	Source Code file for the definitions of interface and helper functions for ND Array
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 18 June 2023 (Sunday) 12:02 PM
*/

//	Headers
#include	<stdio.h>
#include	<stdlib.h>
#include	<stdarg.h>

#include	"gn_nd_array.h"

//	Helper Function
/*
	function: xmalloc
	params:	1. no_of_bytes
	returns: The address of heap where the memory of 'no_of_bytes' is allocated
	brief: This function will allocate 'no_of_bytes' and check if allocation successful
*/
static void* xmalloc(size_t no_of_bytes)
{
	// Code
	void *p = malloc(no_of_bytes);

	//	Error Checking
	if(NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory\n");
		exit(EXIT_FAILURE);
	}

	return(p);
}

//	Interface Functions
extern struct NDArray*	create_array(size_t	no_of_dimension, ...)	//	Variadic Function
{
	// Code
	p_ndarray_t	p_ndarray = xmalloc(SIZE_NDARRAY);

	//	Allocate the array to store all dimensions;
	p_ndarray->no_of_dimension = no_of_dimension;

	p_ndarray->dimension_array = xmalloc(sizeof(long) * no_of_dimension);

	va_list	arg;
	va_start(arg, no_of_dimension);
	
	for(int le = 0; le < no_of_dimension; ++le)
	{
		p_ndarray->dimension_array[le] = va_arg(arg, long);
	}
	va_end(arg);

	//	Allocate the jump bytes array and assign values to that array.
	p_ndarray->jumpbytes_array = xmalloc(sizeof(long) * no_of_dimension);

	long result = 1;
	
	for(int le = no_of_dimension-1; le >= 0; --le)
	{
		p_ndarray->jumpbytes_array[le] = result;
		result = result * p_ndarray->dimension_array[le];
		if(le == 0)
			p_ndarray->array_size = result * 8;
	}

	//	Allocate the nd_array
	p_ndarray->base_address = xmalloc(result * sizeof(data_t));

	for( int le = 0; le < result; ++le )
		p_ndarray->base_address[le] = NULL;

	return(p_ndarray);
}

extern int ndarray_set_data(struct NDArray* array, data_t new_data, ...)
{
	//	Code
	long* indices = xmalloc(array->no_of_dimension * sizeof(long));

	//	Get all the indices in an array
	va_list arg;
	va_start(arg, new_data);
	
	for(int le = 0; le < array->no_of_dimension; ++le)
	{
		indices[le] = va_arg(arg, long);
	}
	va_end(arg);

	//	Calculate final index using all the indices
	long final_index = 0;
	
	for(int le = 0; le < array->no_of_dimension; ++le)
	{
		final_index = final_index + (indices[le] * array->jumpbytes_array[le]);
	}

	// Store the new_data at final index
	array->base_address[final_index] = new_data;

	free(indices);
	return(SUCCESS);
}

extern data_t ndarray_get_data(struct NDArray* array, ...)
{
	//	Code
	long* indices = xmalloc(array->no_of_dimension * sizeof(long));

	//	Get all the indices in the array
	va_list arg;
	va_start(arg, array);
	for(int le = 0; le < array->no_of_dimension; ++le)
	{
		indices[le] = va_arg(arg, long);
	}
	va_end(arg);

	//	Calculate final index using all the indices
	long final_index = 0;

	for(int le = 0; le < array->no_of_dimension; ++le)
	{
		final_index = final_index + (indices[le] * array->jumpbytes_array[le]);
	}
	free(indices);

	//	Store the new_data at the final index
	return(array->base_address[final_index]);
}


extern size_t nd_array_size(p_ndarray_t array)
{
	//	Code
	return(array->array_size);
}

extern void nd_array_destroy(pp_ndarray_t parray)
{
	// 	Code
	p_ndarray_t array = *parray;	

	if(array->base_address)
	{
		free(array->base_address);
		array->base_address = NULL;
	}

	if(array->jumpbytes_array)
	{
		free(array->jumpbytes_array);
		array->jumpbytes_array = NULL;
	}

	if(array->dimension_array)
	{
		free(array->dimension_array);
		array->dimension_array = NULL;
	}

	if(array)
	{
		free(array);
		array = NULL;
	}

	*parray = NULL;
}
