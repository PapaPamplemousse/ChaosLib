#include "chaos_alloc.h"
#include "chaos_test.h"
#include <stdint.h>

int main(void)
{
    chaos_status_t status;
    uint8_t heap[128];
    void *ptr1 = NULL;
    chaos_size_t free_bytes = 0;

    chaos_alloc_config_t cfg = { .mem_start = heap, .mem_size = sizeof(heap) };
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "alloc_init for get_free");

    status = chaos_alloc_get_free(&free_bytes);
    TEST_ASSERT(status == CHAOS_STATUS_OK && free_bytes > 0, "get_free initial");

    chaos_alloc(32, &ptr1);

    chaos_alloc_get_free(&free_bytes);
    TEST_ASSERT(free_bytes < sizeof(heap), "get_free after alloc");

    chaos_free(ptr1);

    chaos_alloc_get_free(&free_bytes);
    TEST_ASSERT(free_bytes > 0, "get_free after free");

    TEST_PASS("alloc_get_free tests passed");
}
