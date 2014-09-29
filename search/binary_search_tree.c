#include <stdio.h>
#include "../common/binary_tree.h"

static struct binary_tree tree;

struct search_param {
    int search_for;
    struct binary_tree_node *last_node;
};

enum binary_tree_enum binary_tree_search_func(
    struct binary_tree *tree,
    struct binary_tree_node *node,
    void *param)
{
    struct search_param *search_param;
    int value;

    search_param = (struct search_param *)param;
    search_param->last_node = node;

    value = binary_tree_node_get_value(tree, node, int);

    if (search_param->search_for < value) {
        return BTE_LEFT;
    } else if (search_param->search_for > value) {
        return BTE_RIGHT;
    }
    return BTE_NONE;
}

enum binary_tree_enum binary_tree_print_func(
    struct binary_tree *tree,
    struct binary_tree_node *node,
    void *param)
{
    printf("%d\n", binary_tree_node_get_value(tree, node, int));
    return BTE_ALL;
}

int main(void)
{
    int count, num;
    struct search_param search_param;
    struct binary_tree_node *node;

    binary_tree_init(&tree, sizeof(int));

    printf("Number of integers:\n");
    scanf("%d", &count);

    while (count--) {
        scanf("%d", &num);
        search_param.search_for = num;
        search_param.last_node = NULL;
        binary_tree_deep_first_enum(&tree, NULL, binary_tree_search_func, (void *)&search_param);
        node = binary_tree_insert_node(&tree, search_param.last_node, 0);
        binary_tree_node_set_value(&tree, node, int, num);
    }

    binary_tree_deep_first_enum(&tree, NULL, binary_tree_print_func, NULL);

    binary_tree_free(&tree);

    return 1;
}
