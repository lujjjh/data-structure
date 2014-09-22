#ifndef _COMMON_QUEUE_H_
#define _COMMON_QUEUE_H_

#define MAX_QUEUE_SIZE 1000

struct queue {
    int front;
    int rear;
    void *data[MAX_QUEUE_SIZE];
};

void queue_init(struct queue *q)
{
    q->front = q->rear = 0;
}

int queue_empty(struct queue *q)
{
    return q->front == q->rear;
}

int queue_full(struct queue *q)
{
    return q->rear == (q->front + 1) % MAX_QUEUE_SIZE;
}

int queue_enqueue(struct queue *q, void *value)
{
    if (queue_full(q)) {
        return 0;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->data[q->rear] = value;
    return 1;
}

int queue_dequeue(struct queue *q, void **dest)
{
    if (queue_empty(q)) {
        return 0;
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    *dest = q->data[q->front];
    return 1;
}

void queue_free(struct queue *q, void(*free_callback)(void *value))
{
    if (free_callback) {
        while (!queue_empty(q)) {
            void *value;
            queue_dequeue(q, &value);
            free_callback(value);
        }
    }
}

#endif
