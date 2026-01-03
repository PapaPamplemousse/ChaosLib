#include <stdio.h>
#include "chaos_string.h"
#include "chaos_test.h"

int main(void)
{
    char dst[12] = "hello";
    chaos_status_t status;

    status = chaos_strcat((chaos_cstr_t)dst, (chaos_cstr_t)" world", sizeof(dst));
    TEST_ASSERT(status == CHAOS_STATUS_OK, "strcat normal status");
    TEST_ASSERT(dst[0] == 'h' && dst[10] == 'd', "strcat content");

    status = chaos_strcat((chaos_cstr_t)dst, (chaos_cstr_t)"!!!", sizeof(dst));
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcat overflow");

    status = chaos_strcat(NULL, (chaos_cstr_t)"abc", sizeof(dst));
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcat NULL dst");

    status = chaos_strcat((chaos_cstr_t)dst, NULL, sizeof(dst));
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcat NULL src");

    TEST_PASS("strcat");
}
