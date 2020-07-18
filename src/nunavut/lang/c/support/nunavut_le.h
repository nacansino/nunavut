/*
 *
 * UAVCAN little-endian serialization support routines.                                                                     +-+ +-+
 *                                                                                                            | | | |
 *                                                                                                            \  -  /
 *  This software is distributed under the terms of the MIT License.                                            ---
 *                                                                                                               o
 * +------------------------------------------------------------------------------------------------------------------+
 */
#ifndef NUNAVUT_SUPPORT_NUNAVUT_LE_H_INCLUDED
#define NUNAVUT_SUPPORT_NUNAVUT_LE_H_INCLUDED

// Guard against including both LE and non-LE helper functions.
#ifdef NUNAVUT_SUPPORT_NUNAVUT_H_INCLUDED
#    error "Must not include both LE and non-LE Nunavut support headers!"
#endif

#include "nunavut_common.h"

#ifdef __cplusplus
extern "C" {
#endif

// --------------------------------------------- PUBLIC API - INTEGER ---------------------------------------------

static inline void nunavutSetUxx(uint8_t* const buf, const NunavutUnsignedBitLength off_bit, const uint64_t value,
                                 const uint8_t len_bit)
{
    _Static_assert(WIDTH64 == (sizeof(uint64_t) * BYTE_WIDTH), "Unexpected size of uint64_t");
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength saturated_len_bit = chooseMin(len_bit, WIDTH64);
    nunavutCopyBits(saturated_len_bit, 0U, off_bit, (const uint8_t*) &value, buf);
}

static inline uint16_t nunavutGetU16(const uint8_t* const buf, const NunavutByteLength buf_size,
                                     const NunavutUnsignedBitLength off_bit, const uint8_t len_bit)
{
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength copy_size = getBitCopySize(buf_size, off_bit, len_bit, WIDTH16);
    NUNAVUT_ASSERT(copy_size <= (sizeof(uint16_t) * BYTE_WIDTH));
    uint16_t val = 0U;
    nunavutCopyBits(copy_size, off_bit, 0U, buf, (uint8_t*) &val);
    return val;
}

static inline uint32_t nunavutGetU32(const uint8_t* const buf, const NunavutByteLength buf_size,
                                     const NunavutUnsignedBitLength off_bit, const uint8_t len_bit)
{
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength copy_size = getBitCopySize(buf_size, off_bit, len_bit, WIDTH32);
    NUNAVUT_ASSERT(copy_size <= (sizeof(uint32_t) * BYTE_WIDTH));
    uint32_t val = 0U;
    nunavutCopyBits(copy_size, off_bit, 0U, buf, (uint8_t*) &val);
    return val;
}

static inline uint64_t nunavutGetU64(const uint8_t* const buf, const NunavutByteLength buf_size,
                                     const NunavutUnsignedBitLength off_bit, const uint8_t len_bit)
{
    NUNAVUT_ASSERT(buf != NULL);
    const NunavutUnsignedBitLength copy_size = getBitCopySize(buf_size, off_bit, len_bit, WIDTH64);
    NUNAVUT_ASSERT(copy_size <= (sizeof(uint64_t) * BYTE_WIDTH));
    uint64_t val = 0U;
    nunavutCopyBits(copy_size, off_bit, 0U, buf, (uint8_t*) &val);
    return val;
}

#ifdef __cplusplus
}
#endif

#endif /* NUNAVUT_SUPPORT_NUNAVUT_LE_H_INCLUDED */
