#include "chaos_memory.h"
#include "chaos_types.h"
#include "chaos_status.h"
#include "chaos_test.h"

/* -------------------------------------------------------------------------- */
/* Tests                                                                       */
/* -------------------------------------------------------------------------- */

static int test_memcmp_equal(void)
{
    chaos_u8_t a[4] = {1,2,3,4};
    chaos_u8_t b[4] = {1,2,3,4};
    chaos_bool_t equal = CHAOS_FALSE;

    chaos_status_t status = chaos_memcmp(a, b, 4U, &equal);

    TEST_ASSERT(status == CHAOS_STATUS_OK, "status should be OK");
    TEST_ASSERT(equal == CHAOS_TRUE, "buffers should be equal");

    TEST_PASS("memcmp equal");
}

static int test_memcmp_not_equal(void)
{
    chaos_u8_t a[4] = {1,2,3,4};
    chaos_u8_t b[4] = {1,2,9,4};
    chaos_bool_t equal = CHAOS_TRUE;

    chaos_status_t status = chaos_memcmp(a, b, 4U, &equal);

    TEST_ASSERT(status == CHAOS_STATUS_OK, "status should be OK");
    TEST_ASSERT(equal == CHAOS_FALSE, "buffers should not be equal");

    TEST_PASS("memcmp not equal");
}

static int test_memcmp_size_zero(void)
{
    chaos_u8_t a[2] = {1,2};
    chaos_u8_t b[2] = {1,2};
    chaos_bool_t equal = CHAOS_FALSE;

    chaos_status_t status = chaos_memcmp(a, b, 0U, &equal);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "size == 0 should warn/fail");

    TEST_PASS("memcmp size zero");
}

static int test_memcmp_buf1_null(void)
{
    chaos_u8_t b[2] = {1,2};
    chaos_bool_t equal = CHAOS_FALSE;

    chaos_status_t status = chaos_memcmp(NULL, b, 2U, &equal);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "buf1 NULL should fail");

    TEST_PASS("memcmp buf1 NULL");
}

static int test_memcmp_buf2_null(void)
{
    chaos_u8_t a[2] = {1,2};
    chaos_bool_t equal = CHAOS_FALSE;

    chaos_status_t status = chaos_memcmp(a, NULL, 2U, &equal);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "buf2 NULL should fail");

    TEST_PASS("memcmp buf2 NULL");
}

static int test_memcmp_equal_null(void)
{
    chaos_u8_t a[2] = {1,2};
    chaos_u8_t b[2] = {1,2};

    chaos_status_t status = chaos_memcmp(a, b, 2U, NULL);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "equal NULL should fail");

    TEST_PASS("memcmp equal NULL");
}

/* -------------------------------------------------------------------------- */
/* Runner                                                                      */
/* -------------------------------------------------------------------------- */

int main(void)
{
    int failures = 0;

    failures += test_memcmp_equal();
    failures += test_memcmp_not_equal();
    failures += test_memcmp_size_zero();
    failures += test_memcmp_buf1_null();
    failures += test_memcmp_buf2_null();
    failures += test_memcmp_equal_null();

    if (failures == 0)
    {
        printf("\nAll chaos_memcmp tests passed \n");
        return 0;
    }

    printf("\n%d test(s) failed \n", failures);
    return 1;
}
