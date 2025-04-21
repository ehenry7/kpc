// =============================================================================
// kperfdata.framework function pointer definitions
// These are set at runtime via dynamic loading.
// =============================================================================

#include "kpc_kperfdata.h"

int (*kpep_config_create)(kpep_db *db, kpep_config **cfg_ptr) = NULL;
void (*kpep_config_free)(kpep_config *cfg) = NULL;
int (*kpep_config_add_event)(kpep_config *cfg, kpep_event **ev_ptr, u32 flag, u32 *err) = NULL;
int (*kpep_config_remove_event)(kpep_config *cfg, usize idx) = NULL;
int (*kpep_config_force_counters)(kpep_config *cfg) = NULL;
int (*kpep_config_events_count)(kpep_config *cfg, usize *count_ptr) = NULL;
int (*kpep_config_events)(kpep_config *cfg, kpep_event **buf, usize buf_size) = NULL;
int (*kpep_config_kpc)(kpep_config *cfg, kpc_config_t *buf, usize buf_size) = NULL;
int (*kpep_config_kpc_count)(kpep_config *cfg, usize *count_ptr) = NULL;
int (*kpep_config_kpc_classes)(kpep_config *cfg, u32 *classes_ptr) = NULL;
int (*kpep_config_kpc_map)(kpep_config *cfg, usize *buf, usize buf_size) = NULL;
int (*kpep_db_create)(const char *name, kpep_db **db_ptr) = NULL;
void (*kpep_db_free)(kpep_db *db) = NULL;
int (*kpep_db_name)(kpep_db *db, const char **name) = NULL;
int (*kpep_db_aliases_count)(kpep_db *db, usize *count) = NULL;
int (*kpep_db_aliases)(kpep_db *db, const char **buf, usize buf_size) = NULL;
int (*kpep_db_counters_count)(kpep_db *db, u8 classes, usize *count) = NULL;
int (*kpep_db_events_count)(kpep_db *db, usize *count) = NULL;
int (*kpep_db_events)(kpep_db *db, kpep_event **buf, usize buf_size) = NULL;
int (*kpep_db_event)(kpep_db *db, const char *name, kpep_event **ev_ptr) = NULL;
int (*kpep_event_name)(kpep_event *ev, const char **name_ptr) = NULL;
int (*kpep_event_alias)(kpep_event *ev, const char **alias_ptr) = NULL;
int (*kpep_event_description)(kpep_event *ev, const char **str_ptr) = NULL;

// Error names array
static const char *kpep_config_error_names[KPEP_CONFIG_ERROR_MAX] = {
    "none",
    "invalid argument",
    "out of memory",
    "I/O",
    "buffer too small",
    "current system unknown",
    "database path invalid",
    "database not found",
    "database architecture unsupported",
    "database version unsupported",
    "database corrupt",
    "event not found",
    "conflicting events",
    "all counters must be forced",
    "event unavailable",
    "check errno"
};

// Error description
const char *kpep_config_error_desc(int code) {
    if (0 <= code && code < KPEP_CONFIG_ERROR_MAX) {
        return kpep_config_error_names[code];
    }
    return "unknown error";
}