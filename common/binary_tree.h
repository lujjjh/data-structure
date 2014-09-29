#ifndef _COMMON_BINARY_TREE_H_
#define _COMMON_BINARY_TREE_H_

#include <assert.h>
#include <stdlib.h>
#include <memory.h>

struct binary_tree_node {
    struct binary_tree_node *left;
    struct binary_tree_node *right;
    void *data;
};

struct binary_tree {
    struct binary_tree_node *root;
    size_t elem_size;
};

void binary_tree_init(struct binary_tree *tree, size_t elem_size)
{
    tree->root = NULL;
    tree->elem_size = elem_size;
}

void binary_tree_free_node(struct binary_tree_node *node)
{
    if (node == NULL) {
        return;
    }
    binary_tree_free_node(node->left);
    binary_tree_free_node(node->right);
    free(node->data);
    free(node);
}

void binary_tree_free(struct binary_tree *tree)
{
    binary_tree_free_node(tree->root);
}

struct binary_tree_node *binary_tree_node_create(struct binary_tree *tree)
{
    struct binary_tree_node *node = malloc(sizeof(struct binary_tree_node));
    node->left = node->right = NULL;
    node->data = (void *)malloc(tree->elem_size);
    return node;
}

void binary_tree_node_destroy(struct binary_tree_node *node)
{
    free(node->data);
    free(node);
}

struct binary_tree_node *binary_tree_insert_node(
    struct binary_tree *tree,
    struct binary_tree_node *parent,
    int direction)
{
    struct binary_tree_node *node = binary_tree_node_create(tree);

    if (parent == NULL) {
        assert(tree->root == NULL);
        tree->root = node;
    } else if (direction == 0) {
        assert(parent->left == NULL);
        parent->left = node;
    } else {
        assert(parent->right == NULL);
        parent->right = node;
    }

    return node;
}

struct binary_tree_node *binary_tree_get_node(
    struct binary_tree *tree,
    struct binary_tree_node *parent,
    int direction)
{
    if (parent == NULL) {
        return tree->root;
    }

    return direction == 0 ? parent->left : parent->right;
}

struct binary_tree_node *binary_tree_pop_node(
    struct binary_tree *tree,
    struct binary_tree_node *parent,
    int direction)
{
    struct binary_tree_node *node = binary_tree_get_node(tree, parent, direction);
    if (parent == NULL) {
        tree->root = NULL;
    } else if (direction == 0) {
        parent->left = NULL;
    } else {
        parent->right = NULL;
    }
    return node;
}

#define binary_tree_node_set_value(tree, node, type, value) \
    (*(type *)node->data = value)

#define binary_tree_node_get_value(tree, node, type) \
    (*(type *)node->data)

enum binary_tree_enum {
    BTE_NONE = 0,
    BTE_LEFT = 2 << 0,
    BTE_RIGHT = 2 << 1,
    BTE_ALL = BTE_LEFT | BTE_RIGHT,
};

void _binary_tree_deep_first_enum(
    struct binary_tree *tree,
    struct binary_tree_node *from,
    enum binary_tree_enum(*func)(
        struct binary_tree *tree,
        struct binary_tree_node *node,
        void *param),
    void *param)
{
    enum binary_tree_enum result;

    if (from == NULL) {
        return;
    }

    result = func(tree, from, param);
    if ((result & BTE_LEFT) == BTE_LEFT) {
        _binary_tree_deep_first_enum(tree, from->left, func, param);
    }
    if ((result & BTE_RIGHT) == BTE_RIGHT) {
        _binary_tree_deep_first_enum(tree, from->right, func, param);
    }
}

void binary_tree_deep_first_enum(
    struct binary_tree *tree,
    struct binary_tree_node *from,
    enum binary_tree_enum(*func)(
        struct binary_tree *tree,
        struct binary_tree_node *node,
        void *param),
    void *param)
{
    if (from == NULL) {
        from = binary_tree_get_node(tree, NULL, 0);
    }
    _binary_tree_deep_first_enum(tree, from, func, param);
}

#endif
