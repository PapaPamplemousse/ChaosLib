#include "chaos_alloc.h"
#include "chaos_test.h"
#include <stdint.h>

typedef struct chaos_alloc_block
{
    chaos_size_t size;/**< Size of the block's payload */
    chaos_bool_t free;/**< Is the block free? */
    struct chaos_alloc_block *next;/**< Pointer to the next block */
} chaos_alloc_block_t;

int main(void)
{
    chaos_status_t status;
    void *ptr = NULL;
    void *ptr2 = NULL;
    chaos_size_t free_bytes;
    uint8_t heap[128];

    /* -------------------------------------------------------------
        Allocation before initialization must fail
    ------------------------------------------------------------- */
    status = chaos_alloc(16, &ptr);
    TEST_ASSERT(status != CHAOS_STATUS_OK && ptr == NULL, "alloc before init fails");

    /* -------------------------------------------------------------
        Allocator initialization
    ------------------------------------------------------------- */
    chaos_alloc_config_t cfg = { .mem_start = heap, .mem_size = sizeof(heap) };
    status = chaos_alloc_init(&cfg);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "alloc_init");

    /* -------------------------------------------------------------
        Allocation with size 0 must fail
    ------------------------------------------------------------- */
    status = chaos_alloc(0, &ptr);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "alloc size 0 fails");

    /* -------------------------------------------------------------
        Oversized allocation must fail
    ------------------------------------------------------------- */
    status = chaos_alloc(sizeof(heap), &ptr);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "alloc oversize fails");

    /* -------------------------------------------------------------
        Simple allocation
    ------------------------------------------------------------- */
    status = chaos_alloc(16, &ptr);
    TEST_ASSERT(status == CHAOS_STATUS_OK && ptr != NULL, "alloc 16 bytes");

    /* -------------------------------------------------------------
        Allocation requiring a block split
    ------------------------------------------------------------- */
    status = chaos_alloc(16, &ptr2);
    TEST_ASSERT(status == CHAOS_STATUS_OK && ptr2 != NULL, "alloc second 16 bytes (split)");

    /* -------------------------------------------------------------
        Alignment verification
    ------------------------------------------------------------- */
    TEST_ASSERT(((uintptr_t)ptr % CHAOS_ALLOC_ALIGNMENT) == 0, "ptr alignment check");
    TEST_ASSERT(((uintptr_t)ptr2 % CHAOS_ALLOC_ALIGNMENT) == 0, "ptr2 alignment check");

    /* -------------------------------------------------------------
        get_free should decrease after allocations
    ------------------------------------------------------------- */
    status = chaos_alloc_get_free(&free_bytes);
    TEST_ASSERT(status == CHAOS_STATUS_OK && free_bytes < sizeof(heap), "get_free after alloc");

    /* -------------------------------------------------------------
        Simple free
    ------------------------------------------------------------- */
    status = chaos_free(ptr);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "free ptr");

    /* -------------------------------------------------------------
        Double free must fail
    ------------------------------------------------------------- */
    status = chaos_free(ptr);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "double free detected");

    /* -------------------------------------------------------------
        Freeing second block
    ------------------------------------------------------------- */
    status = chaos_free(ptr2);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "free ptr2");

    /* -------------------------------------------------------------
        Coalescing verification after freeing
        (Should be able to reallocate full space)
    ------------------------------------------------------------- */
    status = chaos_alloc(sizeof(heap) - sizeof(chaos_alloc_block_t), &ptr);
    TEST_ASSERT(status == CHAOS_STATUS_OK && ptr != NULL, "alloc full heap after free (coalescing)");

    /* -------------------------------------------------------------
        Final cleanup
    ------------------------------------------------------------- */
    status = chaos_free(ptr);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "free full heap");

    TEST_PASS("all alloc tests passed");
}
