// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TOOLS_ANDROID_HEAP_PROFILER_HEAP_PROFILER_H_
#define TOOLS_ANDROID_HEAP_PROFILER_HEAP_PROFILER_H_

#include <stdint.h>
#include "third_party/bsdtrees/tree.h"

#define HEAP_PROFILER_MAGIC_MARKER 0x42beef42L
#define HEAP_PROFILER_MAX_DEPTH 12

#define HEAP_PROFILER_FLAGS_MALLOC 1

#define HEAP_PROFILER_FLAGS_MMAP 2  

#define HEAP_PROFILER_FLAGS_MMAP_FILE 4

#define HEAP_PROFILER_FLAGS_IN_ZYGOTE 8

#ifdef __cplusplus
extern "C" {
#endif

typedef struct StacktraceEntry {
  uintptr_t frames[HEAP_PROFILER_MAX_DEPTH];  
  uint32_t hash;  

  
  
  size_t alloc_bytes;

  
  
  
  struct StacktraceEntry* next;
} StacktraceEntry;

typedef struct Alloc {
  RB_ENTRY(Alloc) rb_node;  
  uintptr_t start;
  uintptr_t end;
  uint32_t flags;       
  StacktraceEntry* st;  
  struct Alloc* next_free;
} Alloc;

typedef struct {
  uint32_t magic_start;       
  uint32_t num_allocs;        
  uint32_t max_allocs;        
  uint32_t num_stack_traces;  
  uint32_t max_stack_traces;  
  size_t total_alloc_bytes;   
  Alloc* allocs;              
  StacktraceEntry* stack_traces;  
} HeapStats;

void heap_profiler_init(HeapStats* heap_stats);

void heap_profiler_alloc(void* addr,
                         size_t size,
                         uintptr_t* frames,
                         uint32_t depth,
                         uint32_t flags);

void heap_profiler_free(void* addr, size_t size, uint32_t* old_flags);

void heap_profiler_cleanup(void);

#ifdef __cplusplus
}
#endif

#endif  
