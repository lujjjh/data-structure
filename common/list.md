初始化
======

    list_init(struct list *l, size_t elem_size)

参数         | 说明
------------|----------------------
`l`         | 列表指针（预先分配内存）
`elem_size` | 列表每个元素占的内存大小

```c
struct list l;

list_init(&l, sizeof(int))
```

释放
====

    list_free(struct list *l)

每个使用 `list_init()` 初始化的列表，必须使用 `list_free()` 释放。

参数         | 说明
------------|--------
`l`         | 列表指针

```c
list_free(&l);
```

重置缓冲区长度
============

    list_set_size(struct list *l, size_t size)

使得缓冲区预留能容纳 `size` 个元素（即 `size * elem_size`）的空间，列表中的原始数据将被保留。若 `size` 小于当前缓冲区长度，则舍弃从 `size` 开始的所有元素。

参数    | 说明
-------|-----------
`l`    | 列表指针
`size` | 新缓冲区长度

```c
list_set_size(&l, 100);
```

获取列表长度
==========

    list_size(struct list *l)

获取**当前已存放**的元素个数，仅对 `push()` 添加的元素有效。

参数         | 说明
------------|--------
`l`         | 列表指针

```c
int size = list_size(&l);
```
