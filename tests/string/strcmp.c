#include <stdio.h>
#include "chaos_string.h"
#include "chaos_test.h"

int main(void)
{
    chaos_bool_t equal = CHAOS_FALSE;
    chaos_status_t status;

    status = chaos_strcmp((chaos_cstr_t)"abc", (chaos_cstr_t)"abc", &equal);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "strcmp equal status");
    TEST_ASSERT(equal == CHAOS_TRUE, "strcmp equal");

    status = chaos_strcmp((chaos_cstr_t)"abc", (chaos_cstr_t)"abd", &equal);
    TEST_ASSERT(equal == CHAOS_FALSE, "strcmp not equal");

    status = chaos_strcmp((chaos_cstr_t)"abc", (chaos_cstr_t)"abcd", &equal);
    TEST_ASSERT(equal == CHAOS_FALSE, "strcmp length diff");

    status = chaos_strcmp(NULL, (chaos_cstr_t)"abc", &equal);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcmp NULL str1");

    status = chaos_strcmp((chaos_cstr_t)"abc", NULL, &equal);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcmp NULL str2");

    status = chaos_strcmp((chaos_cstr_t)"abc", (chaos_cstr_t)"abc", NULL);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strcmp NULL equal");

    TEST_PASS("strcmp");
}
