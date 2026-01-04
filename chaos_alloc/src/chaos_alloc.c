#include "chaos_alloc.h"
#include "chaos_assert.h"
#include "chaos_critical.h"

#ifndef CHAOS_ALLOC_ALIGNMENT
#define CHAOS_ALLOC_ALIGNMENT 8U
#endif
CHAOS_STATIC_ASSERT((CHAOS_ALLOC_ALIGNMENT & (CHAOS_ALLOC_ALIGNMENT - 1U)) == 0U,alloc_alignment_must_be_power_of_two);

/* ============================================================= */
/* ALLOC BLOCK STRUCTURE                                         */
/* ============================================================= */
typedef struct chaos_alloc_block
{
    chaos_size_t size;/**< Size of the block's payload */
    chaos_bool_t free;/**< Is the block free? */
    struct chaos_alloc_block *next;/**< Pointer to the next block */
} chaos_alloc_block_t;

/* ============================================================= */
/* GLOBAL VARIABLES                                             */
/* ============================================================= */
static chaos_alloc_block_t *g_head = CHAOS_NULL;
static chaos_bool_t g_initialized = CHAOS_FALSE;
static chaos_u8_t * g_heap_start = CHAOS_NULL;
static chaos_u8_t * g_heap_end   = CHAOS_NULL;
static chaos_size_t g_max_size  = 0U;

/* ============================================================= */
/* FUNCTION PROTOTYPES                                          */
/* ============================================================= */
static chaos_size_t chaos_align(chaos_size_t size);


/* ============================================================= */
/* ALLOC INIT                                                    */
/* ============================================================= */
chaos_status_t chaos_alloc_init( const chaos_alloc_config_t *config )
{
    chaos_status_t status = CHAOS_STATUS_OK;

    /* Validate parameters */
    chaos_assert_not_null(config, &status, CHAOS_MODULE_ALLOC);
    chaos_assert_not_null(config->mem_start, &status, CHAOS_MODULE_ALLOC);
    chaos_assert_param(config->mem_size > sizeof(chaos_alloc_block_t), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_INVALID_ALLOC_SIZE);
    chaos_assert_param( (((chaos_uintptr_t)config->mem_start % CHAOS_ALLOC_ALIGNMENT) == 0U), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_ALLOC_ALIGNMENT_ERROR);

    if(status == CHAOS_STATUS_OK)
    {
        chaos_enter_critical();

        if (g_initialized == CHAOS_FALSE)
        {
            /* Initialize heap */
            g_heap_start = (chaos_u8_t * )config->mem_start;
            g_heap_end   = g_heap_start + config->mem_size;
            g_max_size   = config->mem_size;
            /* Create initial free block */
            g_head = (chaos_alloc_block_t *)g_heap_start;
            g_head->size = config->mem_size - (chaos_size_t)sizeof(chaos_alloc_block_t);
            g_head->free = CHAOS_TRUE;
            g_head->next = CHAOS_NULL;

            /* Mark allocator as initialized */
            g_initialized = CHAOS_TRUE;

        }
        else
        {
            status = CHAOS_STATUS_MAKE(CHAOS_SEVERITY_WARNING, CHAOS_MODULE_ALLOC, CHAOS_ERRCLASS_INTERNAL, CHAOS_ALREADY_INITIALIZED);
        }

        chaos_exit_critical();
    }
    return status;
}


/* ============================================================= */
/* ALLOC                                                         */
/* ============================================================= */
chaos_status_t chaos_alloc(chaos_size_t size, void **ptr)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_alloc_block_t *current = CHAOS_NULL;
    chaos_size_t aligned = 0U;
    chaos_bool_t found = CHAOS_FALSE;
    chaos_alloc_block_t *new_block = CHAOS_NULL;

    chaos_assert_not_null(ptr, &status, CHAOS_MODULE_ALLOC);
    chaos_assert_param((g_initialized == CHAOS_TRUE), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_NOT_INITIALIZED);
    chaos_assert_param((size != 0U), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_INVALID_ALLOC_SIZE);
    chaos_assert_param((size <= (g_max_size - sizeof(chaos_alloc_block_t))), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_NO_MEMORY);

    if(status == CHAOS_STATUS_OK)
    {
        *ptr = CHAOS_NULL;
        /* Align requested size */
        aligned = chaos_align(size);

        /* Enter critical section */
        chaos_enter_critical();

        current = g_head;

        /* Find a suitable free block */
        while ((current != CHAOS_NULL) && (found == CHAOS_FALSE))
        {
            /* Check if block is free and large enough */
            if ((current->free == CHAOS_TRUE) && (current->size >= aligned))
            {
                /* Found a suitable block */
                if (current->size > aligned + sizeof(chaos_alloc_block_t))
                {
                    /* Split block */
                    new_block = (chaos_alloc_block_t *)((chaos_u8_t *)current + sizeof(chaos_alloc_block_t) + aligned);

                    /* Ensure new block is within heap bounds */
                    if (((chaos_u8_t *)new_block + sizeof(chaos_alloc_block_t)) <= g_heap_end)
                    {
                        new_block->size = current->size - aligned - (chaos_size_t)sizeof(chaos_alloc_block_t);
                        new_block->free = CHAOS_TRUE;
                        new_block->next = current->next;
                        current->next = new_block;
                        current->size = aligned;
                    }
                }

                if(((chaos_u8_t *)current + sizeof(chaos_alloc_block_t)+aligned) <= g_heap_end)
                {
                    /* Mark block as used */
                    current->free = CHAOS_FALSE;
                    *ptr = (void *)((chaos_u8_t *)current + sizeof(chaos_alloc_block_t));
                    /* Set found flag */
                    found = CHAOS_TRUE;
                }
                else
                {
                    /* Move to next block */
                    current = current->next;
                }

            }
            else
            {
                /* Move to next block */
                current = current->next;
            }
        }

        /* Check if allocation was successful */
        if (*ptr == CHAOS_NULL)
        {
            status = CHAOS_STATUS_MAKE(CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_ERRCLASS_MEMORY, CHAOS_NO_MEMORY);
        }

        /* Exit critical section */
        chaos_exit_critical();
    }

    return status;
}

/* ============================================================= */
/* FREE                                                          */
/* ============================================================= */
chaos_status_t chaos_free(void *ptr)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_alloc_block_t *current = CHAOS_NULL;
    chaos_alloc_block_t *prev = CHAOS_NULL;
    chaos_bool_t released = CHAOS_FALSE;

    chaos_assert_not_null(ptr, &status, CHAOS_MODULE_ALLOC);
    chaos_assert_param((g_initialized == CHAOS_TRUE), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_NOT_INITIALIZED);
    chaos_assert_param( ((chaos_u8_t *)ptr > g_heap_start) && ((chaos_u8_t *)ptr < g_heap_end), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_INVALID_POINTER);

    if (status == CHAOS_STATUS_OK)
    {
        chaos_enter_critical();

        current = g_head;

        while ((current != CHAOS_NULL) && (released == CHAOS_FALSE))
        {
            if ((chaos_u8_t *)current + sizeof(chaos_alloc_block_t) == (chaos_u8_t *)ptr)
            {
                if (current->free == CHAOS_TRUE)
                {
                    status = CHAOS_STATUS_MAKE( CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_ERRCLASS_MEMORY, CHAOS_ALLOC_DOUBLE_FREE);
                    released = CHAOS_TRUE;
                }
                else
                {
                    current->free = CHAOS_TRUE;

                    /* Coalesce with next */
                    if ((current->next != CHAOS_NULL) && (current->next->free == CHAOS_TRUE))
                    {
                        current->size += (chaos_size_t)sizeof(chaos_alloc_block_t) + current->next->size;
                        current->next = current->next->next;
                    }

                    /* Coalesce with previous */
                    if ((prev != CHAOS_NULL) && (prev->free == CHAOS_TRUE))
                    {
                        prev->size += (chaos_size_t)sizeof(chaos_alloc_block_t) + current->size;
                        prev->next = current->next;
                    }

                    released = CHAOS_TRUE;
                }
            }

            prev = current;
            current = current->next;
        }

        chaos_exit_critical();
    }

    return status;
}

/* ============================================================= */
/* ALLOC GET FREE                                                */
/* ============================================================= */
chaos_status_t chaos_alloc_get_free(
    chaos_size_t *free_bytes
)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_alloc_block_t *current = CHAOS_NULL;
    chaos_size_t total = 0U;

    chaos_assert_not_null(free_bytes, &status, CHAOS_MODULE_ALLOC);
    chaos_assert_param((g_initialized == CHAOS_TRUE), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_ALLOC, CHAOS_NOT_INITIALIZED);

    if (status == CHAOS_STATUS_OK)
    {
        *free_bytes = 0U;

        chaos_enter_critical();

        current = g_head;
        while (current != CHAOS_NULL)
        {
            if (current->free == CHAOS_TRUE)
            {
                total += current->size;
            }
            current = current->next;
        }

        *free_bytes = total;

        chaos_exit_critical();
    }

    return status;
}

/* ============================================================= */
/* ALIGN HELPER FUNCTION                                        */
/* ============================================================= */
static chaos_size_t chaos_align(chaos_size_t size)
{
    return (size + (CHAOS_ALLOC_ALIGNMENT - 1U)) &
           ~(CHAOS_ALLOC_ALIGNMENT - 1U);
}
