#include "chaos_alloc.h"
#include "chaos_test.h"
#include <stdio.h>
#include <stdint.h>

typedef struct node {
    int value;
    struct node *next;
} node_t;

int main(void)
{
    chaos_status_t status;
    uint8_t heap[1024];
    chaos_alloc_config_t cfg = { .mem_start = heap, .mem_size = sizeof(heap) };
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "alloc_init for integration");

    node_t *head = NULL;
    node_t *n = NULL;

    /* Build a linked list of 10 elements */
    for (int i = 0; i < 10; i++)
    {
        status = chaos_alloc(sizeof(node_t), (void **)&n);
        TEST_ASSERT(status == CHAOS_STATUS_OK && n != NULL, "alloc node");

        n->value = i;
        n->next = head;
        head = n;
    }

    /* Verify list content */
    node_t *iter = head;
    int expected = 9;
    while (iter != NULL)
    {
        TEST_ASSERT(iter->value == expected, "list node value check");
        iter = iter->next;
        expected--;
    }

    /* Free list */
    iter = head;
    while (iter != NULL)
    {
        node_t *tmp = iter->next;
        status = chaos_free(iter);
        TEST_ASSERT(status == CHAOS_STATUS_OK, "free node");
        iter = tmp;
    }

    TEST_PASS("integration list test passed");
}
