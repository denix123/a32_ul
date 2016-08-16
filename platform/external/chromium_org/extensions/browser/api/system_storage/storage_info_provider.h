// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SYSTEM_STORAGE_STORAGE_INFO_PROVIDER_H_
#define EXTENSIONS_BROWSER_API_SYSTEM_STORAGE_STORAGE_INFO_PROVIDER_H_

#include <set>

#include "base/lazy_instance.h"
#include "base/memory/ref_counted.h"
#include "base/observer_list_threadsafe.h"
#include "base/timer/timer.h"
#include "extensions/browser/api/system_info/system_info_provider.h"
#include "extensions/common/api/system_storage.h"

namespace storage_monitor {
class StorageInfo;
}

namespace extensions {

namespace systeminfo {

void BuildStorageUnitInfo(const storage_monitor::StorageInfo& info,
                          core_api::system_storage::StorageUnitInfo* unit);

}  

typedef std::vector<linked_ptr<core_api::system_storage::StorageUnitInfo> >
    StorageUnitInfoList;

class StorageInfoProvider : public SystemInfoProvider {
 public:
  typedef base::Callback<void(const std::string&, double)>
      GetStorageFreeSpaceCallback;

  
  static StorageInfoProvider* Get();

  
  virtual void PrepareQueryOnUIThread() OVERRIDE;
  virtual void InitializeProvider(
      const base::Closure& do_query_info_callback) OVERRIDE;

  virtual double GetStorageFreeSpaceFromTransientIdOnFileThread(
      const std::string& transient_id);

  const StorageUnitInfoList& storage_unit_info_list() const;

  static void InitializeForTesting(scoped_refptr<StorageInfoProvider> provider);

 protected:
  StorageInfoProvider();

  virtual ~StorageInfoProvider();

  
  void GetAllStoragesIntoInfoList();

  
  
  
  
  
  
  
  StorageUnitInfoList info_;

 private:
  
  
  
  virtual bool QueryInfo() OVERRIDE;

  static base::LazyInstance<scoped_refptr<StorageInfoProvider> > provider_;

  DISALLOW_COPY_AND_ASSIGN(StorageInfoProvider);
};

}  

#endif  
