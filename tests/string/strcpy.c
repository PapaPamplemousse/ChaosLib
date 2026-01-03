#include <stdio.h>
#include "chaos_string.h"
#include "chaos_test.h"

int main(void)
{
    char dst[10];
    chaos_status_t status;

    status = chaos_strcpy((chaos_cstr_t)dst, (chaos_cstr_t)"abc", sizeof(dst));
    TEST_ASSERT(status == CHAOS_STATUS_OK, "strcpy normal status");
    TEST_ASSERT(dst[0] == 'a' && dst[3] == '\0', "strcpy content");

    status = chaos_strcpy((chaos_cstr_t)dst, (chaos_cstr_t)"123456789ABC", sizeof(dst));
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcpy overflow detected");
    TEST_ASSERT(dst[sizeof(dst) - 1U] == '\0', "strcpy forced null");

    status = chaos_strcpy(NULL, (chaos_cstr_t)"abc", sizeof(dst));
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcpy NULL dst");

    status = chaos_strcpy((chaos_cstr_t)dst, NULL, sizeof(dst));
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcpy NULL src");

    TEST_PASS("strcpy");
}
