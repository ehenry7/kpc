// =============================================================================
// kdebug/ktrace utility function implementations
// =============================================================================

#include "kpc_kdebug.h"
#include <string.h>

// Clean up trace buffers and reset ktrace/kdebug/kperf.
int kdebug_reset(void) {
    int mib[3] = { CTL_KERN, KERN_KDEBUG, KERN_KDREMOVE };
    return sysctl(mib, 3, NULL, NULL, NULL, 0);
}

// Disable and reinitialize the trace buffers.
int kdebug_reinit(void) {
    int mib[3] = { CTL_KERN, KERN_KDEBUG, KERN_KDSETUP };
    return sysctl(mib, 3, NULL, NULL, NULL, 0);
}

// Set debug filter.
int kdebug_setreg(kd_regtype *kdr) {
    int mib[3] = { CTL_KERN, KERN_KDEBUG, KERN_KDSETREG };
    usize size = sizeof(kd_regtype);
    return sysctl(mib, 3, kdr, &size, NULL, 0);
}

// Set maximum number of trace entries (kd_buf).
int kdebug_trace_setbuf(int nbufs) {
    int mib[4] = { CTL_KERN, KERN_KDEBUG, KERN_KDSETBUF, nbufs };
    return sysctl(mib, 4, NULL, NULL, NULL, 0);
}

// Enable or disable kdebug trace.
int kdebug_trace_enable(bool enable) {
    int mib[4] = { CTL_KERN, KERN_KDEBUG, KERN_KDENABLE, enable };
    return sysctl(mib, 4, NULL, 0, NULL, 0);
}

// Retrieve trace buffer information from kernel.
int kdebug_get_bufinfo(kbufinfo_t *info) {
    if (!info) return -1;
    int mib[3] = { CTL_KERN, KERN_KDEBUG, KERN_KDGETBUF };
    size_t needed = sizeof(kbufinfo_t);
    return sysctl(mib, 3, info, &needed, NULL, 0);
}

// Retrieve trace buffers from kernel.
int kdebug_trace_read(void *buf, usize len, usize *count) {
    if (count) *count = 0;
    if (!buf || !len) return -1;
    int mib[3] = { CTL_KERN, KERN_KDEBUG, KERN_KDREADTR };
    int ret = sysctl(mib, 3, buf, &len, NULL, 0);
    if (ret != 0) return ret;
    *count = len;
    return 0;
}

// Block until there are new buffers filled or `timeout_ms` have passed.
int kdebug_wait(usize timeout_ms, bool *suc) {
    if (timeout_ms == 0) return -1;
    int mib[3] = { CTL_KERN, KERN_KDEBUG, KERN_KDBUFWAIT };
    usize val = timeout_ms;
    int ret = sysctl(mib, 3, NULL, &val, NULL, 0);
    if (suc) *suc = !!val;
    return ret;
}