// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_VARIATIONS_VARIATIONS_SERVICE_H_
#define CHROME_BROWSER_METRICS_VARIATIONS_VARIATIONS_SERVICE_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/metrics/field_trial.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "chrome/browser/metrics/variations/variations_request_scheduler.h"
#include "chrome/browser/metrics/variations/variations_seed_store.h"
#include "chrome/browser/web_resource/resource_request_allowed_notifier.h"
#include "chrome/common/chrome_version_info.h"
#include "components/variations/variations_seed_simulator.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

#if defined(OS_WIN)
#include "chrome/browser/metrics/variations/variations_registry_syncer_win.h"
#endif

class PrefService;
class PrefRegistrySimple;

namespace base {
class Version;
}

namespace metrics {
class MetricsStateManager;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace variations {
class VariationsSeed;
}

namespace chrome_variations {

class VariationsService
    : public net::URLFetcherDelegate,
      public ResourceRequestAllowedNotifier::Observer {
 public:
  class Observer {
   public:
    
    
    
    enum Severity {
      BEST_EFFORT,
      CRITICAL,
    };

    
    
    
    virtual void OnExperimentChangesDetected(Severity severity) = 0;

   protected:
    virtual ~Observer() {}
  };

  virtual ~VariationsService();

  
  
  
  bool CreateTrialsFromSeed();

  
  
  
  void StartRepeatedVariationsSeedFetch();

  
  void AddObserver(Observer* observer);

  
  void RemoveObserver(Observer* observer);

  
  
  
  
  
  void OnAppEnterForeground();

#if defined(OS_WIN)
  
  void StartGoogleUpdateRegistrySync();
#endif

  
  void SetCreateTrialsFromSeedCalledForTesting(bool called);

  
  
  
  static GURL GetVariationsServerURL(PrefService* local_prefs);

  
  static std::string GetDefaultVariationsServerURLForTesting();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  static void RegisterProfilePrefs(user_prefs::PrefRegistrySyncable* registry);

  
  
  
  static scoped_ptr<VariationsService> Create(
      PrefService* local_state,
      metrics::MetricsStateManager* state_manager);

  
  
  void set_policy_pref_service(PrefService* service) {
    DCHECK(service);
    policy_pref_service_ = service;
  }

 protected:
  
  
  virtual void DoActualFetch();

  
  
  virtual void StoreSeed(const std::string& seed_data,
                         const std::string& seed_signature,
                         const base::Time& date_fetched);

  
  
  
  
  
  VariationsService(ResourceRequestAllowedNotifier* notifier,
                    PrefService* local_state,
                    metrics::MetricsStateManager* state_manager);

 private:
  FRIEND_TEST_ALL_PREFIXES(VariationsServiceTest, Observer);
  FRIEND_TEST_ALL_PREFIXES(VariationsServiceTest, SeedStoredWhenOKStatus);
  FRIEND_TEST_ALL_PREFIXES(VariationsServiceTest, SeedNotStoredWhenNonOKStatus);
  FRIEND_TEST_ALL_PREFIXES(VariationsServiceTest, SeedDateUpdatedOn304Status);

  
  
  void FetchVariationsSeed();

  
  void NotifyObservers(
      const variations::VariationsSeedSimulator::Result& result);

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  virtual void OnResourceRequestsAllowed() OVERRIDE;

  
  
  void PerformSimulationWithVersion(scoped_ptr<variations::VariationsSeed> seed,
                                    const base::Version& version);

  
  void RecordLastFetchTime();

  
  PrefService* local_state_;

  
  
  metrics::MetricsStateManager* state_manager_;

  
  
  PrefService* policy_pref_service_;

  VariationsSeedStore seed_store_;

  
  
  
  scoped_ptr<VariationsRequestScheduler> request_scheduler_;

  
  
  scoped_ptr<net::URLFetcher> pending_seed_request_;

  
  GURL variations_server_url_;

  
  
  bool create_trials_from_seed_called_;

  
  bool initial_request_completed_;

  
  
  scoped_ptr<ResourceRequestAllowedNotifier> resource_request_allowed_notifier_;

  
  
  base::TimeTicks last_request_started_time_;

  
  ObserverList<Observer> observer_list_;

#if defined(OS_WIN)
  
  VariationsRegistrySyncer registry_syncer_;
#endif

  base::WeakPtrFactory<VariationsService> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(VariationsService);
};

}  

#endif  
