// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_MAPPING_TABLE_H_
#define MOJO_SYSTEM_MAPPING_TABLE_H_

#include <stdint.h>

#include <vector>

#include "base/containers/hash_tables.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/public/c/system/types.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {

namespace embedder {
class PlatformSharedBufferMapping;
}

namespace system {

class Core;

namespace internal {
bool ShutdownCheckNoLeaks(Core*);
}

class MOJO_SYSTEM_IMPL_EXPORT MappingTable {
 public:
  MappingTable();
  ~MappingTable();

  
  
  MojoResult AddMapping(
      scoped_ptr<embedder::PlatformSharedBufferMapping> mapping);
  MojoResult RemoveMapping(uintptr_t address);

 private:
  friend bool internal::ShutdownCheckNoLeaks(Core*);

  typedef base::hash_map<uintptr_t, embedder::PlatformSharedBufferMapping*>
      AddressToMappingMap;
  AddressToMappingMap address_to_mapping_map_;

  DISALLOW_COPY_AND_ASSIGN(MappingTable);
};

}  
}  

#endif  
