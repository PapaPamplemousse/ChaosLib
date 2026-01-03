/**
 * @file chaos_string.h
 * @brief Safe string operations for CHAOSLIB.
 *
 * Provides safe and robust string manipulation functions
 * with embedded status reporting and MISRA compliance.
 */

#ifndef CHAOS_STRING_H
#define CHAOS_STRING_H

#include "chaos_types.h"
#include "chaos_status.h"


/* ============================================================= */
/* STRING FUNCTIONS                                               */
/* ============================================================= */

/**
 * @brief Compute the length of a null-terminated string.
 * @param[in] str Input string pointer
 * @param[out] len Output length (excluding null terminator)
 */
chaos_status_t chaos_strlen(
    const chaos_cstr_t str,
    chaos_size_t *len
);

/**
 * @brief Copy a null-terminated string to a destination buffer.
 * @param[out] dst Destination buffer
 * @param[in] src Source string
 * @param[in] dst_size Size of destination buffer in bytes
 */
chaos_status_t chaos_strcpy(
    chaos_cstr_t dst,
    const chaos_cstr_t src,
    chaos_size_t dst_size
);

/**
 * @brief Concatenate a string to a destination buffer.
 * @param[out] dst Destination buffer
 * @param[in] src Source string
 * @param[in] dst_size Total size of destination buffer
 */
chaos_status_t chaos_strcat(
    chaos_cstr_t dst,
    const chaos_cstr_t src,
    chaos_size_t dst_size
);

/**
 * @brief Compare two null-terminated strings.
 * @param[in] str1 First string
 * @param[in] str2 Second string
 * @param[out] equal Output boolean: CHAOS_TRUE if equal, CHAOS_FALSE otherwise
 */
chaos_status_t chaos_strcmp(
    const chaos_cstr_t str1,
    const chaos_cstr_t str2,
    chaos_bool_t *equal
);

/**
 * @brief Search for a substring in a string.
 * @param[in] str String to search in
 * @param[in] substr Substring to search for
 * @param[out] found Output boolean: CHAOS_TRUE if found
 */
chaos_status_t chaos_strstr(
    const chaos_cstr_t str,
    const chaos_cstr_t substr,
    chaos_bool_t *found
);

#endif /* CHAOS_STRING_H */
