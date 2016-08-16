// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <assert.h>
#include <string.h>

#if defined(__linux__) || defined(__ANDROID__)
#include <pthread.h>
#define DEFINE_MUTEX(x) pthread_mutex_t x = PTHREAD_MUTEX_INITIALIZER
#define LOCK_MUTEX(x) pthread_mutex_lock(&x)
#define UNLOCK_MUTEX(x) pthread_mutex_unlock(&x)
#else
#error OS not supported.
#endif

#include "tools/android/heap_profiler/heap_profiler.h"


static DEFINE_MUTEX(lock);

static HeapStats* stats;

#define ST_ENTRIES_MAX (64 * 1024)
#define ST_HASHTABLE_BUCKETS (64 * 1024) 

static StacktraceEntry stack_traces[ST_ENTRIES_MAX];
static StacktraceEntry* stack_traces_freelist;
static StacktraceEntry* stack_traces_ht[ST_HASHTABLE_BUCKETS];

static StacktraceEntry* record_stacktrace(uintptr_t* frames, uint32_t depth) {
  if (depth == 0)
    return NULL;

  if (depth > HEAP_PROFILER_MAX_DEPTH)
    depth = HEAP_PROFILER_MAX_DEPTH;

  uint32_t i;
  uintptr_t hash = 0;
  for (i = 0; i < depth; ++i)
    hash = (hash << 1) ^ (frames[i]);
  const uint32_t slot = hash & (ST_HASHTABLE_BUCKETS - 1);
  StacktraceEntry* st = stack_traces_ht[slot];

  
  const size_t frames_length = depth * sizeof(uintptr_t);
  while (st != NULL && st->hash != hash &&
         memcmp(frames, st->frames, frames_length) != 0) {
    st = st->next;
  }

  
  
  if (st == NULL) {
    
    if (stack_traces_freelist != NULL) {
      st = stack_traces_freelist;
      stack_traces_freelist = stack_traces_freelist->next;
    } else if (stats->max_stack_traces < ST_ENTRIES_MAX) {
      st = &stack_traces[stats->max_stack_traces];
      ++stats->max_stack_traces;
    } else {
      return NULL;
    }

    memset(st, 0, sizeof(*st));
    memcpy(st->frames, frames, frames_length);
    st->hash = hash;
    st->next = stack_traces_ht[slot];
    stack_traces_ht[slot] = st;
    ++stats->num_stack_traces;
  }

  return st;
}

static void free_stacktrace(StacktraceEntry* st) {
  assert(st->alloc_bytes == 0);
  const uint32_t slot = st->hash & (ST_HASHTABLE_BUCKETS - 1);

  
  
  StacktraceEntry** prev = &stack_traces_ht[slot];
  while (*prev != st)
    prev = &((*prev)->next);

  
  assert(*prev == st);
  *prev = st->next;

  
  st->next = stack_traces_freelist;
  stack_traces_freelist = st;
  --stats->num_stack_traces;
}

#define ALLOCS_ENTRIES_MAX (256 * 1024)

static Alloc allocs[ALLOCS_ENTRIES_MAX];
static Alloc* allocs_freelist;
static RB_HEAD(HeapEntriesTree, Alloc) allocs_tree =
    RB_INITIALIZER(&allocs_tree);

static int allocs_tree_cmp(Alloc *alloc_1, Alloc *alloc_2) {
  if (alloc_1->start < alloc_2->start)
    return -1;
  if (alloc_1->start > alloc_2->start)
    return 1;
  return 0;
}

RB_PROTOTYPE(HeapEntriesTree, Alloc, rb_node, allocs_tree_cmp);
RB_GENERATE(HeapEntriesTree, Alloc, rb_node, allocs_tree_cmp);

static Alloc* insert_alloc(
    uintptr_t start, uintptr_t end, StacktraceEntry* st, uint32_t flags) {
  Alloc* alloc = NULL;

  
  if (allocs_freelist != NULL) {
    alloc = allocs_freelist;
    allocs_freelist = alloc->next_free;
  } else if (stats->max_allocs < ALLOCS_ENTRIES_MAX) {
    alloc = &allocs[stats->max_allocs];
    ++stats->max_allocs;
  } else {
    return NULL;  
  }

  alloc->start = start;
  alloc->end = end;
  alloc->st = st;
  alloc->flags = flags;
  alloc->next_free = NULL;
  RB_INSERT(HeapEntriesTree, &allocs_tree, alloc);
  ++stats->num_allocs;
  return alloc;
}

static uint32_t delete_allocs_in_range(void* addr, size_t size) {
  uintptr_t del_start = (uintptr_t) addr;
  uintptr_t del_end = del_start + size - 1;
  uint32_t flags = 0;

  Alloc* alloc = NULL;
  Alloc* next_alloc = RB_ROOT(&allocs_tree);

  
  
  
  
  
  
  
  
  while (next_alloc != NULL) {
    alloc = next_alloc;
    if (alloc->start > del_start) {
      next_alloc = RB_LEFT(alloc, rb_node);
    } else if (alloc->end < del_start) {
      next_alloc = RB_RIGHT(alloc, rb_node);
    } else {  
      break;
    }
  }

  
  
  next_alloc = alloc;
  while (next_alloc != NULL) {
    alloc = next_alloc;
    next_alloc = RB_NEXT(HeapEntriesTree, &allocs_tree, alloc);

    if (size != 0) {
      
      if (alloc->start > del_end)
        break;

      
      if (alloc->end < del_start)
        continue;
    } else {
      
      
      if (alloc->start > del_start)
        break;
      if (alloc->start < del_start)
        continue;
      del_end = alloc->end;
    }

    
    
    assert(!(alloc->start > del_end || alloc->end < del_start));

    StacktraceEntry* st = alloc->st;
    flags |= alloc->flags;
    uintptr_t freed_bytes = 0;  

    if (del_start <= alloc->start) {
      if (del_end >= alloc->end) {
        
        
        
        
        
        
        freed_bytes = alloc->end - alloc->start + 1;
        RB_REMOVE(HeapEntriesTree, &allocs_tree, alloc);

        
        alloc->start = alloc->end = 0;
        alloc->st = NULL;

        
        alloc->next_free = allocs_freelist;
        allocs_freelist = alloc;
        --stats->num_allocs;
      } else {
        
        
        
        
        freed_bytes = del_end - alloc->start + 1;
        alloc->start = del_end + 1;
        
        
      }
    } else {
      if (del_end >= alloc->end) {
        
        
        
        
        
        freed_bytes = alloc->end - del_start + 1;
        alloc->end = del_start - 1;
      } else {
        
        
        
        
        freed_bytes = del_end - del_start + 1;
        const uintptr_t old_end = alloc->end;
        alloc->end = del_start - 1;

        
        if (insert_alloc(del_end + 1, old_end, st, alloc->flags) == NULL)
          freed_bytes += (old_end - del_end);
      }
    }
    
    
    assert(st->alloc_bytes >= freed_bytes);
    st->alloc_bytes -= freed_bytes;
    if (st->alloc_bytes == 0)
      free_stacktrace(st);
    stats->total_alloc_bytes -= freed_bytes;
  }
  return flags;
}

void heap_profiler_free(void* addr, size_t size, uint32_t* old_flags) {
  assert(size == 0 || ((uintptr_t) addr + (size - 1)) >= (uintptr_t) addr);

  LOCK_MUTEX(lock);
  uint32_t flags = delete_allocs_in_range(addr, size);
  UNLOCK_MUTEX(lock);

  if (old_flags != NULL)
    *old_flags = flags;
}

void heap_profiler_alloc(void* addr, size_t size, uintptr_t* frames,
                         uint32_t depth, uint32_t flags) {
  if (depth > HEAP_PROFILER_MAX_DEPTH)
    depth = HEAP_PROFILER_MAX_DEPTH;

  if (size == 0)  
    return;

  const uintptr_t start = (uintptr_t) addr;
  const uintptr_t end = start + (size - 1);
  assert(start <= end);

  LOCK_MUTEX(lock);

  delete_allocs_in_range(addr, size);

  StacktraceEntry* st = record_stacktrace(frames, depth);
  if (st != NULL) {
    Alloc* alloc = insert_alloc(start, end, st, flags);
    if (alloc != NULL) {
      st->alloc_bytes += size;
      stats->total_alloc_bytes += size;
    }
  }

  UNLOCK_MUTEX(lock);
}

void heap_profiler_init(HeapStats* heap_stats) {
  LOCK_MUTEX(lock);

  assert(stats == NULL);
  stats = heap_stats;
  memset(stats, 0, sizeof(HeapStats));
  stats->magic_start = HEAP_PROFILER_MAGIC_MARKER;
  stats->allocs = &allocs[0];
  stats->stack_traces = &stack_traces[0];

  UNLOCK_MUTEX(lock);
}

void heap_profiler_cleanup(void) {
  LOCK_MUTEX(lock);

  assert(stats != NULL);
  memset(stack_traces, 0, sizeof(StacktraceEntry) * stats->max_stack_traces);
  memset(stack_traces_ht, 0, sizeof(stack_traces_ht));
  stack_traces_freelist = NULL;

  memset(allocs, 0, sizeof(Alloc) * stats->max_allocs);
  allocs_freelist = NULL;
  RB_INIT(&allocs_tree);

  stats = NULL;

  UNLOCK_MUTEX(lock);
}
