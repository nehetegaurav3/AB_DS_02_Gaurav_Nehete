
/*
	@file: client.c
	@brief: Source code file for the client side use of ND_Array
	@author: Gaurav Nehete(nehetegaurav3@gmail.com)
	@date: 18 June 2023 (Sunday) 02:22 PM
*/

//	Headers
#include <stdio.h>
#include <stdlib.h>

#include "gn_nd_array.h"

//9D_Array ==> int arr[][][][][][][][][];

//	Main Function
int main(void)
{
	// Code
	long long value = 1;
	
	p_ndarray_t array_9D = create_array(9, 5, 8, 6, 2, 3, 5, 5, 3, 2);
	printf("\n");
	
	value = 1;
	for(int index1 = 0; index1 < 5; ++index1)
		for(int index2 = 0; index2 < 8; ++index2)
			for(int index3 = 0; index3 < 6; ++index3)
				for(int index4 = 0; index4 < 2; ++index4)
					for(int index5 = 0; index5 < 3; ++index5)
						for(int index6 = 0; index6 < 5; ++index6)
							for(int index7 = 0; index7 < 5; ++index7)
								for(int index8 = 0; index8 < 3; ++index8)
									for(int index9 = 0; index9 < 2; ++index9)
										{
											printf("Assigining = %lld\n", value);
											ndarray_set_data(array_9D, (data_t)value, 
														index1, index2, index3, 
														index4, index5, index6,
														index7, index8, index9);
											value += 1;
										}

	for(int index1 = 0; index1 < 5; ++index1)
		for(int index2 = 0; index2 < 8; ++index2)
			for(int index3 = 0; index3 < 6; ++index3)
				for(int index4 = 0; index4 < 2; ++index4)
					for(int index5 = 0; index5 < 3; ++index5)
						for(int index6 = 0; index6 < 5; ++index6)
							for(int index7 = 0; index7 < 5; ++index7)
								for(int index8 = 0; index8 < 3; ++index8)
									for(int index9 = 0; index9 < 2; ++index9)
										{
											printf("array_9D[%d][%d][%d][%d][%d][%d][%d][%d][%d] = %lld\n",
													index1, index2, index3, 
													index4, index5, index6,
													index7, index8, index9, 
													(long long)ndarray_get_data(array_9D, 
													index1, index2, index3, 
													index4, index5, index6,
													index7, index8, index9));
											value += 1;
										}
	nd_array_destroy(&array_9D);

	return(EXIT_SUCCESS);
}
