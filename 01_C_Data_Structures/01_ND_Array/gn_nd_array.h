
/*
	@file: gn_nd_array.h
	@brief:	Header file for the declaration of interface functions and type definition for ND Array
	@author: Gaurav Nehete (nehetegaurav3@gmail.com)
	@date: 18 June 2023 (Sunday) 11:12 AM
*/

//  Conditional Compilation
#ifndef	_GN_ND_ARRAY_H
#define	_GN_ND_ARRAY_H

//  Constant Literals
#define     SUCCESS     0
#define     FAILURE     1

struct NDArray;

//	Typedefs
typedef		void*	data_t;
typedef     struct NDArray      ndarray_t;
typedef     struct NDArray*     p_ndarray_t;
typedef     struct NDArray**    pp_ndarray_t;

//	Struct Type Definition
struct NDArray
{
	data_t*	base_address;	//	Structure of actual array

	long *dimension_array;
	long *jumpbytes_array;

	size_t array_size;
    size_t no_of_dimension;
};

#define 	SIZE_NDARRAY	 (sizeof(ndarray_t))

// Interface Functions

/*
	@function: 	create_array
	@param:	1.	No Of Dimensions
			2.	Size of each Dimension
	@return:	Object of Created Array
	@description:	This function will create an object of struct NDArray and assign the necessary values and return the pointer to that object
*/
extern	struct NDArray*	create_array(size_t	no_of_dimension, ...);	//	...	also called 'Elipses' is used for accepting variable number of arguments

/*
	@function:	ndarray_set_data
	@param:	1.	Array to set data
				2.	data to set
				3.	Indices of each dimension
	@return:	Status
	@description:	This function will check for each index and if all indices are correct than this function will store data to that address
 */
extern	int 	ndarray_set_data(struct NDArray*, data_t, ...);

/*
	@function:	ndarray_get_data
	@param:	1.	Array to get data from
				2.	Indices of each dimension
	@return:	Required data
	@description:	This function will return the valid data at the required address calculated using the indices
 */
extern	data_t	ndarray_get_data(struct NDArray*, ...);

extern  size_t  nd_array_size(p_ndarray_t array);

extern  void    nd_array_destroy(pp_ndarray_t parray);

#endif	/* _GN_ND_ARRAY_H */
