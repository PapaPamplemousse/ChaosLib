#include "chaos_alloc.h"
#include "chaos_test.h"
#include <stdint.h>

int main(void)
{
    chaos_status_t status;
    uint8_t heap[256];
    void *ptr1 = NULL, *ptr2 = NULL;

    chaos_alloc_config_t cfg = { .mem_start = heap, .mem_size = sizeof(heap) };
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "alloc_init for free test");

    chaos_alloc(32, &ptr1);
    chaos_alloc(16, &ptr2);

    /* Free first pointer */
    status = chaos_free(ptr1);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "free ptr1");

    /* Double free should fail */
    status = chaos_free(ptr1);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "double free detected");

    /* Free second pointer */
    status = chaos_free(ptr2);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "free ptr2");

    TEST_PASS("free tests passed");
}
