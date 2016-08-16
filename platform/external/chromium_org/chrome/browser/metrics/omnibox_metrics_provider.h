// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_OMNIBOX_METRICS_PROVIDER_H_
#define CHROME_BROWSER_METRICS_OMNIBOX_METRICS_PROVIDER_H_

#include "base/basictypes.h"
#include "components/metrics/metrics_provider.h"
#include "components/metrics/proto/chrome_user_metrics_extension.pb.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

struct OmniboxLog;

class OmniboxMetricsProvider : public metrics::MetricsProvider,
                               public content::NotificationObserver {
 public:
  OmniboxMetricsProvider();
  virtual ~OmniboxMetricsProvider();

  
  virtual void OnRecordingEnabled() OVERRIDE;
  virtual void OnRecordingDisabled() OVERRIDE;
  virtual void ProvideGeneralMetrics(
      metrics::ChromeUserMetricsExtension* uma_proto) OVERRIDE;

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  void RecordOmniboxOpenedURL(const OmniboxLog& log);

  
  content::NotificationRegistrar registrar_;

  
  
  metrics::ChromeUserMetricsExtension omnibox_events_cache;

  DISALLOW_COPY_AND_ASSIGN(OmniboxMetricsProvider);
};

#endif  
