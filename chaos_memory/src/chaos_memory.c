#include "chaos_memory.h"
#include "chaos_assert.h"

/* ============================================================= */
/* MEMCPY                                                        */
/* ============================================================= */
chaos_status_t chaos_memcpy(void *dst, const void *src, chaos_size_t size)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    const chaos_u8_t *s = (const chaos_u8_t *)src;
    chaos_u8_t *d = (chaos_u8_t *)dst;
    chaos_size_t i = 0U;

    /* Validate parameters */
    chaos_assert_not_null(dst, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_not_null(src, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_param((size != 0U), &status, CHAOS_SEVERITY_WARNING, CHAOS_MODULE_MEMORY, CHAOS_MEM_SIZE_ZERO);
    chaos_assert_param((dst != src), &status, CHAOS_SEVERITY_WARNING, CHAOS_MODULE_MEMORY, CHAOS_MEM_SRC_EQ_DST);

    /* Perform copy if no errors */
    if (status == CHAOS_STATUS_OK)
    {
        for (i = 0U; i < size; i++)
        {
            d[i] = s[i];
        }
    }

    return status;
}

/* ============================================================= */
/* MEMMOVE                                                          */
/* ============================================================= */
chaos_status_t chaos_memmove(void *dst, const void *src, chaos_size_t size)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_u8_t *d = (chaos_u8_t *)dst;
    const chaos_u8_t *s = (const chaos_u8_t *)src;
    chaos_size_t i = 0U;

    /* Validate parameters */
    chaos_assert_not_null(dst, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_not_null(src, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_param((size != 0U), &status, CHAOS_SEVERITY_WARNING, CHAOS_MODULE_MEMORY, CHAOS_MEM_SIZE_ZERO);
    chaos_assert_param((dst != src), &status, CHAOS_SEVERITY_WARNING, CHAOS_MODULE_MEMORY, CHAOS_MEM_SRC_EQ_DST);

    /* Perform move if no errors */
    if (status == CHAOS_STATUS_OK)
    {
        /* Determine copy direction based on overlap */
        if (d < s)
        {
            for (i = 0U; i < size; i++)
            {
                d[i] = s[i];
            }
        }
        /* Copy backward if dst > src to handle overlap */
        else
        {
            for (i = size; i > 0U; i--)
            {
                d[i-1U] = s[i-1U];
            }
        }
    }

    return status;
}


/* ============================================================= */
/* MEMSET                                                           */
/* ============================================================= */
chaos_status_t chaos_memset(void *dst, chaos_u8_t value, chaos_size_t size)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_u8_t *d = (chaos_u8_t *)dst;
    chaos_size_t i = 0U;

    /* Validate parameters */
    chaos_assert_not_null(dst, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_param((size != 0U), &status, CHAOS_SEVERITY_WARNING, CHAOS_MODULE_MEMORY, CHAOS_MEM_SIZE_ZERO);

    /* Perform set if no errors */
    if (status == CHAOS_STATUS_OK)
    {
        for (i = 0U; i < size; i++)
        {
            d[i] = value;
        }
    }
    return status;
}

/* ============================================================= */
/* MEMCMP                                                           */
/* ============================================================= */
chaos_status_t chaos_memcmp(
    const void *buf1,
    const void *buf2,
    chaos_size_t size,
    chaos_bool_t *equal)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    const chaos_u8_t *b1 = (const chaos_u8_t *)buf1;
    const chaos_u8_t *b2 = (const chaos_u8_t *)buf2;
    chaos_size_t i = 0U;

    /* Validate parameters */
    chaos_assert_not_null(buf1, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_not_null(buf2, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_not_null(equal, &status, CHAOS_MODULE_MEMORY);
    chaos_assert_param((size != 0U), &status, CHAOS_SEVERITY_WARNING, CHAOS_MODULE_MEMORY, CHAOS_MEM_SIZE_ZERO);

    /* Perform comparison if no errors */
    if (status == CHAOS_STATUS_OK)
    {
        /* Default to equal */
        *equal = CHAOS_TRUE;

        for (i = 0U; (i < size)&&(*equal == CHAOS_TRUE); i++)
        {
            if (b1[i] != b2[i])
            {
                *equal = CHAOS_FALSE;
            }
        }
    }

    return status;
}
