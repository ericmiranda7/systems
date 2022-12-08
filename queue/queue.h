#include <aio.h>

typedef struct Queue
{
    struct Node *head;
    struct Node *tail;
    int length;
} Queue;

Queue *new_Queue();
Queue *queueConstructor();
void queueInit(Queue *queue);
void queue_enqueue(Queue *queue, void *val, size_t val_len);
void print_queue(void *val);
void queue_print(Queue *queue, void (*printer)(void *val));
// You must call free() on the void pointer to avoid memory leaks
void *queue_deque(Queue *queue);