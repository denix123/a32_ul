// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SYSTEM_CPU_CPU_INFO_PROVIDER_H_
#define EXTENSIONS_BROWSER_API_SYSTEM_CPU_CPU_INFO_PROVIDER_H_

#include <vector>

#include "base/cpu.h"
#include "base/lazy_instance.h"
#include "extensions/browser/api/system_info/system_info_provider.h"
#include "extensions/common/api/system_cpu.h"

namespace extensions {

class CpuInfoProvider : public SystemInfoProvider {
 public:
  
  static CpuInfoProvider* Get();

  const core_api::system_cpu::CpuInfo& cpu_info() const { return info_; }

  static void InitializeForTesting(scoped_refptr<CpuInfoProvider> provider);

 private:
  friend class MockCpuInfoProviderImpl;

  CpuInfoProvider();
  virtual ~CpuInfoProvider();

  
  
  virtual bool QueryCpuTimePerProcessor(
      std::vector<linked_ptr<core_api::system_cpu::ProcessorInfo> >* infos);

  
  virtual bool QueryInfo() OVERRIDE;

  
  std::vector<std::string> GetFeatures() const;

  
  
  
  
  
  
  
  core_api::system_cpu::CpuInfo info_;

  static base::LazyInstance<scoped_refptr<CpuInfoProvider> > provider_;
  base::CPU cpu_;

  DISALLOW_COPY_AND_ASSIGN(CpuInfoProvider);
};

}  

#endif  
