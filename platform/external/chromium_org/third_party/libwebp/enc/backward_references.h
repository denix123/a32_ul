// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_ENC_BACKWARD_REFERENCES_H_
#define WEBP_ENC_BACKWARD_REFERENCES_H_

#include <assert.h>
#include <stdlib.h>
#include "../webp/types.h"
#include "../webp/format_constants.h"

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_COLOR_CACHE_BITS 9

#define PIX_OR_COPY_CODES_MAX \
    (NUM_LITERAL_CODES + NUM_LENGTH_CODES + (1 << MAX_COLOR_CACHE_BITS))


enum Mode {
  kLiteral,
  kCacheIdx,
  kCopy,
  kNone
};

typedef struct {
  
  uint8_t mode;
  uint16_t len;
  uint32_t argb_or_distance;
} PixOrCopy;

static WEBP_INLINE PixOrCopy PixOrCopyCreateCopy(uint32_t distance,
                                                 uint16_t len) {
  PixOrCopy retval;
  retval.mode = kCopy;
  retval.argb_or_distance = distance;
  retval.len = len;
  return retval;
}

static WEBP_INLINE PixOrCopy PixOrCopyCreateCacheIdx(int idx) {
  PixOrCopy retval;
  assert(idx >= 0);
  assert(idx < (1 << MAX_COLOR_CACHE_BITS));
  retval.mode = kCacheIdx;
  retval.argb_or_distance = idx;
  retval.len = 1;
  return retval;
}

static WEBP_INLINE PixOrCopy PixOrCopyCreateLiteral(uint32_t argb) {
  PixOrCopy retval;
  retval.mode = kLiteral;
  retval.argb_or_distance = argb;
  retval.len = 1;
  return retval;
}

static WEBP_INLINE int PixOrCopyIsLiteral(const PixOrCopy* const p) {
  return (p->mode == kLiteral);
}

static WEBP_INLINE int PixOrCopyIsCacheIdx(const PixOrCopy* const p) {
  return (p->mode == kCacheIdx);
}

static WEBP_INLINE int PixOrCopyIsCopy(const PixOrCopy* const p) {
  return (p->mode == kCopy);
}

static WEBP_INLINE uint32_t PixOrCopyLiteral(const PixOrCopy* const p,
                                             int component) {
  assert(p->mode == kLiteral);
  return (p->argb_or_distance >> (component * 8)) & 0xff;
}

static WEBP_INLINE uint32_t PixOrCopyLength(const PixOrCopy* const p) {
  return p->len;
}

static WEBP_INLINE uint32_t PixOrCopyArgb(const PixOrCopy* const p) {
  assert(p->mode == kLiteral);
  return p->argb_or_distance;
}

static WEBP_INLINE uint32_t PixOrCopyCacheIdx(const PixOrCopy* const p) {
  assert(p->mode == kCacheIdx);
  assert(p->argb_or_distance < (1U << MAX_COLOR_CACHE_BITS));
  return p->argb_or_distance;
}

static WEBP_INLINE uint32_t PixOrCopyDistance(const PixOrCopy* const p) {
  assert(p->mode == kCopy);
  return p->argb_or_distance;
}


#define HASH_BITS 18
#define HASH_SIZE (1 << HASH_BITS)

typedef struct VP8LHashChain VP8LHashChain;
struct VP8LHashChain {
  
  int32_t hash_to_first_index_[HASH_SIZE];
  
  
  int32_t* chain_;
  
  
  int size_;
};

int VP8LHashChainInit(VP8LHashChain* const p, int size);
void VP8LHashChainClear(VP8LHashChain* const p);  


#define MAX_REFS_BLOCK_PER_IMAGE 16

typedef struct PixOrCopyBlock PixOrCopyBlock;   
typedef struct VP8LBackwardRefs VP8LBackwardRefs;

struct VP8LBackwardRefs {
  int block_size_;               
  int error_;                    
  PixOrCopyBlock* refs_;         
  PixOrCopyBlock** tail_;        
  PixOrCopyBlock* free_blocks_;  
  PixOrCopyBlock* last_block_;   
};

void VP8LBackwardRefsInit(VP8LBackwardRefs* const refs, int block_size);
void VP8LBackwardRefsClear(VP8LBackwardRefs* const refs);
int VP8LBackwardRefsCopy(const VP8LBackwardRefs* const src,
                         VP8LBackwardRefs* const dst);

typedef struct {
  
  PixOrCopy* cur_pos;           
  
  PixOrCopyBlock* cur_block_;   
  const PixOrCopy* last_pos_;   
} VP8LRefsCursor;

VP8LRefsCursor VP8LRefsCursorInit(const VP8LBackwardRefs* const refs);
static WEBP_INLINE int VP8LRefsCursorOk(const VP8LRefsCursor* const c) {
  return (c->cur_pos != NULL);
}
void VP8LRefsCursorNextBlock(VP8LRefsCursor* const c);
static WEBP_INLINE void VP8LRefsCursorNext(VP8LRefsCursor* const c) {
  assert(c != NULL);
  assert(VP8LRefsCursorOk(c));
  if (++c->cur_pos == c->last_pos_) VP8LRefsCursorNextBlock(c);
}


VP8LBackwardRefs* VP8LGetBackwardReferences(
    int width, int height, const uint32_t* const argb, int quality,
    int cache_bits, int use_2d_locality, VP8LHashChain* const hash_chain,
    VP8LBackwardRefs refs[2]);

int VP8LCalculateEstimateForCacheSize(const uint32_t* const argb,
                                      int xsize, int ysize, int quality,
                                      VP8LHashChain* const hash_chain,
                                      VP8LBackwardRefs* const ref,
                                      int* const best_cache_bits);

#ifdef __cplusplus
}
#endif

#endif  
