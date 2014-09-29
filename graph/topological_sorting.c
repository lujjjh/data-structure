#include <stdio.h>
#include <stdlib.h>

struct vertex {
    int value;
    int removed;
};

static struct vertex V[] = {
    1, 0, 2, 0,
    3, 0, 4, 0,
    5, 0, 6, 0,
    7, 0, 8, 0,
    9, 0,
};

static int G[][9] = {
    -1,  6,  4,  5, -1, -1, -1, -1, -1,
    -1, -1, -1, -1,  1, -1, -1, -1, -1,
    -1, -1, -1, -1,  1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1,  2, -1, -1, -1,
    -1, -1, -1, -1, -1, -1,  9,  7, -1,
    -1, -1, -1, -1, -1, -1, -1,  4, -1,
    -1, -1, -1, -1, -1, -1, -1, -1,  2,
    -1, -1, -1, -1, -1, -1, -1, -1,  4,
    -1, -1, -1, -1, -1, -1, -1, -1, -1,
};

int find_first_node_with_no_incoming_edges()
{
    int i, j, count, found;

    count = sizeof V / sizeof V[0];

    for (i = 0; i < count; i++) {
        if (V[i].removed) {
            continue;
        }

        found = 1;
        for (j = 0; j < count; j++) {
            if (!V[j].removed && G[j][i] != -1) {
                found = 0;
                break;
            }
        }
        if (found) {
            return i;
        }
    }

    return -1;
}

int main(void)
{
    int index;

    for (; ; ) {
        index = find_first_node_with_no_incoming_edges();
        if (index == -1) {
            break;
        }
        printf("V%d ", V[index].value);
        V[index].removed = 1;
    }

    printf("\n");

    return 0;
}
