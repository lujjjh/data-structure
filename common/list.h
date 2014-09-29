#ifndef _COMMON_LIST_H_
#define _COMMON_LIST_H_

#include <stdlib.h>
#include <memory.h>

/* a variable-length list */
#define LIST_INITIAL_SIZE 10

struct list {
    void *buf;
    int elem_size;
    int elem_count;
    int buf_count;
};

void list_init(struct list *l, int elem_size)
{
    l->elem_size = elem_size;
    l->elem_count = 0;
    l->buf_count = LIST_INITIAL_SIZE;
    l->buf = (void *)malloc(l->buf_count * elem_size);
}

void list_free(struct list *l)
{
    free(l->buf);
}

size_t list_size(struct list *l)
{
    return l->elem_count;
}

void list_set_size(struct list *l, int size)
{
    void *new_buf;

    if (size == l->buf_count) {
        return;
    }
    new_buf = (void *)malloc(size * l->elem_size);
    memcpy(new_buf, l->buf, size < l-> buf_count ? size : l->buf_count * l->elem_size);
    free(l->buf);
    l->buf = new_buf;
    l->buf_count = size;
}

void list_check_size(struct list *l)
{
    if (l->elem_count == l->buf_count)
    {
        list_set_size(l, l->buf_count * 2);
    }
}

#define list_to_array(l, type) ((type*)(l)->buf)

#define list_push(l, type, value) \
    (list_check_size((l)), list_to_array((l), type)[list_size((l))] = value, (l)->elem_count++)

#endif
