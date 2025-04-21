// =============================================================================
// kdebug private structs and utility function declarations
// =============================================================================

#ifndef KPC_KDEBUG_H
#define KPC_KDEBUG_H

#include "kpc_types.h"
#include <sys/sysctl.h>
#include <stdint.h>

// kd_buf struct (see original file for platform-conditional fields)
#if defined(__arm64__)
typedef uint64_t kd_buf_argtype;
#else
typedef uintptr_t kd_buf_argtype;
#endif

typedef struct {
    uint64_t timestamp;
    kd_buf_argtype arg1;
    kd_buf_argtype arg2;
    kd_buf_argtype arg3;
    kd_buf_argtype arg4;
    kd_buf_argtype arg5;
    uint32_t debugid;
#if defined(__LP64__) || defined(__arm64__)
    uint32_t cpuid;
    kd_buf_argtype unused;
#endif
} kd_buf;

// kd_regtype struct for debug filters
typedef struct {
    unsigned int type;
    unsigned int value1;
    unsigned int value2;
    unsigned int value3;
    unsigned int value4;
} kd_regtype;

// kbufinfo_t struct for trace buffer info
typedef struct {
    int nkdbufs;
    int nolog;
    unsigned int flags;
    int nkdthreads;
    int bufid;
} kbufinfo_t;

// Kdebug utility function declarations
int kdebug_reset(void);
int kdebug_reinit(void);
int kdebug_setreg(kd_regtype *kdr);
int kdebug_trace_setbuf(int nbufs);
int kdebug_trace_enable(bool enable);
int kdebug_get_bufinfo(kbufinfo_t *info);
int kdebug_trace_read(void *buf, usize len, usize *count);
int kdebug_wait(usize timeout_ms, bool *suc);

#endif // KPC_KDEBUG_H