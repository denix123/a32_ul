// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_STATISTICS_PREFS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_STATISTICS_PREFS_H_

#include <map>

#include "base/containers/scoped_ptr_hash_map.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "components/data_reduction_proxy/common/data_reduction_proxy_pref_names.h"

class PrefService;

namespace base {
class ListValue;
class SequencedTaskRunner;
}

namespace data_reduction_proxy {

class DataReductionProxyStatisticsPrefs {
public:
  
  
  
  
  
  DataReductionProxyStatisticsPrefs(
      PrefService* pref_service,
      scoped_refptr<base::SequencedTaskRunner> task_runner,
      const base::TimeDelta& delay);
  ~DataReductionProxyStatisticsPrefs();

  
  
  void Init();

  
  int64 GetInt64(const char* pref_path);

  
  // The pref is later written to |pref service_|.
  void SetInt64(const char* pref_path, int64 pref_value);

  
  base::ListValue* GetList(const char* pref_path);

  
  
  void WritePrefs();

private:
  typedef std::map<const char*, int64> DataReductionProxyPrefMap;
  typedef base::ScopedPtrHashMap<const char*, base::ListValue>
      DataReductionProxyListPrefMap;

  
  
  void InitInt64Pref(const char* pref);

  
  
  void InitListPref(const char* pref);

  
  
  void DelayedWritePrefs();

  
  
  void TransferList(const base::ListValue& from_list,
                    base::ListValue* to_list);

  
  
  int64 GetListPrefInt64Value(const base::ListValue& list_update, size_t index);

  PrefService* pref_service_;
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  base::WeakPtrFactory<DataReductionProxyStatisticsPrefs> weak_factory_;
  const base::TimeDelta delay_;
  bool delayed_task_posted_;
  DataReductionProxyPrefMap pref_map_;
  DataReductionProxyListPrefMap list_pref_map_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyStatisticsPrefs);
};

}  

#endif  
