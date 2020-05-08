#include <minimalist/map.h>

#include <assert.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
  const char *str_a = a, *str_b = b;
  return strcmp(str_a, str_b);
}

int main() {
  struct minimalist_map* map = NULL;
  map = minimalist_map_new(NULL);
  assert(map == NULL); 
  map = minimalist_map_new(compare_strings);
  assert(map != NULL);
  char* value = "value";
  minimalist_map_set(map, "keya", NULL);
  minimalist_map_set(map, "keyb", value);
  minimalist_map_set(map, "keyc", NULL);
  minimalist_map_set(map, "keyd", NULL);
  char* ret = minimalist_map_get(map, "keyb");
  assert(value == ret);
  minimalist_map_free(map);
  return 0;
}
