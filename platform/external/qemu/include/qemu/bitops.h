/*
 * Bitops Module
 *
 * Copyright (C) 2010 Corentin Chary <corentin.chary@gmail.com>
 *
 * Mostly inspired by (stolen from) linux/bitmap.h and linux/bitops.h
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 */

#ifndef BITOPS_H
#define BITOPS_H

#include "qemu-common.h"
#include "host-utils.h"

#define BITS_PER_BYTE           CHAR_BIT
#define BITS_PER_LONG           (sizeof (unsigned long) * BITS_PER_BYTE)

#define BIT(nr)			(1UL << (nr))
#define BIT_MASK(nr)		(1UL << ((nr) % BITS_PER_LONG))
#define BIT_WORD(nr)		((nr) / BITS_PER_LONG)
#define BITS_TO_LONGS(nr)	DIV_ROUND_UP(nr, BITS_PER_BYTE * sizeof(long))

static inline void set_bit(int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);

	*p  |= mask;
}

static inline void clear_bit(int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);

	*p &= ~mask;
}

static inline void change_bit(int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);

	*p ^= mask;
}

static inline int test_and_set_bit(int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);
	unsigned long old = *p;

	*p = old | mask;
	return (old & mask) != 0;
}

static inline int test_and_clear_bit(int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);
	unsigned long old = *p;

	*p = old & ~mask;
	return (old & mask) != 0;
}

static inline int test_and_change_bit(int nr, unsigned long *addr)
{
	unsigned long mask = BIT_MASK(nr);
        unsigned long *p = addr + BIT_WORD(nr);
	unsigned long old = *p;

	*p = old ^ mask;
	return (old & mask) != 0;
}

static inline int test_bit(int nr, const unsigned long *addr)
{
	return 1UL & (addr[BIT_WORD(nr)] >> (nr & (BITS_PER_LONG-1)));
}

unsigned long find_last_bit(const unsigned long *addr,
                            unsigned long size);

unsigned long find_next_bit(const unsigned long *addr,
				   unsigned long size, unsigned long offset);


unsigned long find_next_zero_bit(const unsigned long *addr,
                                 unsigned long size,
                                 unsigned long offset);

static inline unsigned long find_first_bit(const unsigned long *addr,
                                           unsigned long size)
{
    return find_next_bit(addr, size, 0);
}

static inline unsigned long find_first_zero_bit(const unsigned long *addr,
                                                unsigned long size)
{
    return find_next_zero_bit(addr, size, 0);
}

static inline unsigned long hweight_long(unsigned long w)
{
    unsigned long count;

    for (count = 0; w; w >>= 1) {
        count += w & 1;
    }
    return count;
}

static inline uint8_t rol8(uint8_t word, unsigned int shift)
{
    return (word << shift) | (word >> (8 - shift));
}

static inline uint8_t ror8(uint8_t word, unsigned int shift)
{
    return (word >> shift) | (word << (8 - shift));
}

static inline uint16_t rol16(uint16_t word, unsigned int shift)
{
    return (word << shift) | (word >> (16 - shift));
}

static inline uint16_t ror16(uint16_t word, unsigned int shift)
{
    return (word >> shift) | (word << (16 - shift));
}

static inline uint32_t rol32(uint32_t word, unsigned int shift)
{
    return (word << shift) | (word >> (32 - shift));
}

static inline uint32_t ror32(uint32_t word, unsigned int shift)
{
    return (word >> shift) | (word << (32 - shift));
}

static inline uint64_t rol64(uint64_t word, unsigned int shift)
{
    return (word << shift) | (word >> (64 - shift));
}

static inline uint64_t ror64(uint64_t word, unsigned int shift)
{
    return (word >> shift) | (word << (64 - shift));
}

static inline uint32_t extract32(uint32_t value, int start, int length)
{
    assert(start >= 0 && length > 0 && length <= 32 - start);
    return (value >> start) & (~0U >> (32 - length));
}

static inline uint64_t extract64(uint64_t value, int start, int length)
{
    assert(start >= 0 && length > 0 && length <= 64 - start);
    return (value >> start) & (~0ULL >> (64 - length));
}

static inline int32_t sextract32(uint32_t value, int start, int length)
{
    assert(start >= 0 && length > 0 && length <= 32 - start);
    return ((int32_t)(value << (32 - length - start))) >> (32 - length);
}

static inline uint64_t sextract64(uint64_t value, int start, int length)
{
    assert(start >= 0 && length > 0 && length <= 64 - start);
    return ((int64_t)(value << (64 - length - start))) >> (64 - length);
}

static inline uint32_t deposit32(uint32_t value, int start, int length,
                                 uint32_t fieldval)
{
    uint32_t mask;
    assert(start >= 0 && length > 0 && length <= 32 - start);
    mask = (~0U >> (32 - length)) << start;
    return (value & ~mask) | ((fieldval << start) & mask);
}

static inline uint64_t deposit64(uint64_t value, int start, int length,
                                 uint64_t fieldval)
{
    uint64_t mask;
    assert(start >= 0 && length > 0 && length <= 64 - start);
    mask = (~0ULL >> (64 - length)) << start;
    return (value & ~mask) | ((fieldval << start) & mask);
}

#endif
