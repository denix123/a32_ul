/*
 * Bitmap Module
 *
 * Copyright (C) 2010 Corentin Chary <corentin.chary@gmail.com>
 *
 * Mostly inspired by (stolen from) linux/bitmap.h and linux/bitops.h
 *
 * This work is licensed under the terms of the GNU LGPL, version 2.1 or later.
 * See the COPYING.LIB file in the top-level directory.
 */

#ifndef BITMAP_H
#define BITMAP_H

#include "qemu-common.h"
#include "qemu/bitops.h"



#define BITMAP_LAST_WORD_MASK(nbits)                                    \
    (                                                                   \
        ((nbits) % BITS_PER_LONG) ?                                     \
        (1UL<<((nbits) % BITS_PER_LONG))-1 : ~0UL                       \
        )

#define DECLARE_BITMAP(name,bits)                  \
	unsigned long name[BITS_TO_LONGS(bits)]

#define small_nbits(nbits)                      \
	((nbits) <= BITS_PER_LONG)

int slow_bitmap_empty(const unsigned long *bitmap, int bits);
int slow_bitmap_full(const unsigned long *bitmap, int bits);
int slow_bitmap_equal(const unsigned long *bitmap1,
                   const unsigned long *bitmap2, int bits);
void slow_bitmap_complement(unsigned long *dst, const unsigned long *src,
                         int bits);
void slow_bitmap_shift_right(unsigned long *dst,
                          const unsigned long *src, int shift, int bits);
void slow_bitmap_shift_left(unsigned long *dst,
                         const unsigned long *src, int shift, int bits);
int slow_bitmap_and(unsigned long *dst, const unsigned long *bitmap1,
                 const unsigned long *bitmap2, int bits);
void slow_bitmap_or(unsigned long *dst, const unsigned long *bitmap1,
                 const unsigned long *bitmap2, int bits);
void slow_bitmap_xor(unsigned long *dst, const unsigned long *bitmap1,
                  const unsigned long *bitmap2, int bits);
int slow_bitmap_andnot(unsigned long *dst, const unsigned long *bitmap1,
                    const unsigned long *bitmap2, int bits);
int slow_bitmap_intersects(const unsigned long *bitmap1,
			const unsigned long *bitmap2, int bits);

static inline unsigned long *bitmap_new(int nbits)
{
    int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
    return g_malloc0(len);
}

static inline void bitmap_zero(unsigned long *dst, int nbits)
{
    if (small_nbits(nbits)) {
        *dst = 0UL;
    } else {
        int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
        memset(dst, 0, len);
    }
}

static inline void bitmap_fill(unsigned long *dst, int nbits)
{
    size_t nlongs = BITS_TO_LONGS(nbits);
    if (!small_nbits(nbits)) {
        int len = (nlongs - 1) * sizeof(unsigned long);
        memset(dst, 0xff,  len);
    }
    dst[nlongs - 1] = BITMAP_LAST_WORD_MASK(nbits);
}

static inline void bitmap_copy(unsigned long *dst, const unsigned long *src,
                               int nbits)
{
    if (small_nbits(nbits)) {
        *dst = *src;
    } else {
        int len = BITS_TO_LONGS(nbits) * sizeof(unsigned long);
        memcpy(dst, src, len);
    }
}

static inline int bitmap_and(unsigned long *dst, const unsigned long *src1,
                             const unsigned long *src2, int nbits)
{
    if (small_nbits(nbits)) {
        return (*dst = *src1 & *src2) != 0;
    }
    return slow_bitmap_and(dst, src1, src2, nbits);
}

static inline void bitmap_or(unsigned long *dst, const unsigned long *src1,
			const unsigned long *src2, int nbits)
{
    if (small_nbits(nbits)) {
        *dst = *src1 | *src2;
    } else {
        slow_bitmap_or(dst, src1, src2, nbits);
    }
}

static inline void bitmap_xor(unsigned long *dst, const unsigned long *src1,
			const unsigned long *src2, int nbits)
{
    if (small_nbits(nbits)) {
        *dst = *src1 ^ *src2;
    } else {
        slow_bitmap_xor(dst, src1, src2, nbits);
    }
}

static inline int bitmap_andnot(unsigned long *dst, const unsigned long *src1,
			const unsigned long *src2, int nbits)
{
    if (small_nbits(nbits)) {
        return (*dst = *src1 & ~(*src2)) != 0;
    }
    return slow_bitmap_andnot(dst, src1, src2, nbits);
}

static inline void bitmap_complement(unsigned long *dst, const unsigned long *src,
			int nbits)
{
    if (small_nbits(nbits)) {
        *dst = ~(*src) & BITMAP_LAST_WORD_MASK(nbits);
    } else {
        slow_bitmap_complement(dst, src, nbits);
    }
}

static inline int bitmap_equal(const unsigned long *src1,
			const unsigned long *src2, int nbits)
{
    if (small_nbits(nbits)) {
        return ! ((*src1 ^ *src2) & BITMAP_LAST_WORD_MASK(nbits));
    } else {
        return slow_bitmap_equal(src1, src2, nbits);
    }
}

static inline int bitmap_empty(const unsigned long *src, int nbits)
{
    if (small_nbits(nbits)) {
        return ! (*src & BITMAP_LAST_WORD_MASK(nbits));
    } else {
        return slow_bitmap_empty(src, nbits);
    }
}

static inline int bitmap_full(const unsigned long *src, int nbits)
{
    if (small_nbits(nbits)) {
        return ! (~(*src) & BITMAP_LAST_WORD_MASK(nbits));
    } else {
        return slow_bitmap_full(src, nbits);
    }
}

static inline int bitmap_intersects(const unsigned long *src1,
			const unsigned long *src2, int nbits)
{
    if (small_nbits(nbits)) {
        return ((*src1 & *src2) & BITMAP_LAST_WORD_MASK(nbits)) != 0;
    } else {
        return slow_bitmap_intersects(src1, src2, nbits);
    }
}

void bitmap_set(unsigned long *map, int i, int len);
void bitmap_clear(unsigned long *map, int start, int nr);
unsigned long bitmap_find_next_zero_area(unsigned long *map,
					 unsigned long size,
					 unsigned long start,
					 unsigned int nr,
					 unsigned long align_mask);

#endif 
