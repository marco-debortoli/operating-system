#include <kernel/ordered_map.h>
#include <kernel/heap.h>
#include <kernel/panic.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>

uint8_t standard_lessthan_predicate(type_t a, type_t b)
{
	// Return if a is less than b
	return ( a < b ) ? 1 : 0;
}

ordered_map_t create_ordered_map(uint32_t max_size, lessthan_predicate_t less_than)
{
	// Create an ordered map, allocate space for the array and reset all values to 0
	ordered_map_t orderedMap;
	orderedMap.array = (void*)kmalloc(max_size * sizeof(type_t));
	memset(orderedMap.array, 0, max_size * sizeof(type_t));

	// Base values
	orderedMap.size = 0;
	orderedMap.max_size = max_size;
	orderedMap.less_than = less_than;
	
	return orderedMap;
}

ordered_map_t place_ordered_map(void* addr, uint32_t max_size, lessthan_predicate_t less_than)
{
	// Create an ordered map starting at desired address
	ordered_map_t orderedMap;
	orderedMap.array = (type_t*)addr;
	memset(orderedMap.array, 0, max_size * sizeof(type_t));
	
	// Base values
	orderedMap.size = 0;
	orderedMap.max_size = max_size;
	orderedMap.less_than = less_than;

	return orderedMap;
}

void destroy_ordered_map(ordered_map_t *map)
{
	// Free all the physical space taken up by the map
	kfree(map->array);
}

void insert_ordered_map(type_t item, ordered_map_t *map)
{
	// Iterate through trying to find place to put the item
	ASSERT(map->less_than);
	uint32_t iterator = 0;
	while (iterator < map->size && map->less_than(map->array[iterator], item))
		iterator++;

	// Append to the end of the map
	if ( iterator == map->size )
	{
		map->array[map->size++] = item;
	}
	// Otherwise place item in and move all other items down the map
	else
	{
		type_t tmp = map->array[iterator];
		map->array[iterator] = item;

		while ( iterator < map->size )
		{
			iterator++;
			type_t tmp2 = map->array[iterator];
			map->array[iterator] = tmp;
			tmp = tmp2;
		}
		map->size++;
	}
}

type_t lookup_ordered_map(uint32_t i, ordered_map_t *map)
{
	// Get the requested value at index i
	ASSERT( i < map->size );
	return map->array[i];
}

void remove_ordered_map(uint32_t i, ordered_map_t *map)
{
	// Remove the value at index i;
	while ( i < map->size )
	{
		map->array[i] = map->array[i+1];
		i++;
	}
	map->size--;
}






