// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_SIGNIN_STATUS_METRICS_PROVIDER_H_
#define CHROME_BROWSER_METRICS_SIGNIN_STATUS_METRICS_PROVIDER_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "chrome/browser/signin/signin_manager_factory.h"
#include "chrome/browser/ui/browser_list_observer.h"
#include "components/metrics/metrics_provider.h"
#include "components/signin/core/browser/signin_manager_base.h"

class Browser;
class ChromeUserMetricsExtension;

namespace base {
class FilePath;
}

namespace metrics {
class ChromeUserMetricsExtension;
}

class SigninStatusMetricsProvider : public metrics::MetricsProvider,
                                    public chrome::BrowserListObserver,
                                    public SigninManagerBase::Observer,
                                    public SigninManagerFactory::Observer {
 public:
  virtual ~SigninStatusMetricsProvider();

  
  virtual void ProvideGeneralMetrics(
      metrics::ChromeUserMetricsExtension* uma_proto) OVERRIDE;

  
  static SigninStatusMetricsProvider* CreateInstance();

 private:
  
  
  
  
  explicit SigninStatusMetricsProvider(bool is_test);

  FRIEND_TEST_ALL_PREFIXES(SigninStatusMetricsProvider,
                           UpdateInitialSigninStatus);
  FRIEND_TEST_ALL_PREFIXES(SigninStatusMetricsProvider,
                           UpdateStatusWhenBrowserAdded);
  FRIEND_TEST_ALL_PREFIXES(SigninStatusMetricsProvider, GoogleSigninSucceeded);
  FRIEND_TEST_ALL_PREFIXES(SigninStatusMetricsProvider, GoogleSignedOut);

  
  
  
  enum ProfilesSigninStatus {
    ALL_PROFILES_SIGNED_IN,
    ALL_PROFILES_NOT_SIGNED_IN,
    MIXED_SIGNIN_STATUS,
    UNKNOWN_SIGNIN_STATUS,
    ERROR_GETTING_SIGNIN_STATUS,
    SIGNIN_STATUS_MAX,
  };

  
  
  virtual void OnBrowserAdded(Browser* browser) OVERRIDE;

  
  virtual void SigninManagerCreated(SigninManagerBase* manager) OVERRIDE;
  virtual void SigninManagerShutdown(SigninManagerBase* manager) OVERRIDE;

  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  
  void Initialize();

  
  
  
  
  
  void UpdateInitialSigninStatus(size_t total_count, size_t signed_in_count);

  
  void UpdateStatusWhenBrowserAdded(bool signed_in);

  
  void ComputeCurrentSigninStatus();

  
  
  void SetSigninStatus(ProfilesSigninStatus new_status);

  
  ProfilesSigninStatus GetSigninStatusForTesting();

  
  ProfilesSigninStatus signin_status_;

  
  
  ScopedObserver<SigninManagerBase, SigninStatusMetricsProvider>
      scoped_observer_;

  
  bool is_test_;

  base::WeakPtrFactory<SigninStatusMetricsProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SigninStatusMetricsProvider);
};

#endif  
