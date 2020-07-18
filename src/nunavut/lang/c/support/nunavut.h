/*
 *
 * UAVCAN generic serialization support routines.                                                                     +-+ +-+
 *                                                                                                            | | | |
 *                                                                                                            \  -  /
 *  This software is distributed under the terms of the MIT License.                                            ---
 *                                                                                                               o
 * +------------------------------------------------------------------------------------------------------------------+
 */
#ifndef NUNAVUT_SUPPORT_NUNAVUT_H_INCLUDED
#define NUNAVUT_SUPPORT_NUNAVUT_H_INCLUDED

#include "nunavut_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// Guard against including both LE and non-LE helper functions.
#ifdef NUNAVUT_SUPPORT_NUNAVUT_LE_H_INCLUDED
#    error "Must not include both LE and non-LE Nunavut support headers!"
#endif

// --------------------------------------------- PUBLIC API - INTEGER ---------------------------------------------

static inline void nunavutSetUxx(uint8_t* const buf, const NunavutUnsignedBitLength off_bit, const uint64_t value,
                                 const uint8_t len_bit)
{
    _Static_assert(WIDTH64 == (sizeof(uint64_t) * BYTE_WIDTH), "Unexpected size of uint64_t");
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength saturated_len_bit = chooseMin(len_bit, WIDTH64);
    const uint8_t tmp[sizeof(uint64_t)] = {
        (uint8_t)((value >> 0U) & BYTE_MAX),   // Suppress warnings about the magic numbers. Their purpose is clear.
        (uint8_t)((value >> 8U) & BYTE_MAX),   // NOLINT NOSONAR
        (uint8_t)((value >> 16U) & BYTE_MAX),  // NOLINT NOSONAR
        (uint8_t)((value >> 24U) & BYTE_MAX),  // NOLINT NOSONAR
        (uint8_t)((value >> 32U) & BYTE_MAX),  // NOLINT NOSONAR
        (uint8_t)((value >> 40U) & BYTE_MAX),  // NOLINT NOSONAR
        (uint8_t)((value >> 48U) & BYTE_MAX),  // NOLINT NOSONAR
        (uint8_t)((value >> 56U) & BYTE_MAX),  // NOLINT NOSONAR
    };
    nunavutCopyBits(saturated_len_bit, 0U, off_bit, &tmp[0], buf);
}

static inline uint16_t nunavutGetU16(const uint8_t* const buf, const NunavutByteLength buf_size,
                                     const NunavutUnsignedBitLength off_bit, const uint8_t len_bit)
{
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength copy_size = getBitCopySize(buf_size, off_bit, len_bit, WIDTH16);
    NUNAVUT_ASSERT(copy_size <= (sizeof(uint16_t) * BYTE_WIDTH));
    uint8_t tmp[sizeof(uint16_t)] = {0};
    nunavutCopyBits(copy_size, off_bit, 0U, buf, &tmp[0]);
    return (uint16_t)(tmp[0] | (uint16_t)(((uint16_t) tmp[1]) << BYTE_WIDTH));
}

static inline uint32_t nunavutGetU32(const uint8_t* const buf, const NunavutByteLength buf_size,
                                     const NunavutUnsignedBitLength off_bit, const uint8_t len_bit)
{
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength copy_size = getBitCopySize(buf_size, off_bit, len_bit, WIDTH32);
    NUNAVUT_ASSERT(copy_size <= (sizeof(uint32_t) * BYTE_WIDTH));
    uint8_t tmp[sizeof(uint32_t)] = {0};
    nunavutCopyBits(copy_size, off_bit, 0U, buf, &tmp[0]);
    return (uint32_t)(tmp[0] |                      // Suppress warnings about the magic numbers.
                      ((uint32_t) tmp[1] << 8U) |   // NOLINT NOSONAR
                      ((uint32_t) tmp[2] << 16U) |  // NOLINT NOSONAR
                      ((uint32_t) tmp[3] << 24U));  // NOLINT NOSONAR
}

static inline uint64_t nunavutGetU64(const uint8_t* const buf, const NunavutByteLength buf_size,
                                     const NunavutUnsignedBitLength off_bit, const uint8_t len_bit)
{
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength copy_size = getBitCopySize(buf_size, off_bit, len_bit, WIDTH64);
    NUNAVUT_ASSERT(copy_size <= (sizeof(uint64_t) * BYTE_WIDTH));
    uint8_t tmp[sizeof(uint64_t)] = {0};
    nunavutCopyBits(copy_size, off_bit, 0U, buf, &tmp[0]);
    return (uint64_t)(tmp[0] |                      // Suppress warnings about the magic numbers.
                      ((uint64_t) tmp[1] << 8U) |   // NOLINT NOSONAR
                      ((uint64_t) tmp[2] << 16U) |  // NOLINT NOSONAR
                      ((uint64_t) tmp[3] << 24U) |  // NOLINT NOSONAR
                      ((uint64_t) tmp[4] << 32U) |  // NOLINT NOSONAR
                      ((uint64_t) tmp[5] << 40U) |  // NOLINT NOSONAR
                      ((uint64_t) tmp[6] << 48U) |  // NOLINT NOSONAR
                      ((uint64_t) tmp[7] << 56U));  // NOLINT NOSONAR
}

#ifdef __cplusplus
} /* end extern "C" */
#endif

#endif  /* NUNAVUT_SUPPORT_SERIALIZATION_H_INCLUDED */
