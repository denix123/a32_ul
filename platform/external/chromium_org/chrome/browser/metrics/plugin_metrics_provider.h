// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_PLUGIN_METRICS_PROVIDER_H_
#define CHROME_BROWSER_METRICS_PLUGIN_METRICS_PROVIDER_H_

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "components/metrics/metrics_provider.h"
#include "content/public/browser/browser_child_process_observer.h"

namespace base {
class FilePath;
}

namespace content {
struct WebPluginInfo;
}

class PrefRegistrySimple;
class PrefService;

class PluginMetricsProvider : public metrics::MetricsProvider,
                              public content::BrowserChildProcessObserver {
 public:
  explicit PluginMetricsProvider(PrefService* local_state);
  virtual ~PluginMetricsProvider();

  
  
  void GetPluginInformation(const base::Closure& done_callback);

  
  virtual void ProvideSystemProfileMetrics(
      metrics::SystemProfileProto* system_profile_proto) OVERRIDE;
  virtual void ProvideStabilityMetrics(
      metrics::SystemProfileProto* system_profile_proto) OVERRIDE;
  virtual void ClearSavedStabilityMetrics() OVERRIDE;

  
  void LogPluginLoadingError(const base::FilePath& plugin_path);

  
  void SetPluginsForTesting(const std::vector<content::WebPluginInfo>& plugins);

  
  
  static bool IsPluginProcess(int process_type);

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  FRIEND_TEST_ALL_PREFIXES(PluginMetricsProviderTest,
                           RecordCurrentStateWithDelay);
  FRIEND_TEST_ALL_PREFIXES(PluginMetricsProviderTest,
                           RecordCurrentStateIfPending);
  FRIEND_TEST_ALL_PREFIXES(PluginMetricsProviderTest,
                           ProvideStabilityMetricsWhenPendingTask);
  struct ChildProcessStats;

  
  void OnGotPlugins(const base::Closure& done_callback,
                    const std::vector<content::WebPluginInfo>& plugins);

  
  ChildProcessStats& GetChildProcessStats(
      const content::ChildProcessData& data);

  
  void RecordCurrentState();

  
  
  
  bool RecordCurrentStateWithDelay(int delay_ms);

  
  
  bool RecordCurrentStateIfPending();

  
  virtual void BrowserChildProcessHostConnected(
      const content::ChildProcessData& data) OVERRIDE;
  virtual void BrowserChildProcessCrashed(
      const content::ChildProcessData& data) OVERRIDE;
  virtual void BrowserChildProcessInstanceCreated(
      const content::ChildProcessData& data) OVERRIDE;

  PrefService* local_state_;

  
  std::vector<content::WebPluginInfo> plugins_;

  
  std::map<base::string16, ChildProcessStats> child_process_stats_buffer_;

  base::WeakPtrFactory<PluginMetricsProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PluginMetricsProvider);
};

#endif  
