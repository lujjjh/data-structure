#include <stdio.h>
#include <stdlib.h>

struct vertex {
    int value;
};

/* already in topological order */

static struct vertex V[] = {
    1, 2, 3, 4, 5, 6, 7, 8, 9
};

#define COUNT sizeof V / sizeof V[0]

static int G[][COUNT] = {
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

static int ve[COUNT], vl[COUNT];

int calc_ve(int index)
{
    int i, max, current;

    if (ve[index] != -1) {
        return ve[index];
    }

    for (i = 0, max = -1; i < COUNT; i++) {
        if (G[i][index] != -1) {
            current = calc_ve(i) + G[i][index];
            if (current > max) {
                max = current;
            }
        }
    }

    return ve[index] = max;
}

int calc_vl(int index)
{
    int i, min, current;

    if (vl[index] != -1) {
        return vl[index];
    }

    for (i = 0, min = -1; i < COUNT; i++) {
        if (G[index][i] != -1) {
            current = calc_vl(i) - G[index][i];
            if (min == -1 || current < min) {
                min = current;
            }
        }
    }

    return vl[index] = min;
}

int main(void)
{
    int i;

    for (i = 0; i < COUNT; i++) {
        ve[i] = -1;
        vl[i] = -1;
    }

    /* calculate ve */
    ve[0] = 0;
    for (i = 0; i < COUNT; i++) {
        printf("ve(%d) - V%d = %d\n", i, V[i].value, calc_ve(i));
    }
    printf("\n");

    /* calculate vl */
    vl[COUNT-1] = ve[COUNT-1];
    for (i = 0; i < COUNT; i++) {
        printf("vl(%d) - V%d = %d\n", i, V[i].value, calc_vl(i));
    }
    printf("\n");

    /* critical path */
    printf("Critical path:\n");
    for (i = 0; i < COUNT; i++) {
        if (ve[i] == vl[i]) {
            printf("V%d ", V[i].value);
        }
    }
    printf("\n");

    return 0;
}
