#include <queue.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    srand(time(NULL));
    Queue *my_queue = new_Queue();

    printf("Randomly initialising queue with 10 int elements...\n");
    for (int i = 0; i < 10; i++)
    {
        int rand_num = rand() % 10;
        queue_enqueue(my_queue, &rand_num, sizeof(rand_num));
    }

    queue_print(my_queue, print_queue);
    printf("\n");

    int *deque_val = (int *)queue_deque(my_queue);
    printf("Dequeing: %d\n", *deque_val);
    free(deque_val);
    queue_print(my_queue, print_queue);

    return 0;
}