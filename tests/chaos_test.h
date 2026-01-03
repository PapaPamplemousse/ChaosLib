#ifndef CHAOS_TEST_H
#define CHAOS_TEST_H

#include <stdio.h>

/* -------------------------------------------------------------------------- */
/* Test helpers                                                                */
/* -------------------------------------------------------------------------- */

#define TEST_ASSERT(cond, msg)                             \
    do                                                     \
    {                                                      \
        if (!(cond))                                      \
        {                                                  \
            printf("[FAIL] %s\n", msg);                    \
            return 1;                                     \
        }                                                  \
    } while (0)

#define TEST_PASS(msg)                                     \
    do                                                     \
    {                                                      \
        printf("[PASS] %s\n", msg);                        \
        return 0;                                         \
    } while (0)

#define TEST_INFO(msg)                                     \
    do                                                     \
    {                                                      \
        printf("[INFO] %s\n", msg);                        \
    } while (0)

#endif /* CHAOS_TEST_H */
