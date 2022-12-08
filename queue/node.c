#include <stdio.h>
#include <node.h>
#include <string.h>
#include <stdlib.h>

// 1. frontend
Node *new_Node(void *val, size_t val_len)
{
    Node *nPtr = nodeConstructor();
    nodeInit(nPtr, val, val_len);
    return nPtr;
}

// 2. memory allocation
Node *nodeConstructor()
{
    return (Node *)malloc(sizeof(Node));
}

// 3. data initialisation
void nodeInit(Node *this, void *val, size_t val_len)
{
    this->next = NULL;
    this->val = malloc(val_len);
    memcpy(this->val, val, val_len);
}