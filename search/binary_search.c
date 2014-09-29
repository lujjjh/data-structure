#include <stdio.h>
#include "../common/list.h"

struct list l;

int binary_search(struct list *l, int value)
{
    int low, high, mid, current;
    int *arr = list_to_array(l, int);
    size_t size = list_size(l);

    for (low = 0, high = size - 1; low <= high; ) {
        mid = (low + high) / 2;
        if ((current = arr[mid]) == value) {
            return mid;
        } else if (value < current) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return -1;
}

int main(void)
{
    int i;

    list_init(&l, sizeof(int));

    for (i = 1; i <= 100; i++) {
        list_push(&l, int, i);
    }

    printf("binary_search(10) = l[%d]\n", binary_search(&l, 10));
    printf("binary_search(101) = l[%d]\n", binary_search(&l, 101));

    list_free(&l);
}
