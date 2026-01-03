#include <string.h>

#include "chaos_memory.h"
#include "chaos_types.h"
#include "chaos_status.h"

#include "chaos_test.h"

/* -------------------------------------------------------------------------- */
/* Tests                                                                       */
/* -------------------------------------------------------------------------- */

static int test_memmove_nominal(void)
{
    chaos_u8_t src[6] = {1,2,3,4,5,6};
    chaos_u8_t dst[6] = {0};

    chaos_status_t status = chaos_memmove(dst, src, sizeof(src));

    TEST_ASSERT(status == CHAOS_STATUS_OK, "status should be OK");

    for (chaos_size_t i = 0U; i < sizeof(src); i++)
    {
        TEST_ASSERT(dst[i] == src[i], "content mismatch");
    }

    TEST_PASS("memmove nominal");
}

static int test_memmove_overlap_forward(void)
{
    chaos_u8_t buf[8] = {1,2,3,4,5,6,7,8};

    /* dst < src, overlap */
    chaos_status_t status = chaos_memmove(&buf[0], &buf[2], 6U);

    TEST_ASSERT(status == CHAOS_STATUS_OK, "overlap forward failed");

    chaos_u8_t expected[8] = {3,4,5,6,7,8,7,8};

    for (chaos_size_t i = 0U; i < 8U; i++)
    {
        TEST_ASSERT(buf[i] == expected[i], "forward overlap mismatch");
    }

    TEST_PASS("memmove overlap forward");
}

static int test_memmove_overlap_backward(void)
{
    chaos_u8_t buf[8] = {1,2,3,4,5,6,7,8};

    /* dst > src, overlap */
    chaos_status_t status = chaos_memmove(&buf[2], &buf[0], 6U);

    TEST_ASSERT(status == CHAOS_STATUS_OK, "overlap backward failed");

    chaos_u8_t expected[8] = {1,2,1,2,3,4,5,6};

    for (chaos_size_t i = 0U; i < 8U; i++)
    {
        TEST_ASSERT(buf[i] == expected[i], "backward overlap mismatch");
    }

    TEST_PASS("memmove overlap backward");
}

static int test_memmove_dst_null(void)
{
    chaos_u8_t src[4] = {1,2,3,4};

    chaos_status_t status = chaos_memmove(NULL, src, 4U);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "dst NULL should fail");

    TEST_PASS("memmove dst NULL");
}

static int test_memmove_src_null(void)
{
    chaos_u8_t dst[4] = {0};

    chaos_status_t status = chaos_memmove(dst, NULL, 4U);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "src NULL should fail");

    TEST_PASS("memmove src NULL");
}

/* -------------------------------------------------------------------------- */
/* Runner                                                                      */
/* -------------------------------------------------------------------------- */

int main(void)
{
    int failures = 0;

    failures += test_memmove_nominal();
    failures += test_memmove_overlap_forward();
    failures += test_memmove_overlap_backward();
    failures += test_memmove_dst_null();
    failures += test_memmove_src_null();

    if (failures == 0)
    {
        printf("\nAll chaos_memmove tests passed \n");
        return 0;
    }

    printf("\n%d test(s) failed \n", failures);
    return 1;
}
