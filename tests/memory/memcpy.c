#include <string.h>

#include "chaos_memory.h"
#include "chaos_types.h"
#include "chaos_status.h"

#include "chaos_test.h"

/* -------------------------------------------------------------------------- */
/* Tests                                                                       */
/* -------------------------------------------------------------------------- */

static int test_memcpy_nominal(void)
{
    chaos_u8_t src[8] = {1,2,3,4,5,6,7,8};
    chaos_u8_t dst[8] = {0};

    chaos_status_t status = chaos_memcpy(dst, src, sizeof(src));

    TEST_ASSERT(status == CHAOS_STATUS_OK, "status should be OK");

    for (chaos_size_t i = 0U; i < sizeof(src); i++)
    {
        TEST_ASSERT(dst[i] == src[i], "memory content mismatch");
    }

    TEST_PASS("memcpy nominal");
}

static int test_memcpy_dst_null(void)
{
    chaos_u8_t src[4] = {1,2,3,4};

    chaos_status_t status = chaos_memcpy(NULL, src, sizeof(src));

    TEST_ASSERT(status != CHAOS_STATUS_OK, "NULL dst should fail");

    TEST_PASS("memcpy dst NULL");
}

static int test_memcpy_src_null(void)
{
    chaos_u8_t dst[4] = {0};

    chaos_status_t status = chaos_memcpy(dst, NULL, sizeof(dst));

    TEST_ASSERT(status != CHAOS_STATUS_OK, "NULL src should fail");

    TEST_PASS("memcpy src NULL");
}

static int test_memcpy_size_zero(void)
{
    chaos_u8_t src[4] = {1,2,3,4};
    chaos_u8_t dst[4] = {0};

    chaos_status_t status = chaos_memcpy(dst, src, 0U);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "size == 0 should warn/fail");

    TEST_PASS("memcpy size zero");
}

static int test_memcpy_same_buffer(void)
{
    chaos_u8_t buf[4] = {1,2,3,4};

    chaos_status_t status = chaos_memcpy(buf, buf, sizeof(buf));

    TEST_ASSERT(status != CHAOS_STATUS_OK, "dst == src should warn/fail");

    TEST_PASS("memcpy dst == src");
}

/* -------------------------------------------------------------------------- */
/* Test runner                                                                 */
/* -------------------------------------------------------------------------- */

int main(void)
{
    int failures = 0;

    failures += test_memcpy_nominal();
    failures += test_memcpy_dst_null();
    failures += test_memcpy_src_null();
    failures += test_memcpy_size_zero();
    failures += test_memcpy_same_buffer();

    if (failures == 0)
    {
        printf("\nAll chaos_memcpy tests passed \n");
        return 0;
    }
    else
    {
        printf("\n%d test(s) failed \n", failures);
        return 1;
    }
}
