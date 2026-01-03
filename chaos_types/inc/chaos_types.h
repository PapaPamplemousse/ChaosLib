/**
 * @file chaos_types.h
 * @brief Fully self-contained type definitions with guaranteed sizes.
 * * This header provides a set of primitive types and macros for use in 
 * freestanding or embedded environments where the standard library 
 * (libc) might be unavailable or restricted.
 * @note Compile-time validation of type widths is performed via static assertions.
 * @author PapaPamplemousse
 * @version 1.0.0
 */

#ifndef CHAOS_TYPES_H
#define CHAOS_TYPES_H

/* ============================================================= */
/* COMPILER DETECTION                    */
/* ============================================================= */

/**
 * @section Compiler Requirements
 * @brief Enforcement of C99 standard or higher.
 */

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 199901L)
#error "CHAOSLIB requires at least C99 compliance"
#endif

/* ============================================================= */
/* INTEGER TYPE DEFINITIONS                   */
/* ============================================================= */

/**
 * @name Fixed-width Integer Types
 * @brief Explicitly sized signed and unsigned integers.
 * @{
 */

/** @brief Signed 8-bit integer. */
typedef signed char        chaos_i8_t;
/** @brief Unsigned 8-bit integer. */
typedef unsigned char      chaos_u8_t;

/** @brief Signed 16-bit integer. */
typedef signed short       chaos_i16_t;
/** @brief Unsigned 16-bit integer. */
typedef unsigned short     chaos_u16_t;

/** @brief Signed 32-bit integer. */
typedef signed long        chaos_i32_t;
/** @brief Unsigned 32-bit integer. */
typedef unsigned long      chaos_u32_t;

#if defined(CHAOS_ENABLE_INT64) && (CHAOS_ENABLE_INT64 == 1)
/** @brief Signed 64-bit integer. (Optional: requires CHAOS_ENABLE_INT64) */
typedef signed long long   chaos_i64_t;
/** @brief Unsigned 64-bit integer. (Optional: requires CHAOS_ENABLE_INT64) */
typedef unsigned long long chaos_u64_t;
#endif

/** @} */

/* ============================================================= */
/* BOOLEAN TYPE                          */
/* ============================================================= */

/**
 * @name Boolean Logic
 * @brief Custom boolean implementation for environments without <stdbool.h>.
 * @{
 */

/** @brief Boolean type represented as an 8-bit unsigned integer. */
typedef chaos_u8_t chaos_bool_t;

/** @brief Boolean True value. */
#define CHAOS_TRUE  ((chaos_bool_t)1U)

/** @brief Boolean False value. */
#define CHAOS_FALSE ((chaos_bool_t)0U)

/** @} */

/* ============================================================= */
/* SIZE / POINTER TYPES                      */
/* ============================================================= */

/**
 * @name Memory and Pointer Types
 * @brief Types for memory sizing and pointer arithmetic.
 * @{
 */

/** @brief Type used for object sizes (equivalent to size_t). */
typedef chaos_u32_t chaos_size_t;

/** @brief Type used for pointer subtraction results (equivalent to ptrdiff_t). */
typedef chaos_i32_t chaos_ptrdiff_t;

/** @} */


/* ============================================================= */
/* FLOATING POINT TYPES                       */
/* ============================================================= */

/**
 * @name Floating Point Types
 * @brief Standards-based floating point definitions.
 * @{
 */
#if defined(CHAOS_ENABLE_FLOAT) && (CHAOS_ENABLE_FLOAT == 1)
    /** @brief 32-bit single-precision floating point (IEEE-754). */
    typedef float  chaos_f32_t;

    /** @brief 64-bit double-precision floating point (IEEE-754). */
    typedef double chaos_f64_t;
#endif
/** @} */

/* ============================================================= */
/* CHARACTER / STRING TYPES                                         */
/* ============================================================= */

/**
 * @name Character and String Types
 * @brief Explicit types for single characters and character buffers.
 * @{
 */

/** @brief Single character type (8-bit). */
typedef chaos_u8_t chaos_char_t;

/** @brief Null-terminated string type pointer. */
typedef chaos_char_t *chaos_cstr_t;

/** @brief Define a null character for convenience. */
#define CHAOS_CHAR_NULL ((chaos_char_t)0)

/** @} */


/* ============================================================= */
/* COMPILE-TIME VALIDATION                     */
/* ============================================================= */

/**
* @brief Static assertion macro for C99.
* * Triggers a compilation error if the condition is false by declaring 
* an array with a negative size.
* @param cond The condition to evaluate.
* @param name A unique identifier for the assertion (used in the type name).
*/
#define CHAOS_STATIC_ASSERT(cond, name) \
    typedef char static_assert_##name[(cond) ? 1 : -1]

#if defined(CHAOS_STRICT_ABI_CHECK) && (CHAOS_STRICT_ABI_CHECK == 1)

    /* Integer width checks */
    CHAOS_STATIC_ASSERT(sizeof(chaos_i8_t)  == 1, i8_must_be_1_byte);
    CHAOS_STATIC_ASSERT(sizeof(chaos_u8_t)  == 1, u8_must_be_1_byte);
    CHAOS_STATIC_ASSERT(sizeof(chaos_i16_t) == 2, i16_must_be_2_bytes);
    CHAOS_STATIC_ASSERT(sizeof(chaos_u16_t) == 2, u16_must_be_2_bytes);
    CHAOS_STATIC_ASSERT(sizeof(chaos_i32_t) == 4, i32_must_be_4_bytes);
    CHAOS_STATIC_ASSERT(sizeof(chaos_u32_t) == 4, u32_must_be_4_bytes);

#if defined(CHAOS_ENABLE_INT64) && (CHAOS_ENABLE_INT64 == 1)
    CHAOS_STATIC_ASSERT(sizeof(chaos_i64_t) == 8, i64_must_be_8_bytes);
    CHAOS_STATIC_ASSERT(sizeof(chaos_u64_t) == 8, u64_must_be_8_bytes);
#endif /* CHAOS_ENABLE_INT64 */

    /* Boolean validation */
    CHAOS_STATIC_ASSERT(sizeof(chaos_bool_t) == 1, bool_must_be_1_byte);

#if defined(CHAOS_ENABLE_FLOAT) && (CHAOS_ENABLE_FLOAT == 1)
    /* Float validation (IEEE-754 assumed) */
    CHAOS_STATIC_ASSERT(sizeof(chaos_f32_t) == 4, f32_must_be_4_bytes);
    CHAOS_STATIC_ASSERT(sizeof(chaos_f64_t) == 8, f64_must_be_8_bytes);
#endif /* CHAOS_ENABLE_FLOAT */
#endif /* CHAOS_STRICT_ABI_CHECK */
/* ============================================================= */
/* LIMIT CONSTANTS                        */
/* ============================================================= */

/**
 * @name Integer Limit Constants
 * @brief Minimum and maximum values for chaos integer types.
 * @{
 */

#define chaos_u8_t_MAX   ((chaos_u8_t)0xFFU)      /**< Max value of chaos_u8_t  */
#define chaos_i8_t_MIN   ((chaos_i8_t)0x80)       /**< Min value of chaos_i8_t  */
#define chaos_i8_t_MAX   ((chaos_i8_t)0x7F)       /**< Max value of chaos_i8_t  */

#define chaos_u16_t_MAX  ((chaos_u16_t)0xFFFFU)   /**< Max value of chaos_u16_t */
#define chaos_i16_t_MIN  ((chaos_i16_t)0x8000)    /**< Min value of chaos_i16_t */
#define chaos_i16_t_MAX  ((chaos_i16_t)0x7FFF)    /**< Max value of chaos_i16_t */

#define chaos_u32_t_MAX  ((chaos_u32_t)0xFFFFFFFFUL) /**< Max value of chaos_u32_t */
#define chaos_i32_t_MIN  ((chaos_i32_t)0x80000000L)  /**< Min value of chaos_i32_t */
#define chaos_i32_t_MAX  ((chaos_i32_t)0x7FFFFFFFL)  /**< Max value of chaos_i32_t */

#if defined(CHAOS_ENABLE_INT64) && (CHAOS_ENABLE_INT64 == 1)
#define chaos_u64_t_MAX  ((chaos_u64_t)0xFFFFFFFFFFFFFFFFULL) /**< Max value of chaos_u64_t */
#define chaos_i64_t_MIN  ((chaos_i64_t)0x8000000000000000LL)  /**< Min value of chaos_i64_t */
#define chaos_i64_t_MAX  ((chaos_i64_t)0x7FFFFFFFFFFFFFFFLL)  /**< Max value of chaos_i64_t */
#endif

/** @} */

/* ============================================================= */
/* NULL DEFINITION                      */
/* ============================================================= */

/**
 * @brief Define CHAOS_NULL if it hasn't been defined yet.
 * * Safe pointer constant representing a null pointer.
 */
#ifndef CHAOS_NULL
#define CHAOS_NULL ((void *)0)
#endif

#endif /* CHAOS_TYPES_H */