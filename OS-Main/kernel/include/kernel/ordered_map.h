/*

	Ordered map header
	Base Class: arch/i386/ordered-map/ordered_map.c

*/

#ifndef _KERNEL_ORDERED_MAP_H
#define _KERNEL_ORDERED_MAP_H

#include <stdint.h>

typedef void* type_t;

// A predicate should return nonzero if the first argument is less than the second
typedef uint8_t (*lessthan_predicate_t)(type_t, type_t);

typedef struct
{
	type_t *array;
	uint32_t size;
	uint32_t max_size;
	lessthan_predicate_t less_than;
} ordered_map_t;


// A standard less than predicate
uint8_t standard_lessthan_predicate(type_t a, type_t b);

// Create an ordered map
ordered_map_t create_ordered_map(uint32_t max_size, lessthan_predicate_t less_than);
ordered_map_t place_ordered_map(void *addr, uint32_t max_size, lessthan_predicate_t less_than);

// Destroy an ordered array
void destroy_ordered_map(ordered_map_t *array);

// Add an item into the array
void insert_ordered_map(type_t item, ordered_map_t *map);

// Lookup the item at index i
type_t lookup_ordered_map(uint32_t i, ordered_map_t *map);

// Deletes the item at location i from the array
void remove_ordered_map(uint32_t i, ordered_map_t *map);

#endif
