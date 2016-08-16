#ifndef QEMU_RANGE_H
#define QEMU_RANGE_H

#include <inttypes.h>
#include <qemu/typedefs.h>


struct Range {
    uint64_t begin; 
    uint64_t end;   
};

static inline void range_extend(Range *range, Range *extend_by)
{
    if (!extend_by->begin && !extend_by->end) {
        return;
    }
    if (!range->begin && !range->end) {
        *range = *extend_by;
        return;
    }
    if (range->begin > extend_by->begin) {
        range->begin = extend_by->begin;
    }
    
    if (range->end - 1 < extend_by->end - 1) {
        range->end = extend_by->end;
    }
}

static inline uint64_t range_get_last(uint64_t offset, uint64_t len)
{
    return offset + len - 1;
}

static inline int range_covers_byte(uint64_t offset, uint64_t len,
                                    uint64_t byte)
{
    return offset <= byte && byte <= range_get_last(offset, len);
}

static inline int ranges_overlap(uint64_t first1, uint64_t len1,
                                 uint64_t first2, uint64_t len2)
{
    uint64_t last1 = range_get_last(first1, len1);
    uint64_t last2 = range_get_last(first2, len2);

    return !(last2 < first1 || last1 < first2);
}

#endif
