// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_RDEBUG_H
#define CRAZY_LINKER_RDEBUG_H

#include <stdint.h>

namespace crazy {

struct link_map_t {
  uintptr_t l_addr;
  char* l_name;
  uintptr_t l_ld;
  link_map_t* l_next;
  link_map_t* l_prev;
};

enum {
  RT_CONSISTENT,
  RT_ADD,
  RT_DELETE
};

struct r_debug {
  int32_t r_version;
  link_map_t* r_map;
  void (*r_brk)(void);
  int32_t r_state;
  uintptr_t r_ldbase;
};

typedef void (*crazy_callback_handler_t)(void* opaque);
typedef bool (*rdebug_callback_poster_t)(void* context,
                                         crazy_callback_handler_t,
                                         void* opaque);

class RDebug;
typedef void (*rdebug_callback_handler_t)(RDebug*, link_map_t*);

class RDebug {
 public:
  RDebug() : r_debug_(NULL), init_(false),
             readonly_entries_(false), post_for_later_execution_(NULL),
             post_for_later_execution_context_(NULL) {}
  ~RDebug() {}

  
  
  
  void AddEntry(link_map_t* entry) { RunOrDelay(&AddEntryInternal, entry); }
  void DelEntry(link_map_t* entry) { RunOrDelay(&DelEntryInternal, entry); }

  
  
  void SetDelayedCallbackPoster(rdebug_callback_poster_t poster,
                                void* context) {
    post_for_later_execution_ = poster;
    post_for_later_execution_context_ = context;
  }

  r_debug* GetAddress() { return r_debug_; }

 private:
  
  
  bool Init();

  
  
  
  
  
  
  void AddEntryImpl(link_map_t* entry);
  void DelEntryImpl(link_map_t* entry);
  static void AddEntryInternal(RDebug* rdebug, link_map_t* entry) {
    rdebug->AddEntryImpl(entry);
  }
  static void DelEntryInternal(RDebug* rdebug, link_map_t* entry) {
    rdebug->DelEntryImpl(entry);
  }

  
  
  bool PostCallback(rdebug_callback_handler_t handler, link_map_t* entry);

  
  void RunOrDelay(rdebug_callback_handler_t handler, link_map_t* entry) {
    if (!PostCallback(handler, entry))
      (*handler)(this, entry);
  }

  RDebug(const RDebug&);
  RDebug& operator=(const RDebug&);

  r_debug* r_debug_;
  bool init_;
  bool readonly_entries_;
  rdebug_callback_poster_t post_for_later_execution_;
  void* post_for_later_execution_context_;
};

}  

#endif  
