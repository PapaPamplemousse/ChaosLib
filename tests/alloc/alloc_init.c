#include "chaos_alloc.h"
#include "chaos_test.h"
#include <stdint.h>

int main(void)
{
    chaos_status_t status;
    uint8_t heap[1024];

    /* Test basic initialization */
    chaos_alloc_config_t cfg = {
        .mem_start = heap,
        .mem_size  = sizeof(heap)
    };
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "alloc_init basic");

    /* Test double init */
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "alloc_init double init");

    TEST_PASS("alloc_init tests passed");
}
