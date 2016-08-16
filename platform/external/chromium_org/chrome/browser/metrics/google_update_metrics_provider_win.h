// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_GOOGLE_UPDATE_METRICS_PROVIDER_WIN_H_
#define CHROME_BROWSER_METRICS_GOOGLE_UPDATE_METRICS_PROVIDER_WIN_H_

#include "base/bind.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "chrome/installer/util/google_update_settings.h"
#include "components/metrics/metrics_provider.h"

class GoogleUpdateMetricsProviderWin : public metrics::MetricsProvider {
 public:
  GoogleUpdateMetricsProviderWin();
  virtual ~GoogleUpdateMetricsProviderWin();

  
  
  void GetGoogleUpdateData(const base::Closure& done_callback);

  
  virtual void ProvideSystemProfileMetrics(
      metrics::SystemProfileProto* system_profile_proto) OVERRIDE;

 private:
  
  struct GoogleUpdateMetrics {
    GoogleUpdateMetrics();
    ~GoogleUpdateMetrics();

    
    bool is_system_install;

    
    base::Time last_started_automatic_update_check;

    
    
    base::Time last_checked;

    
    GoogleUpdateSettings::ProductData google_update_data;

    
    GoogleUpdateSettings::ProductData product_data;
  };

  
  static GoogleUpdateMetrics GetGoogleUpdateDataOnBlockingPool();

  
  
  void ReceiveGoogleUpdateData(
      const base::Closure& done_callback,
      const GoogleUpdateMetrics& google_update_metrics);

  
  
  GoogleUpdateMetrics google_update_metrics_;

  base::WeakPtrFactory<GoogleUpdateMetricsProviderWin> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GoogleUpdateMetricsProviderWin);
};

#endif  
