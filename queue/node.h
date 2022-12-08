#include <aio.h>

typedef struct Node
{
    void *val;
    struct Node *next;
} Node;

Node *new_Node(void *val, size_t val_len);
Node *nodeConstructor();
void nodeInit(Node *, void *, size_t);