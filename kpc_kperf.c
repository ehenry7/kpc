// =============================================================================
// kperf.framework function pointer definitions
// These are set at runtime via dynamic loading.
// =============================================================================

#include "kpc_kperf.h"

int  (*kpc_cpu_string)(char *buf, usize buf_size) = NULL;
u32  (*kpc_pmu_version)(void) = NULL;
u32  (*kpc_get_counting)(void) = NULL;
int  (*kpc_set_counting)(u32 classes) = NULL;
u32  (*kpc_get_thread_counting)(void) = NULL;
int  (*kpc_set_thread_counting)(u32 classes) = NULL;
u32  (*kpc_get_config_count)(u32 classes) = NULL;
int  (*kpc_get_config)(u32 classes, kpc_config_t *config) = NULL;
int  (*kpc_set_config)(u32 classes, kpc_config_t *config) = NULL;
u32  (*kpc_get_counter_count)(u32 classes) = NULL;
int  (*kpc_get_cpu_counters)(bool all_cpus, u32 classes, int *curcpu, u64 *buf) = NULL;
int  (*kpc_get_thread_counters)(u32 tid, u32 buf_count, u64 *buf) = NULL;
int  (*kpc_force_all_ctrs_set)(int val) = NULL;
int  (*kpc_force_all_ctrs_get)(int *val_out) = NULL;
int  (*kperf_action_count_set)(u32 count) = NULL;
int  (*kperf_action_count_get)(u32 *count) = NULL;
int  (*kperf_action_samplers_set)(u32 actionid, u32 sample) = NULL;
int  (*kperf_action_samplers_get)(u32 actionid, u32 *sample) = NULL;
int  (*kperf_action_filter_set_by_task)(u32 actionid, i32 port) = NULL;
int  (*kperf_action_filter_set_by_pid)(u32 actionid, i32 pid) = NULL;
int  (*kperf_timer_count_set)(u32 count) = NULL;
int  (*kperf_timer_count_get)(u32 *count) = NULL;
int  (*kperf_timer_period_set)(u32 actionid, u64 tick) = NULL;
int  (*kperf_timer_period_get)(u32 actionid, u64 *tick) = NULL;
int  (*kperf_timer_action_set)(u32 actionid, u32 timerid) = NULL;
int  (*kperf_timer_action_get)(u32 actionid, u32 *timerid) = NULL;
int  (*kperf_timer_pet_set)(u32 timerid) = NULL;
int  (*kperf_timer_pet_get)(u32 *timerid) = NULL;
int  (*kperf_sample_set)(u32 enabled) = NULL;
int  (*kperf_sample_get)(u32 *enabled) = NULL;
int  (*kperf_reset)(void) = NULL;
u64  (*kperf_ns_to_ticks)(u64 ns) = NULL;
u64  (*kperf_ticks_to_ns)(u64 ticks) = NULL;
u64  (*kperf_tick_frequency)(void) = NULL;

// Lightweight PET helpers
#include <sys/sysctl.h>

int kperf_lightweight_pet_get(u32 *enabled) {
    if (!enabled) return -1;
    usize size = 4;
    return sysctlbyname("kperf.lightweight_pet", enabled, &size, NULL, 0);
}

int kperf_lightweight_pet_set(u32 enabled) {
    return sysctlbyname("kperf.lightweight_pet", NULL, NULL, &enabled, 4);
}