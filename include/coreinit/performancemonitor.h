#pragma once
#include <wut.h>

/**
 * \defgroup coreinit_performancemonitor Performance Monitor
 * \ingroup coreinit
 *
 * @{
 */


#ifdef __cplusplus
extern "C" {
#endif


/// Used to tell OSSetPerformanceMonitor() which arguments are valid.
typedef enum PerfMonArg {
    PM_ARG_MMCR0 = 1u << 0u,
    PM_ARG_MMCR1 = 1u << 1u,
    PM_ARG_PMC1  = 1u << 2u,
    PM_ARG_PMC2  = 1u << 3u,
    PM_ARG_PMC3  = 1u << 4u,
    PM_ARG_PMC4  = 1u << 5u,
} PerfMonArg;

/**
 * Flags to write to (U)MMCR0 register.
 *
 * \sa OSSetPerformanceMonitor
 */
typedef enum PerfMonMMCR0Flags {
    PM_PMC1_CURRENT                             = 0b0000000u << 6,
    PM_PMC1_CPU_CYCLES                          = 0b0000001u << 6,
    PM_PMC1_INSTRUCTIONS_COMPLETED              = 0b0000010u << 6,
    PM_PMC1_TBL_RISING_TRANSITIONS              = 0b0000011u << 6,
    PM_PMC1_INSTRUCTIONS_DISPATCHED             = 0b0000100u << 6,
    PM_PMC1_EIEIO_INSTRUCTIONS_COMPLETED        = 0b0000101u << 6,
    PM_PMC1_ITLB_SEARCH_CYCLES                  = 0b0000110u << 6,
    PM_PMC1_L2_HITS                             = 0b0000111u << 6,
    PM_PMC1_INSTRUCTIONS_EA_DELIVERED           = 0b0001000u << 6,
    PM_PMC1_INSTRUCTIONS_COMPLETED_MATCHES_IABR = 0b0001001u << 6,
    PM_PMC1_SLOW_L1_MISSES                      = 0b0001010u << 6,
    PM_PMC1_UNRESOLVED_BRANCHES                 = 0b0001011u << 6,
    PM_PMC1_UNRESOLVED_STALL_CYCLES             = 0b0001100u << 6,
    PM_PMC1_L1_SHARED_STORES                    = 0b0001110u << 6,
    PM_PMC1_L2_SHARED_INTERVENTIONS             = 0b0001111u << 6,
    PM_PMC1_CACHE_PARADOXES                     = 0b0010000u << 6,
    PM_PMC1_CIU_LOAD_REQUESTS                   = 0b0010100u << 6,
    PM_PMC1_BIU_ADDRESS_ONLY_REQUESTS           = 0b0010101u << 6,
    PM_PMC1_CIU_PARADOXES                       = 0b0010110u << 6,
    PM_PMC1_60XE_BUS_DATA_BEATS                 = 0b0010111u << 6,

    PM_PMC2_CURRENT                           = 0b000000u,
    PM_PMC2_CPU_CYCLES                        = 0b000001u,
    PM_PMC2_INSTRUCTIONS_COMPLETED            = 0b000010u,
    PM_PMC2_TBL_RISING_TRANSITIONS            = 0b000011u,
    PM_PMC2_INSTRUCTIONS_DISPATCHED           = 0b000100u,
    PM_PMC2_L1_ICACHE_MISSES                  = 0b000101u,
    PM_PMC2_ITLB_MISSES                       = 0b000110u,
    PM_PMC2_L2_INSTRUCTION_MISSES             = 0b000111u,
    PM_PMC2_PRED_BRANCHES_NOT_TAKEN           = 0b001000u,
    PM_PMC2_RESERVED_LOADS                    = 0b001010u,
    PM_PMC2_LOADS_AND_STORES                  = 0b001011u,
    PM_PMC2_CACHE_SNOOPS                      = 0b001100u,
    PM_PMC2_L1_TO_L2_CASTOUTS                 = 0b001101u,
    PM_PMC2_SYSTEM_UNIT_INSTRUCTIONS          = 0b001110u,
    PM_PMC2_L1_INSTRUCTION_MISS_CYCLES        = 0b001111u,
    PM_PMC2_FIRST_SPECULATIVE_BRANCH_RESOLVES = 0b010000u,
    PM_PMC2_L2_SHARED_STORES                  = 0b010001u,
    PM_PMC2_L1_SHARED_INTERVENTIONS           = 0b010010u,
    PM_PMC2_CIU_STORE_REQUESTS                = 0b010100u,
    PM_PMC2_SLOW_OUTSTANDING_BIU_TRANSACTIONS = 0b010101u,
    PM_PMC2_CIU_MODIFIED_INTERVENTIONS        = 0b010110u,
} PerfMonMMCR0Flags;

/**
 * Flags to write to (U)MMCR1 register.
 *
 * \sa OSSetPerformanceMonitor
 */
typedef enum PerfMonMMCR1Flags {
    PM_PMC3_CURRENT                            = 0b00000u << 27,
    PM_PMC3_CPU_CYCLES                         = 0b00001u << 27,
    PM_PMC3_INSTRUCTIONS_COMPLETED             = 0b00010u << 27,
    PM_PMC3_TBL_RISING_TRANSITIONS             = 0b00011u << 27,
    PM_PMC3_INSTRUCTIONS_DISPATCHED            = 0b00100u << 27,
    PM_PMC3_L1_DCACHE_MISSES                   = 0b00101u << 27,
    PM_PMC3_DTLB_MISSES                        = 0b00110u << 27,
    PM_PMC3_L2_DATA_MISSES                     = 0b00111u << 27,
    PM_PMC3_PRED_BRANCHES_TAKEN                = 0b01000u << 27,
    PM_PMC3_COND_STORES_COMPLETED              = 0b01010u << 27,
    PM_PMC3_FPU_INSTRUCTIONS_COMPLETED         = 0b01011u << 27,
    PM_PMC3_L2_CASTOUTS_BY_SNOOPS              = 0b01100u << 27,
    PM_PMC3_L2_CACHE_OPERATIONS                = 0b01101u << 27,
    PM_PMC3_L1_LOAD_MISS_CYCLES                = 0b01111u << 27,
    PM_PMC3_SECOND_SPECULATIVE_BRANCH_RESOLVES = 0b10000u << 27,
    PM_PMC3_BPU_STALL_LR_CR_CYCLES             = 0b10001u << 27,
    PM_PMC3_L1_MODIFIED_INTERVENTIONS          = 0b10010u << 27,
    PM_PMC3_ICBI_SNOOPS                        = 0b10011u << 27,
    PM_PMC3_CIU_ADDRESS_ONLY_REQUESTS          = 0b10100u << 27,
    PM_PMC3_BIU_LOAD_REQUESTS                  = 0b10101u << 27,
    PM_PMC3_CIU_SHARED_INTERVENTIONS           = 0b10110u << 27,

    PM_PMC4_CURRENT                           = 0b00000u << 22,
    PM_PMC4_CPU_CYCLES                        = 0b00001u << 22,
    PM_PMC4_INSTRUCTIONS_COMPLETED            = 0b00010u << 22,
    PM_PMC4_TBL_RISING_TRANSITIONS            = 0b00011u << 22,
    PM_PMC4_INSTRUCTIONS_DISPATCHED           = 0b00100u << 22,
    PM_PMC4_L2_CASTOUTS                       = 0b00101u << 22,
    PM_PMC4_DTLB_SEARCH_CYCLES                = 0b00110u << 22,
    PM_PMC4_BRANCHES_MISPREDICTED             = 0b01000u << 22,
    PM_PMC4_INTACT_COND_STORES_COMPLETED      = 0b01010u << 22,
    PM_PMC4_SYNC_INSTRUCTIONS_COMPLETED       = 0b01011u << 22,
    PM_PMC4_SNOOP_RETRIES                     = 0b01100u << 22,
    PM_PMC4_INTEGER_OPERATIONS                = 0b01101u << 22,
    PM_PMC4_BPU_STALL_TWO_BRANCHES_CYCLES     = 0b01110u << 22,
    PM_PMC4_L2_MODIFIED_INTERVENTIONS         = 0b10000u << 22,
    PM_PMC4_TLBIE_SNOOPS                      = 0b10001u << 22,
    PM_PMC4_L2_BANK_REFRESH_OVERFLOWS         = 0b10010u << 22,
    PM_PMC4_CIU_ARTRY_COUNT                   = 0b10100u << 22,
    PM_PMC4_BIU_STORE_REQUESTS                = 0b10101u << 22,
    PM_PMC4_CIU_TWO_CORE_SHARED_INTERVENTIONS = 0b10110u << 22,
} PerfMonMMCR1Flags;

/**
 * Write to performance monitor registers.
 *
 * Performance monitor registers can only be written by the kernel, this allows userspace
 * to write to them.
 *
 * \param arg_mask OR-ed values from `PerfMonArg`, indicating which of the following
 * arguments are to be written to registers.
 *
 * \param mmcr0 OR-ed values from `PerfMonMMCR0Flags` to write to register MMCR0.
 * \param mmcr1 OR-ed values from `PerfMonMMCR1Flags` to write to register MMCR1.
 * \param pmc1 Value to write to register PMC1.
 * \param pmc2 Value to write to register PMC2.
 * \param pmc3 Value to write to register PMC3.
 * \param pmc4 Value to write to register PMC4.
 */
void OSSetPerformanceMonitor(uint32_t arg_mask,
                             uint32_t mmcr0,
                             uint32_t mmcr1,
                             uint32_t pmc1,
                             uint32_t pmc2,
                             uint32_t pmc3,
                             uint32_t pmc4);

/**
 * Convenience function to read from UPMC1.
 */
static inline
uint32_t
__wut_read_upmc1()
{
    uint32_t result;
    asm("mfupmc1 %[result]"
        : [result] "=r"(result));
    return result;
}

/**
 * Convenience function to read from UPMC2.
 */
static inline
uint32_t
__wut_read_upmc2()
{
    uint32_t result;
    asm("mfupmc2 %[result]"
        : [result] "=r"(result));
    return result;
}

/**
 * Convenience function to read from UPMC3.
 */
static inline
uint32_t
__wut_read_upmc3()
{
    uint32_t result;
    asm("mfupmc3 %[result]"
        : [result] "=r"(result));
    return result;
}

/**
 * Convenience function to read from UPMC4.
 */
static inline
uint32_t
__wut_read_upmc4()
{
    uint32_t result;
    asm("mfupmc4 %[result]"
        : [result] "=r"(result));
    return result;
}

#ifdef __cplusplus
}
#endif

/** @} */
