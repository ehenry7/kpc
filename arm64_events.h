#ifndef ARM64_EVENTS_H
#define ARM64_EVENTS_H

struct {
    const char *name;
    unsigned int code;
} rawEvent;

#define NUMBER_OF_RAW_EVENTS 1023

struct rawEvent rawEvents[NUMBER_OF_RAW_EVENTS] = {
    {"SW_INCR", 0x0000},
    {"L1I_CACHE_REFILL", 0x0001},
    {"L1I_TLB_REFILL", 0x0002},
    {"L1D_CACHE_REFILL", 0x0003},
    {"L1D_CACHE", 0x0004},
    {"L1D_TLB_REFILL",	0x0005},
    {"INST_RETIRED",	0x0008},
    {"EXC_TAKEN",	0x0009},
    {"EXC_RETURN",	0x000a},
    {"CID_WRITE_RETIRED",	0x000b},
    {"BR_IMMED_RETIRED",	0x000d},
    {"BR_RETURN_RETIRED",	0x000e},
    {"BR_MIS_PRED",	0x0010},
    {"CPU_CYCLES",	0x0011},
    {"BR_PRED",	0x0012},
    {"MEM_ACCESS",	0x0013},
    {"L1I_CACHE",	0x0014},
    {"L1D_CACHE_WB",	0x0015},
    {"L2D_CACHE",	0x0016},
    {"L2D_CACHE_REFILL",	0x0017},
    {"L2D_CACHE_WB",	0x0018},
    {"BUS_ACCESS",	0x0019},
    {"MEMORY_ERROR",	0x001a},
    {"INST_SPEC",	0x001b},
    {"TTBR_WRITE_RETIRED",	0x001c},
    {"BUS_CYCLES",	0x001d},
    {"CHAIN",	0x001e},
};


#endif // ARM64_EVENTS_H