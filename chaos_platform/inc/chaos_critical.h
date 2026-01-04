/**
 * @file chaos_critical.h
 * @brief Critical section management hooks for CHAOSLIB.
 */

#ifndef CHAOS_HOOK_H
#define CHAOS_HOOK_H


/**
 * @brief Enter a critical section (disable interrupts/acquire lock)
 * @details This weak function should be overridden to implement platform-specific
 *          critical section entry. In single-threaded environments, this can be empty.
 *          Typical implementations: disable interrupts, acquire mutex, or disable preemption.
 * @note Must be paired with chaos_exit_critical()
 * @see chaos_exit_critical()
 * @return void
 */
extern void chaos_enter_critical(void);

/**
 * @brief Exit a critical section (enable interrupts/release lock)
 * @details This weak function should be overridden to implement platform-specific
 *          critical section exit. Must restore the state changed by chaos_enter_critical().
 * @note Must be paired with chaos_enter_critical()
 * @see chaos_enter_critical()
 * @return void
 */
extern void chaos_exit_critical(void);



#endif /* CHAOS_HOOK_H */
