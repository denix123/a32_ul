// Copyright 2012 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#include <stdlib.h>
#include "./utils.h"




#if defined(PRINT_MEM_INFO)

#include <stdio.h>
#include <stdlib.h>  

static int num_malloc_calls = 0;
static int num_calloc_calls = 0;
static int num_free_calls = 0;
static int countdown_to_fail = 0;     

typedef struct MemBlock MemBlock;
struct MemBlock {
  void* ptr_;
  size_t size_;
  MemBlock* next_;
};

static MemBlock* all_blocks = NULL;
static size_t total_mem = 0;
static size_t total_mem_allocated = 0;
static size_t high_water_mark = 0;
static size_t mem_limit = 0;

static int exit_registered = 0;

static void PrintMemInfo(void) {
  fprintf(stderr, "\nMEMORY INFO:\n");
  fprintf(stderr, "num calls to: malloc = %4d\n", num_malloc_calls);
  fprintf(stderr, "              calloc = %4d\n", num_calloc_calls);
  fprintf(stderr, "              free   = %4d\n", num_free_calls);
  fprintf(stderr, "total_mem: %u\n", (uint32_t)total_mem);
  fprintf(stderr, "total_mem allocated: %u\n", (uint32_t)total_mem_allocated);
  fprintf(stderr, "high-water mark: %u\n", (uint32_t)high_water_mark);
  while (all_blocks != NULL) {
    MemBlock* b = all_blocks;
    all_blocks = b->next_;
    free(b);
  }
}

static void Increment(int* const v) {
  if (!exit_registered) {
#if defined(MALLOC_FAIL_AT)
    {
      const char* const malloc_fail_at_str = getenv("MALLOC_FAIL_AT");
      if (malloc_fail_at_str != NULL) {
        countdown_to_fail = atoi(malloc_fail_at_str);
      }
    }
#endif
#if defined(MALLOC_LIMIT)
    {
      const char* const malloc_limit_str = getenv("MALLOC_LIMIT");
      if (malloc_limit_str != NULL) {
        mem_limit = atoi(malloc_limit_str);
      }
    }
#endif
    (void)countdown_to_fail;
    (void)mem_limit;
    atexit(PrintMemInfo);
    exit_registered = 1;
  }
  ++*v;
}

static void AddMem(void* ptr, size_t size) {
  if (ptr != NULL) {
    MemBlock* const b = (MemBlock*)malloc(sizeof(*b));
    if (b == NULL) abort();
    b->next_ = all_blocks;
    all_blocks = b;
    b->ptr_ = ptr;
    b->size_ = size;
    total_mem += size;
    total_mem_allocated += size;
#if defined(PRINT_MEM_TRAFFIC)
#if defined(MALLOC_FAIL_AT)
    fprintf(stderr, "fail-count: %5d [mem=%u]\n",
            num_malloc_calls + num_calloc_calls, (uint32_t)total_mem);
#else
    fprintf(stderr, "Mem: %u (+%u)\n", (uint32_t)total_mem, (uint32_t)size);
#endif
#endif
    if (total_mem > high_water_mark) high_water_mark = total_mem;
  }
}

static void SubMem(void* ptr) {
  if (ptr != NULL) {
    MemBlock** b = &all_blocks;
    
    while (*b != NULL && (*b)->ptr_ != ptr) b = &(*b)->next_;
    if (*b == NULL) {
      fprintf(stderr, "Invalid pointer free! (%p)\n", ptr);
      abort();
    }
    {
      MemBlock* const block = *b;
      *b = block->next_;
      total_mem -= block->size_;
#if defined(PRINT_MEM_TRAFFIC)
      fprintf(stderr, "Mem: %u (-%u)\n",
              (uint32_t)total_mem, (uint32_t)block->size_);
#endif
      free(block);
    }
  }
}

#else
#define Increment(v) do {} while(0)
#define AddMem(p, s) do {} while(0)
#define SubMem(p)    do {} while(0)
#endif

static int CheckSizeArgumentsOverflow(uint64_t nmemb, size_t size) {
  const uint64_t total_size = nmemb * size;
  if (nmemb == 0) return 1;
  if ((uint64_t)size > WEBP_MAX_ALLOCABLE_MEMORY / nmemb) return 0;
  if (total_size != (size_t)total_size) return 0;
#if defined(PRINT_MEM_INFO) && defined(MALLOC_FAIL_AT)
  if (countdown_to_fail > 0 && --countdown_to_fail == 0) {
    return 0;    
  }
#endif
#if defined(MALLOC_LIMIT)
  if (mem_limit > 0 && total_mem + total_size >= mem_limit) {
    return 0;   
  }
#endif

  return 1;
}

void* WebPSafeMalloc(uint64_t nmemb, size_t size) {
  void* ptr;
  Increment(&num_malloc_calls);
  if (!CheckSizeArgumentsOverflow(nmemb, size)) return NULL;
  assert(nmemb * size > 0);
  ptr = malloc((size_t)(nmemb * size));
  AddMem(ptr, (size_t)(nmemb * size));
  return ptr;
}

void* WebPSafeCalloc(uint64_t nmemb, size_t size) {
  void* ptr;
  Increment(&num_calloc_calls);
  if (!CheckSizeArgumentsOverflow(nmemb, size)) return NULL;
  assert(nmemb * size > 0);
  ptr = calloc((size_t)nmemb, size);
  AddMem(ptr, (size_t)(nmemb * size));
  return ptr;
}

void WebPSafeFree(void* const ptr) {
  if (ptr != NULL) {
    Increment(&num_free_calls);
    SubMem(ptr);
  }
  free(ptr);
}
