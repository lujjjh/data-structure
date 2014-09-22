#include <stdio.h>
#include <stdlib.h>
#include "../common/queue.h"

struct vertex {
    char value;
    int visited;
};

static struct vertex V[] = {
    'A', 0,
    'B', 0,
    'C', 0,
    'D', 0,
    'E', 0,
};

static int G[5][5] = {
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 1,
    1, 1, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 1, 0, 0, 0,
};

int _dfs(int start_index, int dest_index)
{
    int i;

    V[start_index].visited = 1;

    if (start_index == dest_index) {
        printf("%c", V[start_index].value);
        return 1;
    }

    for (i = 0; i < sizeof V / sizeof V[0]; i++) {
        if (G[start_index][i] && !V[i].visited) {
            if (_dfs(i, dest_index) == 1) {
                printf(" <- %c", V[start_index].value);
                return 1;
            }
        }
    }

    return 0;
}

int dfs(int start_index, int dest_index)
{
    int i;

    for (i = 0; i < sizeof V / sizeof V[0]; i++) {
        V[i].visited = 0;
    }

    return _dfs(start_index, dest_index);
}

int main(void)
{
    int i;

    // search for a path from A -> E
    printf("A -> E: ");
    if (dfs(0, 4) == 0) {
        printf("not connected!\n");
    } else {
        printf("\n");
    }

    // search for a path from A -> D
    printf("A -> D: ");
    if (dfs(0, 3) == 0) {
        printf("not connected!\n");
    } else {
        printf("\n");
    }

    return 0;
}
