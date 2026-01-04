#include "chaos_alloc.h"
#include "chaos_test.h"
#include <stdint.h>

int main(void)
{
    chaos_status_t status;
    uint8_t heap[512];
    void *ptr1 = NULL;
    void *ptr2 = NULL;

    chaos_alloc_config_t cfg = { .mem_start = heap, .mem_size = sizeof(heap) };
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "alloc_init for alloc test");

    /* Simple allocation */
    status = chaos_alloc(16, &ptr1);
    TEST_ASSERT(status == CHAOS_STATUS_OK && ptr1 != NULL, "alloc simple 16 bytes");

    /* Allocate another block */
    status = chaos_alloc(32, &ptr2);
    TEST_ASSERT(status == CHAOS_STATUS_OK && ptr2 != NULL, "alloc another 32 bytes");

    /* Allocate too big block */
    void *ptr3 = NULL;
    status = chaos_alloc(1024, &ptr3);
    TEST_ASSERT(status != CHAOS_STATUS_OK && ptr3 == NULL, "alloc oversize fails");

    TEST_PASS("alloc tests passed");
}
