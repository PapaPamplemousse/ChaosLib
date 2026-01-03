#include <string.h>

#include "chaos_memory.h"
#include "chaos_types.h"
#include "chaos_status.h"
#include "chaos_test.h"

/* -------------------------------------------------------------------------- */
/* Tests                                                                       */
/* -------------------------------------------------------------------------- */

static int test_memset_nominal(void)
{
    chaos_u8_t buf[8] = {0};

    chaos_status_t status = chaos_memset(buf, 0xAAU, sizeof(buf));

    TEST_ASSERT(status == CHAOS_STATUS_OK, "status should be OK");

    for (chaos_size_t i = 0U; i < sizeof(buf); i++)
    {
        TEST_ASSERT(buf[i] == 0xAAU, "buffer not set correctly");
    }

    TEST_PASS("memset nominal");
}

static int test_memset_size_zero(void)
{
    chaos_u8_t buf[4] = {1,2,3,4};

    chaos_status_t status = chaos_memset(buf, 0xFFU, 0U);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "size == 0 should warn/fail");

    TEST_PASS("memset size zero");
}

static int test_memset_dst_null(void)
{
    chaos_status_t status = chaos_memset(NULL, 0x00U, 4U);

    TEST_ASSERT(status != CHAOS_STATUS_OK, "dst NULL should fail");

    TEST_PASS("memset dst NULL");
}

/* -------------------------------------------------------------------------- */
/* Runner                                                                      */
/* -------------------------------------------------------------------------- */

int main(void)
{
    int failures = 0;

    failures += test_memset_nominal();
    failures += test_memset_size_zero();
    failures += test_memset_dst_null();

    if (failures == 0)
    {
        printf("\nAll chaos_memset tests passed \n");
        return 0;
    }

    printf("\n%d test(s) failed \n", failures);
    return 1;
}
