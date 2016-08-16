// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SYSTEM_MEMORY_MEMORY_INFO_PROVIDER_H_
#define EXTENSIONS_BROWSER_API_SYSTEM_MEMORY_MEMORY_INFO_PROVIDER_H_

#include "base/lazy_instance.h"
#include "extensions/browser/api/system_info/system_info_provider.h"
#include "extensions/common/api/system_memory.h"

namespace extensions {

class MemoryInfoProvider : public SystemInfoProvider {
 public:
  static MemoryInfoProvider* Get();

  const core_api::system_memory::MemoryInfo& memory_info() const {
    return info_;
  }

  static void InitializeForTesting(scoped_refptr<MemoryInfoProvider> provider);

 private:
  friend class MockMemoryInfoProviderImpl;

  MemoryInfoProvider();
  virtual ~MemoryInfoProvider();

  
  virtual bool QueryInfo() OVERRIDE;

  
  
  
  
  
  
  
  core_api::system_memory::MemoryInfo info_;

  static base::LazyInstance<scoped_refptr<MemoryInfoProvider> > provider_;

  DISALLOW_COPY_AND_ASSIGN(MemoryInfoProvider);
};

}  

#endif  
