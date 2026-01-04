/**
 * @file chaos_alloc.h
 * @brief Chaos memory allocator interface.
 *
 * This file defines the interface for a custom memory allocator in the Chaos library.
 * It provides functions to initialize the allocator, allocate and free memory,
 * and query the amount of free memory available.
 */
#ifndef CHAOS_ALLOC_H
#define CHAOS_ALLOC_H

#include "chaos_types.h"
#include "chaos_status.h"

/* ============================================================= */
/* ALLOCATOR CONFIGURATION STRUCTURE                             */
/* ============================================================= */
/**
 * @brief Configuration structure for initializing the memory allocator.
 */
typedef struct
{
    void        *mem_start;/**< Start of memory region */
    chaos_size_t mem_size; /**< Size of memory region */
} chaos_alloc_config_t;

#if (CHAOS_ENABLE_ALLOC == 1)
/**
 * @brief Initialize allocator with a memory region.
 * @param[in] config Pointer to allocator configuration
 */
chaos_status_t chaos_alloc_init( const chaos_alloc_config_t *config );

/**
 * @brief Allocate memory.
 * @param[in] size Number of bytes to allocate
 * @param[out] ptr Pointer to allocated memory
 */
chaos_status_t chaos_alloc(chaos_size_t size, void **ptr);

/**
 * @brief Free memory.
 * @param[in] ptr Pointer to memory to free
 */
chaos_status_t chaos_free(void *ptr);

/**
 * @brief Get free memory in bytes.
 * @param[out] free_bytes Pointer to store free memory size
 */
chaos_status_t chaos_alloc_get_free(
    chaos_size_t *free_bytes
);


#else /* CHAOS_ENABLE_ALLOC == 0 -> STUBS */

static inline chaos_status_t chaos_alloc_init(const chaos_alloc_config_t *c) { (void)c; return CHAOS_STATUS_OK; }
static inline chaos_status_t chaos_free(void *p) { (void)p; return CHAOS_STATUS_OK; }

static inline chaos_status_t chaos_alloc(chaos_size_t s, void **p) {
    (void)s;
    if (p) *p = NULL;
    return CHAOS_STATUS_MAKE(CHAOS_SEVERITY_FATAL, CHAOS_MODULE_ALLOC, CHAOS_ERRCLASS_NOT_SUPPORTED, CHAOS_ALLOC_DISABLED);
}

static inline chaos_status_t chaos_alloc_get_free(chaos_size_t *f) {
    if (f) *f = 0;
    return CHAOS_STATUS_MAKE(CHAOS_SEVERITY_FATAL, CHAOS_MODULE_ALLOC, CHAOS_ERRCLASS_NOT_SUPPORTED, CHAOS_ALLOC_DISABLED);
}

#endif /* CHAOS_ENABLE_ALLOC */
#endif /* CHAOS_ALLOC_H */
