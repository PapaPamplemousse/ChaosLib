/**
 * @file chaos_string.c
 * @brief Implementation of safe string operations for CHAOSLIB.
 */

#include "chaos_string.h"
#include "chaos_assert.h"

/* ============================================================= */
/* STRLEN                                                        */
/* ============================================================= */

chaos_status_t chaos_strlen(
    const chaos_cstr_t str,
    chaos_size_t *len
)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_size_t count = 0U;

    chaos_assert_not_null(str, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(len, &status, CHAOS_MODULE_STRING);

    if (status == CHAOS_STATUS_OK)
    {
        while (str[count] != CHAOS_CHAR_NULL)
        {
            count++;
        }

        *len = count;
    }
    return status;
}

/* ============================================================= */
/* STRCPY                                                        */ 
/* ============================================================= */
chaos_status_t chaos_strcpy(
    chaos_cstr_t dst,
    const chaos_cstr_t src,
    chaos_size_t dst_size
)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_size_t i = 0U;

    chaos_assert_not_null(dst, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(src, &status, CHAOS_MODULE_STRING);
    chaos_assert_param((dst_size != 0U), &status, CHAOS_SEVERITY_ERROR, CHAOS_MODULE_STRING, CHAOS_STRING_TRUNCATED);

    if (status == CHAOS_STATUS_OK)
    {
        while ((src[i] != CHAOS_CHAR_NULL) && (i < (dst_size - 1U)))
        {
            dst[i] = src[i];
            i++;
        }

        /* Always null-terminate */
        dst[i] = CHAOS_CHAR_NULL;

        /* Detect truncation */
        if (src[i] != CHAOS_CHAR_NULL)
        {
            status = CHAOS_STATUS_MAKE(
                CHAOS_SEVERITY_WARNING,
                CHAOS_MODULE_STRING,
                CHAOS_ERRCLASS_OVERFLOW,
                CHAOS_STRING_TRUNCATED
            );
        }
    }
    return status;
}


/* ============================================================= */
/* STRCAT                                                        */
/* ============================================================= */

chaos_status_t chaos_strcat(
    chaos_cstr_t dst,
    const chaos_cstr_t src,
    chaos_size_t dst_size
)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_size_t dst_len = 0U;
    chaos_size_t i = 0U;

    chaos_assert_not_null(dst, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(src, &status, CHAOS_MODULE_STRING);
    chaos_assert_param((dst_size != 0U), &status,
                       CHAOS_SEVERITY_ERROR,
                       CHAOS_MODULE_STRING,
                       CHAOS_STRING_TRUNCATED);

    if (status == CHAOS_STATUS_OK)
    {
        /* Find end of dst */
        while ((dst_len < dst_size) && (dst[dst_len] != CHAOS_CHAR_NULL))
        {
            dst_len++;
        }

        /* dst not null-terminated within dst_size */
        if (dst_len >= dst_size)
        {
            status = CHAOS_STATUS_MAKE(
                CHAOS_SEVERITY_ERROR,
                CHAOS_MODULE_STRING,
                CHAOS_ERRCLASS_OVERFLOW,
                CHAOS_STRING_TRUNCATED
            );
        }
        else
        {
            /* Append src */
            while ((src[i] != CHAOS_CHAR_NULL) &&
                   ((dst_len + i) < (dst_size - 1U)))
            {
                dst[dst_len + i] = src[i];
                i++;
            }

            /* Always null-terminate */
            dst[dst_len + i] = CHAOS_CHAR_NULL;

            /* Detect truncation */
            if (src[i] != CHAOS_CHAR_NULL)
            {
                status = CHAOS_STATUS_MAKE(
                    CHAOS_SEVERITY_WARNING,
                    CHAOS_MODULE_STRING,
                    CHAOS_ERRCLASS_OVERFLOW,
                    CHAOS_STRING_TRUNCATED
                );
            }
        }
    }

    return status;
}


/* ============================================================= */
/* STRCMP                                                        */
/* ============================================================= */

chaos_status_t chaos_strcmp(
    const chaos_cstr_t str1,
    const chaos_cstr_t str2,
    chaos_bool_t *equal
)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_size_t i = 0U;

    chaos_assert_not_null(str1, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(str2, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(equal, &status, CHAOS_MODULE_STRING);

    if (status == CHAOS_STATUS_OK)
    {
        *equal = CHAOS_TRUE;

        while ((str1[i] != CHAOS_CHAR_NULL) &&
               (str2[i] != CHAOS_CHAR_NULL) &&
               (*equal == CHAOS_TRUE))
        {
            if (str1[i] != str2[i])
            {
                *equal = CHAOS_FALSE;
            }
            i++;
        }

        if (str1[i] != str2[i])
        {
            *equal = CHAOS_FALSE;
        }
    }

    return status;
}


/* ============================================================= */
/* STRSTR                                                        */
/* ============================================================= */

chaos_status_t chaos_strstr(
    const chaos_cstr_t str,
    const chaos_cstr_t substr,
    chaos_bool_t *found
)
{
    chaos_status_t status = CHAOS_STATUS_OK;
    chaos_size_t i = 0U;
    chaos_size_t j = 0U;

    chaos_assert_not_null(str, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(substr, &status, CHAOS_MODULE_STRING);
    chaos_assert_not_null(found, &status, CHAOS_MODULE_STRING);

    if (status == CHAOS_STATUS_OK)
    {
        *found = CHAOS_FALSE;

        /* Empty substring always matches */
        if (substr[0] == CHAOS_CHAR_NULL)
        {
            *found = CHAOS_TRUE;
        }
        else
        {
            while ((str[i] != CHAOS_CHAR_NULL) && (*found == CHAOS_FALSE))
            {
                j = 0U;

                while ((substr[j] != CHAOS_CHAR_NULL) &&
                       (str[i + j] != CHAOS_CHAR_NULL) &&
                       (str[i + j] == substr[j]))
                {
                    j++;
                }

                if (substr[j] == CHAOS_CHAR_NULL)
                {
                    *found = CHAOS_TRUE;
                }

                i++;
            }
        }
    }

    return status;
}
