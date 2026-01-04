/**
 * @file chaos_memory.h
 * @brief Safe memory operations for CHAOSLIB.
 *
 * Provides memcpy, memmove, memset, memcmp replacements
 * with embedded safety, status return, and MISRA compliance.
 */

#ifndef CHAOS_MEMORY_H
#define CHAOS_MEMORY_H

#include "chaos_types.h"
#include "chaos_status.h"


/* ============================================================= */
/* MEMORY FUNCTIONS                                               */
/* ============================================================= */

/**
 * @brief Safe memory copy
 * @param[inout] dst Destination buffer
 * @param[in] src Source buffer
 * @param[in] size Number of bytes to copy
 * @return CHAOS_STATUS_OK on success or a CHAOS status code on error
 */
extern chaos_status_t chaos_memcpy(void *dst, const void *src, chaos_size_t size);

/**
 * @brief Safe memory move (handles overlapping buffers)
 * @param[inout] dst Destination buffer
 * @param[in] src Source buffer
 * @param[in] size Number of bytes to move
 * @return CHAOS_STATUS_OK on success or a CHAOS status code on error
 */
extern chaos_status_t chaos_memmove(void *dst, const void *src, chaos_size_t size);

/**
 * @brief Safe memory set
 * @param[inout] dst Destination buffer
 * @param[in] value Byte value to set
 * @param[in] size Number of bytes to set
 * @return CHAOS_STATUS_OK on success or a CHAOS status code on error
 */
extern chaos_status_t chaos_memset(void *dst, chaos_u8_t value, chaos_size_t size);

/**
 * @brief Memory comparison
 * @param[in] buf1 First buffer
 * @param[in] buf2 Second buffer
 * @param[in] size Number of bytes to compare
 * @param[out] equal Output parameter set to CHAOS_TRUE if equal, CHAOS_FALSE otherwise
 * @return CHAOS_STATUS_OK on success or a CHAOS status code on error
 */
extern chaos_status_t chaos_memcmp(
    const void *buf1,
    const void *buf2,
    chaos_size_t size,
    chaos_bool_t *equal
);

#endif /* CHAOS_MEMORY_H */
