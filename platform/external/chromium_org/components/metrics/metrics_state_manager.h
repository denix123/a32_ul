// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_METRICS_STATE_MANAGER_H_
#define COMPONENTS_METRICS_METRICS_STATE_MANAGER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/metrics/field_trial.h"
#include "components/metrics/client_info.h"

class PrefService;
class PrefRegistrySimple;

namespace metrics {

class ClonedInstallDetector;

class MetricsStateManager {
 public:
  
  
  typedef base::Callback<void(const ClientInfo& client_info)>
      StoreClientInfoCallback;

  
  
  typedef base::Callback<scoped_ptr<ClientInfo>(void)> LoadClientInfoCallback;

  virtual ~MetricsStateManager();

  
  bool IsMetricsReportingEnabled();

  
  
  const std::string& client_id() const { return client_id_; }

  
  
  void ForceClientIdCreation();

  
  
  
  void CheckForClonedInstall(
      scoped_refptr<base::SingleThreadTaskRunner> task_runner);

  
  
  
  
  
  
  
  scoped_ptr<const base::FieldTrial::EntropyProvider> CreateEntropyProvider();

  
  
  static scoped_ptr<MetricsStateManager> Create(
      PrefService* local_state,
      const base::Callback<bool(void)>& is_reporting_enabled_callback,
      const StoreClientInfoCallback& store_client_info,
      const LoadClientInfoCallback& load_client_info);

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  FRIEND_TEST_ALL_PREFIXES(MetricsStateManagerTest, EntropySourceUsed_Low);
  FRIEND_TEST_ALL_PREFIXES(MetricsStateManagerTest, EntropySourceUsed_High);
  FRIEND_TEST_ALL_PREFIXES(MetricsStateManagerTest, LowEntropySource0NotReset);
  FRIEND_TEST_ALL_PREFIXES(MetricsStateManagerTest,
                           PermutedEntropyCacheClearedWhenLowEntropyReset);
  FRIEND_TEST_ALL_PREFIXES(MetricsStateManagerTest, ResetMetricsIDs);

  
  
  
  enum EntropySourceType {
    ENTROPY_SOURCE_NONE,
    ENTROPY_SOURCE_LOW,
    ENTROPY_SOURCE_HIGH,
  };

  
  
  
  
  
  
  MetricsStateManager(
      PrefService* local_state,
      const base::Callback<bool(void)>& is_reporting_enabled_callback,
      const StoreClientInfoCallback& store_client_info,
      const LoadClientInfoCallback& load_client_info);

  
  void BackUpCurrentClientInfo();

  
  
  scoped_ptr<ClientInfo> LoadClientInfoAndMaybeMigrate();

  
  
  
  int GetLowEntropySource();

  
  
  
  EntropySourceType entropy_source_returned() const {
    return entropy_source_returned_;
  }

  
  
  void ResetMetricsIDsIfNecessary();

  
  
  static bool instance_exists_;

  
  PrefService* const local_state_;

  
  
  const base::Callback<bool(void)> is_reporting_enabled_callback_;

  
  
  const StoreClientInfoCallback store_client_info_;

  
  
  const LoadClientInfoCallback load_client_info_;

  
  std::string client_id_;

  
  int low_entropy_source_;

  
  EntropySourceType entropy_source_returned_;

  scoped_ptr<ClonedInstallDetector> cloned_install_detector_;

  DISALLOW_COPY_AND_ASSIGN(MetricsStateManager);
};

}  

#endif  
