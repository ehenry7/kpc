// =============================================================================
// Dynamic loader for kperf and kperfdata frameworks
// =============================================================================

#ifndef KPC_DYNLOAD_H
#define KPC_DYNLOAD_H

#include <stdbool.h>

bool lib_init(void);
void lib_deinit(void);

extern char lib_err_msg[256];

#endif // KPC_DYNLOAD_H