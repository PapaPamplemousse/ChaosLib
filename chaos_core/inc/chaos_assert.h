#ifndef CHAOS_ASSERT_H
#define CHAOS_ASSERT_H

#include "chaos_types.h"
#include "chaos_status.h"

/* ============================================================= */
/* CONFIGURATION                                                 */
/* ============================================================= */

#ifndef CHAOS_ENABLE_ASSERT
#define CHAOS_ENABLE_ASSERT 0
#endif

/* ============================================================= */
/* INTERNAL HELPERS                                              */
/* ============================================================= */

static inline chaos_bool_t chaos_status_is_ok(chaos_status_t status)
{
    return (status == CHAOS_STATUS_OK) ? CHAOS_TRUE : CHAOS_FALSE;
}

/* ============================================================= */
/* ASSERT FUNCTIONS                                              */
/* ============================================================= */

#if (CHAOS_ENABLE_ASSERT == 1)

/**
 * @brief Assert pointer is not NULL.
 */
static inline void chaos_assert_not_null(
    const void *ptr,
    chaos_status_t *status,
    chaos_module_t module_id
)
{
    if ((status == CHAOS_NULL) || (chaos_status_is_ok(*status) == CHAOS_FALSE))
    {
        /* Do nothing */
    }
    else if (ptr == CHAOS_NULL)
    {
        *status = CHAOS_STATUS_MAKE(
            CHAOS_SEVERITY_ERROR,
            module_id,
            CHAOS_ERRCLASS_NULL_PTR,
            0U
        );
    }
}

/**
 * @brief Assert a parameter condition and update status on failure.
 */
static inline void chaos_assert_param(
    chaos_bool_t cond,
    chaos_status_t *status,
    chaos_severity_t severity,
    chaos_module_t module_id,
    chaos_u8_t code
)
{
    if ((status == CHAOS_NULL) ||
        (chaos_status_is_ok(*status) == CHAOS_FALSE))
    {
        /* Do nothing */
    }
    else if (cond == CHAOS_FALSE)
    {
        *status = CHAOS_STATUS_MAKE(
            severity,
            module_id,
            CHAOS_ERRCLASS_INVALID_PARAM,
            code
        );
    }
}


#else /* CHAOS_ENABLE_ASSERT == 0 */

/* Assertions disabled: compiled but inert */

static inline void chaos_assert_not_null(
    const void *ptr,
    chaos_status_t *status,
    chaos_module_t module_id
)
{
    (void)ptr;
    (void)status;
    (void)module_id;
}

static inline void chaos_assert_param(
    chaos_bool_t cond,
    chaos_status_t *status,
    chaos_severity_t severity,
    chaos_module_t module_id,
    chaos_u8_t code
)
{
    (void)cond;
    (void)status;
    (void)severity;
    (void)module_id;
    (void)code;
}

#endif /* CHAOS_ENABLE_ASSERT */

#endif /* CHAOS_ASSERT_H */
