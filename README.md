# minimalist-map

A simple, minimalist map implementation in C.

# How to use

A simple example:
```
int compare(const void *a, const void b*) {
  const char *str_a = a, *str_b = b;
  return strcmp(a, b);
}

struct minimalist_map* map = minimalist_map_new(compare);
minimalist_map_set(map, "key", "value"); 
void *ret = minimalist_map_get(map, "key");
```
