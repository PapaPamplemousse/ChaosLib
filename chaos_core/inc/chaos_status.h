/**
 * @file chaos_status.h
 * @brief Unified status and error handling for CHAOSLIB.
 */

#ifndef CHAOS_STATUS_H
#define CHAOS_STATUS_H

#include "chaos_types.h"

/* ============================================================= */
/* STATUS TYPE                                                   */
/* ============================================================= */

typedef chaos_u32_t chaos_status_t;

/* ============================================================= */
/* SEVERITY                                                      */
/* ============================================================= */

/**
 * @brief Defines the impact or urgency of a status result.
 */
typedef enum
{
    CHAOS_SEVERITY_OK      = 0x00U, /**< Operation successful. */
    CHAOS_SEVERITY_WARNING = 0x01U, /**< Operation succeeded with potential issues. */
    CHAOS_SEVERITY_ERROR   = 0x02U, /**< Operation failed, but system remains stable. */
    CHAOS_SEVERITY_FATAL   = 0x03U  /**< Unrecoverable failure. */
} chaos_severity_t;

/* ============================================================= */
/* MODULE IDENTIFIERS                                            */
/* ============================================================= */

/**
 * @brief Identifies the library module that originated the status.
 */
typedef enum
{
    CHAOS_MODULE_NONE     = 0x00U, /**< No specific module (Generic). */
    CHAOS_MODULE_CORE     = 0x01U, /**< Core library functionality. */
    CHAOS_MODULE_TYPES    = 0x02U, /**< Type system and definitions. */
    CHAOS_MODULE_MEMORY   = 0x03U, /**< Low-level memory management. */
    CHAOS_MODULE_STRING   = 0x04U, /**< String handling utilities. */
    CHAOS_MODULE_ALLOC    = 0x05U, /**< Dynamic memory allocators. */
    CHAOS_MODULE_MATH     = 0x06U, /**< Mathematical functions. */
    CHAOS_MODULE_STDLIB   = 0x07U, /**< Standard library wrappers. */
    CHAOS_MODULE_PLATFORM = 0x08U  /**< Platform-specific abstractions. */
} chaos_module_t;

/* ============================================================= */
/* ERROR CLASSES                                                 */
/* ============================================================= */

/**
 * @brief Categorizes the type of error encountered.
 */
typedef enum
{
    CHAOS_ERRCLASS_NONE          = 0x00U, /**< No error category. */
    CHAOS_ERRCLASS_NULL_PTR      = 0x01U, /**< A null pointer was provided. */
    CHAOS_ERRCLASS_OUT_OF_RANGE  = 0x02U, /**< Parameter or index is out of bounds. */
    CHAOS_ERRCLASS_OVERFLOW      = 0x03U, /**< Computation or buffer overflow. */
    CHAOS_ERRCLASS_INVALID_PARAM = 0x04U, /**< An argument is invalid. */
    CHAOS_ERRCLASS_NOT_SUPPORTED = 0x05U, /**< Feature not implemented or supported. */
    CHAOS_ERRCLASS_INTERNAL      = 0x06U  /**< Internal logic or system error. */
} chaos_errclass_t;

/* ============================================================= */
/* CHAOS_MEMORY SPECIFIC ERROR CODES                             */
/* ============================================================= */

/**
 * @brief Specific error codes for the CHAOS_MODULE_MEMORY.
 * * These codes are intended to be used in the 'code' field of a #chaos_status_t
 * when the module is set to #CHAOS_MODULE_MEMORY.
 */
typedef enum
{
    CHAOS_MEM_OK          = 0x00U, /**< Operation successful. */
    CHAOS_MEM_SIZE_ZERO   = 0x01U, /**< Size parameter is zero; no operation performed. */
    CHAOS_MEM_SRC_EQ_DST  = 0x02U, /**< Source and destination addresses are identical; no copy required. */
    CHAOS_MEM_OVERFLOW    = 0x03U, /**< Memory operation would result in a buffer overflow. */
    CHAOS_MEM_ALIGNMENT   = 0x04U, /**< Memory address does not meet the required alignment criteria. */
    CHAOS_MEM_UNKNOWN     = 0xFFU  /**< Generic or unidentified memory error */
} chaos_memory_code_t;


/* ============================================================= */
/* STATUS ENCODING                                               */
/* ============================================================= */

/**
 * @brief Constructs a #chaos_status_t value from its components.
 * * @param sev  Severity level (#chaos_severity_t).
 * @param mod  Originating module (#chaos_module_t).
 * @param cls  Error category (#chaos_errclass_t).
 * @param code Specific 8-bit error code.
 */
#define CHAOS_STATUS_MAKE(sev, mod, cls, code) \
    ((chaos_status_t)( \
        (((chaos_u32_t)(sev)  & 0xFFU) << 24) | \
        (((chaos_u32_t)(mod)  & 0xFFU) << 16) | \
        (((chaos_u32_t)(cls)  & 0xFFU) << 8 ) | \
        ((chaos_u32_t)(code)  & 0xFFU) ))

/* ============================================================= */
/* STATUS DECODING                                               */
/* ============================================================= */

/**
 * @brief Extracts the severity level from a #chaos_status_t.
 */
#define CHAOS_STATUS_SEVERITY(st) \
    ((chaos_severity_t)(((st) >> 24) & 0xFFU))

/**
 * @brief Extracts the module ID from a #chaos_status_t.
 */
#define CHAOS_STATUS_MODULE(st) \
    ((chaos_module_t)(((st) >> 16) & 0xFFU))

/**
 * @brief Extracts the error class from a #chaos_status_t.
 */
#define CHAOS_STATUS_CLASS(st) \
    ((chaos_errclass_t)(((st) >> 8) & 0xFFU))

/**
 * @brief Extracts the specific error code from a #chaos_status_t.
 */
#define CHAOS_STATUS_CODE(st) \
    ((chaos_u8_t)((st) & 0xFFU))

/* ============================================================= */
/* COMMON STATUS VALUES                                          */
/* ============================================================= */

/**
 * @brief Predefined status indicating a successful operation.
 */
#define CHAOS_STATUS_OK \
    CHAOS_STATUS_MAKE(CHAOS_SEVERITY_OK, CHAOS_MODULE_NONE, CHAOS_ERRCLASS_NONE, 0U)

#endif /* CHAOS_STATUS_H */
