#include <stdio.h>
#include "chaos_string.h"
#include "chaos_test.h"

int main(void)
{
    chaos_bool_t found = CHAOS_FALSE;
    chaos_status_t status;

    status = chaos_strstr((chaos_cstr_t)"hello world", (chaos_cstr_t)"world", &found);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "strstr status ok");
    TEST_ASSERT(found == CHAOS_TRUE, "strstr found");

    status = chaos_strstr((chaos_cstr_t)"hello world", (chaos_cstr_t)"mars", &found);
    TEST_ASSERT(found == CHAOS_FALSE, "strstr not found");

    status = chaos_strstr((chaos_cstr_t)"abc", (chaos_cstr_t)"", &found);
    TEST_ASSERT(found == CHAOS_TRUE, "strstr empty substr");

    status = chaos_strstr(NULL, (chaos_cstr_t)"abc", &found);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strstr NULL str");

    status = chaos_strstr((chaos_cstr_t)"abc", NULL, &found);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strstr NULL substr");

    status = chaos_strstr((chaos_cstr_t)"abc", (chaos_cstr_t)"a", NULL);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strstr NULL found");

    TEST_PASS("strstr");
}
