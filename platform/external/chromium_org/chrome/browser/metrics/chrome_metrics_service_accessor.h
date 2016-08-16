// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICE_ACCESSOR_H_
#define CHROME_BROWSER_METRICS_CHROME_METRICS_SERVICE_ACCESSOR_H_

#include <stdint.h>
#include <string>

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "chrome/browser/metrics/metrics_reporting_state.h"
#include "chrome/browser/metrics/metrics_service_accessor.h"

class ChromeExtensionDownloaderFactory;
class PrefService;
class Profile;

namespace {
class CrashesDOMHandler;
class FlashDOMHandler;
}

namespace component_updater {
class ComponentUpdateService;
void RegisterSwReporterComponent(ComponentUpdateService* cus,
                                 PrefService* prefs);
}

namespace extensions {
class MetricsPrivateGetIsCrashReportingEnabledFunction;
}

namespace prerender {
bool IsOmniboxEnabled(Profile* profile);
}

namespace system_logs {
class ChromeInternalLogSource;
}

namespace options {
class BrowserOptionsHandler;
}

class ChromeMetricsServiceAccessor : public MetricsServiceAccessor {
 private:
  friend void component_updater::RegisterSwReporterComponent(
      component_updater::ComponentUpdateService* cus,
      PrefService* prefs);
  friend bool prerender::IsOmniboxEnabled(Profile* profile);
  friend class ChromeExtensionDownloaderFactory;
  friend class ChromeRenderMessageFilter;
  friend class ::CrashesDOMHandler;
  friend class DataReductionProxyChromeSettings;
  friend class extensions::MetricsPrivateGetIsCrashReportingEnabledFunction;
  friend class ::FlashDOMHandler;
  friend class system_logs::ChromeInternalLogSource;
  friend class UmaSessionStats;
  friend class options::BrowserOptionsHandler;
  friend void InitiateMetricsReportingChange(
      bool, const OnMetricsReportingCallbackType&);

  FRIEND_TEST_ALL_PREFIXES(ChromeMetricsServiceAccessorTest,
                           MetricsReportingEnabled);
  FRIEND_TEST_ALL_PREFIXES(ChromeMetricsServiceAccessorTest,
                           CrashReportingEnabled);

  
  
  
  
  static bool IsMetricsReportingEnabled();

  
  
  
  static bool IsCrashReportingEnabled();

  
  
  
  
  
  
  
  static bool RegisterSyntheticFieldTrial(const std::string& trial_name,
                                          const std::string& group_name);

  
  
  static bool RegisterSyntheticFieldTrialWithNameHash(
      uint32_t trial_name_hash,
      const std::string& group_name);

  DISALLOW_IMPLICIT_CONSTRUCTORS(ChromeMetricsServiceAccessor);
};

#endif  
