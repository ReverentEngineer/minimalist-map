#include "minimalist/map.h"

#include <stdlib.h>
#include <assert.h>

enum color_t { RED, BLACK };

struct map_node {
  struct map_node *parent;
  struct map_node *left;
  struct map_node *right;
  enum color_t color;
  const void *key;
  void *value;
};

struct minimalist_map {
  struct map_node    *root;
  minimalist_map_compare_fn  compare;
};

struct minimalist_map* 
minimalist_map_new(minimalist_map_compare_fn compare) {
  struct minimalist_map* map = NULL;

  if (compare == NULL) {
    goto err;
  } 

  map = malloc(sizeof(struct minimalist_map));

  if (map == NULL) {
    goto err;
  }

  map->compare = compare;
  map->root = NULL;
err:
  return map;
}

static void
free_node(struct map_node *node) {
  if (node->right != NULL) {
    free_node(node->right);
  } else if (node->left != NULL)  {
    free_node(node->left);
  }
  free(node); 
}

void
minimalist_map_free(struct minimalist_map *map) {
  free_node(map->root);
  free(map);
}

static struct map_node*
get_sibling(struct map_node* node) {
  if (node->parent == NULL) {
    return NULL;
  }

  if (node == node->parent->left) {
    return node->parent->right;
  } else {
    return node->parent->left;
  }
}

static struct map_node*
get_parent(struct map_node* node) {
  return node == NULL ? NULL : node->parent;
}

static struct map_node*
get_grand_parent(struct map_node* node) {
  return get_parent(get_parent(node));
}

static struct map_node*
get_uncle(struct map_node* node) {
  struct map_node* parent = get_parent(node);
  return get_sibling(parent);
}

static void
rotate_left(struct map_node* node) {
  struct map_node* new_node = node->right;
  struct map_node* parent = get_parent(node);
  assert(new_node != NULL);
  
  node->right = new_node->left;
  new_node->left = node;
  if (node->right != NULL) {
    node->right->parent = node;
  }

  if (parent != NULL) {
    if (node == parent->left) {
      parent->left = new_node;
    } else if (node == parent->right) {
      parent->right = new_node;
    }
  }
}

static void
repair(struct map_node *node) {
  if (get_parent(node) == NULL) {
    node->color = BLACK;
  } else if (get_parent(node)->color == BLACK) {
    // Do nothing
  } else if (get_uncle(node) != NULL &&
              get_uncle(node)->color == RED) {
    get_parent(node)->color = BLACK;
    get_uncle(node)->color = BLACK;
    get_grand_parent(node)-> color = RED;
    repair(get_grand_parent(node));
  } else {
    // TODO: Balance map         
  }
}

static void add(struct map_node *root, 
    struct map_node *node,
    minimalist_map_compare_fn compare) {
  int comparison = compare(root->key, node->key);
  if (root != NULL) {
    if (comparison > 0) {
      if (root->right != NULL) {
        add(root->right, node, compare); 
      } else {
        node->parent = root;
        root->right = node;
      }
    } else if (comparison < 0) {
      if (root->left != NULL) {
        add(root->left, node, compare); 
      } else {
        node->parent = root;
        root->left = node;
      }
    } else {
      root->value = node->value;
      free(node);
    }
  }
}

void
minimalist_map_set(struct minimalist_map *map,
                   const void *key,
                   void *value) {
  struct map_node* new_node = malloc(sizeof(struct map_node));
  if (new_node != NULL) {
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = key;
    new_node->value = value;
    new_node->color = RED;
    if (map->root != NULL) {
      add(map->root, new_node, map->compare);
    } else {
      map->root = new_node;
    }
    repair(new_node);
  }
}

static void*
find(struct map_node *node, const void* key, minimalist_map_compare_fn compare) {
  int comparison = compare(node->key, key);
  if (comparison > 0) {
    return find(node->left, key, compare);
  } else if (comparison < 0) {
    return find(node->left, key, compare);
  } else {
    return node->value;
  }
}

void*
minimalist_map_get(struct minimalist_map *map,
                   const void *key) {
  return find(map->root, key, map->compare);
}
