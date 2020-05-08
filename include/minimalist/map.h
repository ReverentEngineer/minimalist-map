#ifndef __MINIMALIST_MAP_H__
#define __MINIMALIST_MAP_H__
/**
 * @file map.h
 */

#define MINIMALIST_MAP_VERSION "1.0.0"

/**
 * @brief A map instance
 */
struct minimalist_map;

typedef int (*minimalist_map_compare_fn)(const void*, const void*);

/**
 * @brief Creates a new map
 *
 * @return An instance of a map
 */
struct minimalist_map* minimalist_map_new(minimalist_map_compare_fn compare);

/**
 * @brief Frees an instance of a map.
 *
 * @param map Map to free
 */
void minimalist_map_free(struct minimalist_map *map);

/**
 * @brief Sets an element in a map.
 *
 * Setting the value to NULL removes any previously set element.
 *
 * @param map The map on which to operate.
 * @param key The key to use for the element.
 * @param value The value of the element.
 */
void minimalist_map_set(struct minimalist_map* map,
                        const void* key,
                        void *value);

/**
 * @brief Gets element in a map
 * 
 * @param map The map to sarch
 * @param key The key of the element.
 *
 * @return The element, if found. Otherwise, NULL.
 */
void* minimalist_map_get(struct minimalist_map* map,
                         const void* key);

#endif
