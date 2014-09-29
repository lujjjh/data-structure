#include <assert.h>
#include <stdio.h>
#include "../common/list.h"

static struct list l;

int main(void)
{
    int i;

    list_init(&l, sizeof(int));

    printf("buf: %p\n", l.buf);

    for (i = 0; i < 100; i++) {
        list_push(&l, int, i);
    }
    // buf should be changed
    printf("buf: %p\n", l.buf);

    for (i = 0; i < 100; i++) {
        assert(list_to_array(&l, int)[i] == i);
        printf("%d\n", list_to_array(&l, int)[i]);
    }

    list_set_size(&l, 10);
    // buf should be changed
    printf("buf: %p\n", l.buf);
    // should be undefined
    printf("%d\n", list_to_array(&l, int)[10]);

    list_free(&l);
}
