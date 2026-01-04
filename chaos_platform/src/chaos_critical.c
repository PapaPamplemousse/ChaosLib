
#include "chaos_critical.h"

/**
 * Critical Section Hooks
 */
__attribute__((weak)) void chaos_enter_critical(void) {
    // Default: nothing (single thread)
}

__attribute__((weak)) void chaos_exit_critical(void) {
    // Default: nothing
}




