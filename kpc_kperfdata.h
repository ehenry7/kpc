// =============================================================================
// <kperfdata.framework> header (reverse engineered)
// Provides functions to access the local CPU database for performance events.
// =============================================================================

#ifndef KPC_KPERFDATA_H
#define KPC_KPERFDATA_H

#include "kpc_types.h"

// KPEP CPU architecture constants
#define KPEP_ARCH_I386      0
#define KPEP_ARCH_X86_64    1
#define KPEP_ARCH_ARM       2
#define KPEP_ARCH_ARM64     3

// KPEP event struct
typedef struct kpep_event {
    const char *name;
    const char *description;
    const char *errata;
    const char *alias;
    const char *fallback;
    u32 mask;
    u8 number;
    u8 umask;
    u8 reserved;
    u8 is_fixed;
} kpep_event;

// KPEP database struct
typedef struct kpep_db {
    const char *name;
    const char *cpu_id;
    const char *marketing_name;
    void *plist_data;
    void *event_map;
    kpep_event *event_arr;
    kpep_event **fixed_event_arr;
    void *alias_map;
    usize reserved_1;
    usize reserved_2;
    usize reserved_3;
    usize event_count;
    usize alias_count;
    usize fixed_counter_count;
    usize config_counter_count;
    usize power_counter_count;
    u32 archtecture;
    u32 fixed_counter_bits;
    u32 config_counter_bits;
    u32 power_counter_bits;
} kpep_db;

// KPEP config struct
typedef struct kpep_config {
    kpep_db *db;
    kpep_event **ev_arr;
    usize *ev_map;
    usize *ev_idx;
    u32 *flags;
    u64 *kpc_periods;
    usize event_count;
    usize counter_count;
    u32 classes;
    u32 config_counter;
    u32 power_counter;
    u32 reserved;
} kpep_config;

// KPEP error codes and names
typedef enum {
    KPEP_CONFIG_ERROR_NONE = 0,
    KPEP_CONFIG_ERROR_INVALID_ARGUMENT,
    KPEP_CONFIG_ERROR_OUT_OF_MEMORY,
    KPEP_CONFIG_ERROR_IO,
    KPEP_CONFIG_ERROR_BUFFER_TOO_SMALL,
    KPEP_CONFIG_ERROR_CUR_SYSTEM_UNKNOWN,
    KPEP_CONFIG_ERROR_DB_PATH_INVALID,
    KPEP_CONFIG_ERROR_DB_NOT_FOUND,
    KPEP_CONFIG_ERROR_DB_ARCH_UNSUPPORTED,
    KPEP_CONFIG_ERROR_DB_VERSION_UNSUPPORTED,
    KPEP_CONFIG_ERROR_DB_CORRUPT,
    KPEP_CONFIG_ERROR_EVENT_NOT_FOUND,
    KPEP_CONFIG_ERROR_CONFLICTING_EVENTS,
    KPEP_CONFIG_ERROR_COUNTERS_NOT_FORCED,
    KPEP_CONFIG_ERROR_EVENT_UNAVAILABLE,
    KPEP_CONFIG_ERROR_ERRNO,
    KPEP_CONFIG_ERROR_MAX
} kpep_config_error_code;

extern int (*kpep_config_create)(kpep_db *db, kpep_config **cfg_ptr);
extern void (*kpep_config_free)(kpep_config *cfg);
extern int (*kpep_config_add_event)(kpep_config *cfg, kpep_event **ev_ptr, u32 flag, u32 *err);
extern int (*kpep_config_remove_event)(kpep_config *cfg, usize idx);
extern int (*kpep_config_force_counters)(kpep_config *cfg);
extern int (*kpep_config_events_count)(kpep_config *cfg, usize *count_ptr);
extern int (*kpep_config_events)(kpep_config *cfg, kpep_event **buf, usize buf_size);
extern int (*kpep_config_kpc)(kpep_config *cfg, kpc_config_t *buf, usize buf_size);
extern int (*kpep_config_kpc_count)(kpep_config *cfg, usize *count_ptr);
extern int (*kpep_config_kpc_classes)(kpep_config *cfg, u32 *classes_ptr);
extern int (*kpep_config_kpc_map)(kpep_config *cfg, usize *buf, usize buf_size);
extern int (*kpep_db_create)(const char *name, kpep_db **db_ptr);
extern void (*kpep_db_free)(kpep_db *db);
extern int (*kpep_db_name)(kpep_db *db, const char **name);
extern int (*kpep_db_aliases_count)(kpep_db *db, usize *count);
extern int (*kpep_db_aliases)(kpep_db *db, const char **buf, usize buf_size);
extern int (*kpep_db_counters_count)(kpep_db *db, u8 classes, usize *count);
extern int (*kpep_db_events_count)(kpep_db *db, usize *count);
extern int (*kpep_db_events)(kpep_db *db, kpep_event **buf, usize buf_size);
extern int (*kpep_db_event)(kpep_db *db, const char *name, kpep_event **ev_ptr);
extern int (*kpep_event_name)(kpep_event *ev, const char **name_ptr);
extern int (*kpep_event_alias)(kpep_event *ev, const char **alias_ptr);
extern int (*kpep_event_description)(kpep_event *ev, const char **str_ptr);

// Error description helper
const char *kpep_config_error_desc(int code);

#endif // KPC_KPERFDATA_H