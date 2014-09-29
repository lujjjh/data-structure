通用库
=====

可变长列表 (list.h)
------------------

### 初始化 ###

    list_init(struct list *l, size_t elem_size)

参数         | 说明
------------|----------------------
`l`         | 列表（预先分配内存）
`elem_size` | 列表每个元素占的内存大小

```c
struct list l;

list_init(&l, sizeof(int))
```
