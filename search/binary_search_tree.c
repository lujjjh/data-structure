#include <stdio.h>
#include "../common/binary_tree.h"

static struct binary_tree tree;

int main(void)
{
    int count, num;

    binary_tree_init(&tree, sizeof(int));

    printf("Number of integers:\n");
    scanf("%d", &count);

    while (count--) {
        scanf("%d", &num);
        
    }

    binary_tree_free(&tree);

    return 1;
}
