// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_HANDLE_TABLE_H_
#define MOJO_SYSTEM_HANDLE_TABLE_H_

#include <utility>
#include <vector>

#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace system {

class Core;
class Dispatcher;
class DispatcherTransport;

typedef std::vector<scoped_refptr<Dispatcher>> DispatcherVector;

namespace internal {
bool ShutdownCheckNoLeaks(Core*);
}


class MOJO_SYSTEM_IMPL_EXPORT HandleTable {
 public:
  HandleTable();
  ~HandleTable();

  
  
  
  
  
  
  Dispatcher* GetDispatcher(MojoHandle handle);

  
  
  
  
  
  MojoResult GetAndRemoveDispatcher(MojoHandle handle,
                                    scoped_refptr<Dispatcher>* dispatcher);

  
  
  MojoHandle AddDispatcher(const scoped_refptr<Dispatcher>& dispatcher);

  
  
  
  
  std::pair<MojoHandle, MojoHandle> AddDispatcherPair(
      const scoped_refptr<Dispatcher>& dispatcher0,
      const scoped_refptr<Dispatcher>& dispatcher1);

  
  
  
  
  
  
  bool AddDispatcherVector(const DispatcherVector& dispatchers,
                           MojoHandle* handles);

  
  
  
  
  MojoResult MarkBusyAndStartTransport(
      MojoHandle disallowed_handle,
      const MojoHandle* handles,
      uint32_t num_handles,
      std::vector<DispatcherTransport>* transports);

  
  
  void RemoveBusyHandles(const MojoHandle* handles, uint32_t num_handles);

  
  
  
  void RestoreBusyHandles(const MojoHandle* handles, uint32_t num_handles);

 private:
  friend bool internal::ShutdownCheckNoLeaks(Core*);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  struct Entry {
    Entry();
    explicit Entry(const scoped_refptr<Dispatcher>& dispatcher);
    ~Entry();

    scoped_refptr<Dispatcher> dispatcher;
    bool busy;
  };
  typedef base::hash_map<MojoHandle, Entry> HandleToEntryMap;

  
  MojoHandle AddDispatcherNoSizeCheck(
      const scoped_refptr<Dispatcher>& dispatcher);

  HandleToEntryMap handle_to_entry_map_;
  MojoHandle next_handle_;  

  DISALLOW_COPY_AND_ASSIGN(HandleTable);
};

}  
}  

#endif  
