// =============================================================================
// <kperf.framework> header (reverse engineered)
// This framework wraps some sysctl calls to communicate with the kpc in kernel.
// Most functions require root privileges, or process is "blessed".
// =============================================================================

#ifndef KPC_KPERF_H
#define KPC_KPERF_H

#include "kpc_types.h"

// Cross-platform class constants.
#define KPC_CLASS_FIXED         (0)
#define KPC_CLASS_CONFIGURABLE  (1)
#define KPC_CLASS_POWER         (2)
#define KPC_CLASS_RAWPMU        (3)

// Cross-platform class mask constants.
#define KPC_CLASS_FIXED_MASK         (1u << KPC_CLASS_FIXED)        // 1
#define KPC_CLASS_CONFIGURABLE_MASK  (1u << KPC_CLASS_CONFIGURABLE) // 2
#define KPC_CLASS_POWER_MASK         (1u << KPC_CLASS_POWER)        // 4
#define KPC_CLASS_RAWPMU_MASK        (1u << KPC_CLASS_RAWPMU)       // 8

// PMU version constants.
#define KPC_PMU_ERROR     (0) // Error
#define KPC_PMU_INTEL_V3  (1) // Intel
#define KPC_PMU_ARM_APPLE (2) // ARM64
#define KPC_PMU_INTEL_V2  (3) // Old Intel
#define KPC_PMU_ARM_V2    (4) // Old ARM

// The maximum number of counters we could read from every class in one go.
#define KPC_MAX_COUNTERS 32

// Bits for defining what to do on an action.
#define KPERF_SAMPLER_TH_INFO       (1U << 0)
#define KPERF_SAMPLER_TH_SNAPSHOT   (1U << 1)
#define KPERF_SAMPLER_KSTACK        (1U << 2)
#define KPERF_SAMPLER_USTACK        (1U << 3)
#define KPERF_SAMPLER_PMC_THREAD    (1U << 4)
#define KPERF_SAMPLER_PMC_CPU       (1U << 5)
#define KPERF_SAMPLER_PMC_CONFIG    (1U << 6)
#define KPERF_SAMPLER_MEMINFO       (1U << 7)
#define KPERF_SAMPLER_TH_SCHEDULING (1U << 8)
#define KPERF_SAMPLER_TH_DISPATCH   (1U << 9)
#define KPERF_SAMPLER_TK_SNAPSHOT   (1U << 10)
#define KPERF_SAMPLER_SYS_MEM       (1U << 11)
#define KPERF_SAMPLER_TH_INSCYC     (1U << 12)
#define KPERF_SAMPLER_TK_INFO       (1U << 13)

// Maximum number of kperf action ids.
#define KPERF_ACTION_MAX (32)

// Maximum number of kperf timer ids.
#define KPERF_TIMER_MAX (8)

// x86/arm config registers are 64-bit
typedef u64 kpc_config_t;

// Function pointers (extern, defined in kpc_kperf.c; set by dynload)
extern int  (*kpc_cpu_string)(char *buf, usize buf_size);
extern u32  (*kpc_pmu_version)(void);
extern u32  (*kpc_get_counting)(void);
extern int  (*kpc_set_counting)(u32 classes);
extern u32  (*kpc_get_thread_counting)(void);
extern int  (*kpc_set_thread_counting)(u32 classes);
extern u32  (*kpc_get_config_count)(u32 classes);
extern int  (*kpc_get_config)(u32 classes, kpc_config_t *config);
extern int  (*kpc_set_config)(u32 classes, kpc_config_t *config);
extern u32  (*kpc_get_counter_count)(u32 classes);
extern int  (*kpc_get_cpu_counters)(bool all_cpus, u32 classes, int *curcpu, u64 *buf);
extern int  (*kpc_get_thread_counters)(u32 tid, u32 buf_count, u64 *buf);
extern int  (*kpc_force_all_ctrs_set)(int val);
extern int  (*kpc_force_all_ctrs_get)(int *val_out);
extern int  (*kperf_action_count_set)(u32 count);
extern int  (*kperf_action_count_get)(u32 *count);
extern int  (*kperf_action_samplers_set)(u32 actionid, u32 sample);
extern int  (*kperf_action_samplers_get)(u32 actionid, u32 *sample);
extern int  (*kperf_action_filter_set_by_task)(u32 actionid, i32 port);
extern int  (*kperf_action_filter_set_by_pid)(u32 actionid, i32 pid);
extern int  (*kperf_timer_count_set)(u32 count);
extern int  (*kperf_timer_count_get)(u32 *count);
extern int  (*kperf_timer_period_set)(u32 actionid, u64 tick);
extern int  (*kperf_timer_period_get)(u32 actionid, u64 *tick);
extern int  (*kperf_timer_action_set)(u32 actionid, u32 timerid);
extern int  (*kperf_timer_action_get)(u32 actionid, u32 *timerid);
extern int  (*kperf_timer_pet_set)(u32 timerid);
extern int  (*kperf_timer_pet_get)(u32 *timerid);
extern int  (*kperf_sample_set)(u32 enabled);
extern int  (*kperf_sample_get)(u32 *enabled);
extern int  (*kperf_reset)(void);
extern u64  (*kperf_ns_to_ticks)(u64 ns);
extern u64  (*kperf_ticks_to_ns)(u64 ticks);
extern u64  (*kperf_tick_frequency)(void);

// Lightweight PET helpers (not in kperf.framework)
int kperf_lightweight_pet_get(u32 *enabled);
int kperf_lightweight_pet_set(u32 enabled);

#endif // KPC_KPERF_H