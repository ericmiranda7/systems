#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <node.h>
#include <queue.h>

void print_queue(void *val)
{
    printf("%d ", *((int *)val));
}

void queue_enqueue(Queue *queue, void *val, size_t val_len)
{
    Node *node = new_Node(val, val_len);

    if (queue->head == NULL)
    {
        queue->head = node;
        queue->tail = queue->head;
    }
    else
    {
        queue->tail->next = node;
        queue->tail = node;
    }
    queue->length++;
}

void *queue_deque(Queue *queue)
{
    if (queue->head == NULL)
    {
        printf("End of the line\n");
        return NULL;
    }

    Node *tmp_head = queue->head;
    void *rc = tmp_head->val;
    queue->head = tmp_head->next;
    free(tmp_head);
    return rc;
}

void queue_print(Queue *queue, void (*printer)(void *val))
{
    Node *tmp_head = queue->head;

    printf("Queue: ");
    while (tmp_head != NULL)
    {
        (*printer)(tmp_head->val);
        tmp_head = tmp_head->next;
        if (tmp_head != NULL)
            printf(" -> ");
    }
}

Queue *new_Queue()
{
    Queue *qPtr = queueConstructor();
    queueInit(qPtr);
    return qPtr;
}

Queue *queueConstructor()
{
    return malloc(sizeof(Queue));
}

void queueInit(Queue *queue)
{
    queue->head = NULL;
    queue->tail = NULL;
    queue->length = 0;
}
