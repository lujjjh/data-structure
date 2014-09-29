#include <assert.h>
#include <stdio.h>
#include "../common/binary_tree.h"

int main(void)
{
    struct binary_tree tree;
    struct binary_tree_node *root, *node;

    binary_tree_init(&tree, sizeof(int));

    root = binary_tree_insert_node(&tree, NULL, 0);
    binary_tree_node_set_value(&tree, root, int, 20);
    assert(binary_tree_node_get_value(&tree, root, int) == 20);

    /* insert a node to the root, on the left */
    node = binary_tree_insert_node(&tree, root, 0);
    binary_tree_node_set_value(&tree, node, int, 11);
    assert(binary_tree_node_get_value(&tree, node, int) == 11);

    /* get node with binary_tree_get_node */
    assert(binary_tree_node_get_value(&tree,
        binary_tree_get_node(&tree, root, 0), int) == 11);

    /* set new value to node */
    binary_tree_node_set_value(&tree,
        binary_tree_get_node(&tree, root, 0), int, 99);
    assert(binary_tree_node_get_value(&tree, node, int) == 99);

    binary_tree_free(&tree);

    return 0;
}
