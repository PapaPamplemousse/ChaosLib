#include <stdio.h>
#include "chaos_string.h"
#include "chaos_test.h"

int main(void)
{
    chaos_size_t len = 0U;
    chaos_status_t status;

    status = chaos_strlen((chaos_cstr_t)"hello", &len);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "strlen status ok");
    TEST_ASSERT(len == 5U, "strlen normal");

    status = chaos_strlen((chaos_cstr_t)"", &len);
    TEST_ASSERT(status == CHAOS_STATUS_OK, "strlen empty status");
    TEST_ASSERT(len == 0U, "strlen empty");

    status = chaos_strlen(NULL, &len);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strlen NULL str");

    status = chaos_strlen((chaos_cstr_t)"abc", NULL);
    TEST_ASSERT(status != CHAOS_STATUS_OK, "strlen NULL len");

    TEST_PASS("strlen");
}
