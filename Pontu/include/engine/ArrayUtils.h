/**
 * \file ArrayUtils.h
 * \brief This file define a macro used to generate dynamic array structs and associated functions
 * \author Martin Rouault
 * \date 3/01/2022
 */

#ifndef ARRAY_UTILS_INCLUDED
#define ARRAY_UTILS_INCLUDED

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <errno.h>

/**
 * \brief Generate a dynamic array for type T
 * If you want an int array use
 *	GENERATE_DYNAMIC_ARRAY(int)

 * If you miss a function, write it with a type as int first then rewrite it in the macro
 *	You will need to follow function naming convetions to avoid multiple functions with the same name
 *	Functions in header must be marked as inline
 *	Don't forget antislashes
 */

#define GENERATE_DYNAMIC_ARRAY(T) \
struct array_##T { \
	T* elems; \
	size_t size; \
	size_t space; \
}; \
\
/*Contruct an empty array*/ \
static struct array_##T array_##T##_Create() { \
	struct array_##T array = {.elems=NULL, .size=0, .space=0}; \
	return array; \
} \
\
/*Free an array*/ \
static void array_##T##_Free(struct array_##T* array) { \
	free(array->elems); \
	array->elems = NULL; \
	array->size = 0; \
	array->space = 0; \
} \
\
/*Reserve space for an array*/\
static void array_##T##_Reserve(struct array_##T* array, const size_t space) { \
	array->space = space; \
	array->elems = realloc(array->elems, sizeof(T)*(array->space)); \
	if (array->elems == NULL) { \
		perror("Realloc arrayUtils"); exit(errno); \
	} \
} \
\
/*Fit space to size for an array*/\
static void array_##T##_FitToSize(struct array_##T* array) { \
	array->space = array->size; \
	array->elems = realloc(array->elems, sizeof(T)*(array->space)); \
	if (array->elems == NULL) { \
		perror("Realloc arrayUtils"); exit(errno); \
	}  \
} \
\
/*Add an element to an array*/\
static void array_##T##_AddElement(struct array_##T* array, const T element) { \
	++(array->size); \
	if (array->size > array->space) { \
		++(array->space); \
		array->elems = realloc(array->elems, sizeof(T)*(array->space)); \
		if (array->elems == NULL) { \
			perror("Realloc arrayUtils"); exit(errno); \
		}  \
	} \
	\
	array->elems[array->size - 1] = element; \
} \
\
/*Remove an element from an array*/\
static bool array_##T##_RemoveElement(struct array_##T* array, const T element, bool (*areEqual)(const T, const T)) { \
	for (size_t i=0; i<array->size; ++i) { \
		if (areEqual(array->elems[i], element)) { \
			for (;i<array->size-1; ++i) { \
				array->elems[i] = array->elems[i+1]; \
			} \
			--(array->size); \
			return true; \
		} \
	} \
	return false; \
} \
\
/*Check if an array contains an element*/\
static bool array_##T##_Contains(const struct array_##T* const array, const T element, bool (*areEqual)(const T, const T)) { \
	for (size_t i = 0; i < array->size; i++) { \
		if (areEqual(array->elems[i], element)) { \
			return true; \
		} \
	} \
	return false; \
}\
\
/*Apply a function to each element in the array*/\
static void array_##T##_Foreach(const struct array_##T* const array, void (*func)(const T)) { \
	for(size_t i = 0; i<array->size; ++i) { \
		func(array->elems[i]);\
	}\
}\
\
/*Return last element*/\
static T* array_##T##_First(const struct array_##T* const array) {\
	return &array->elems[0];\
}\
\
/*Return last element*/\
static T* array_##T##_Last(const struct array_##T* const array) {\
	return &array->elems[array->size-1];\
}\



#endif //ARRAY_UTILS_INCLUDED
