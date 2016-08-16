// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_MERGE_SESSION_HELPER_H_
#define GOOGLE_APIS_GAIA_MERGE_SESSION_HELPER_H_

#include <deque>

#include "base/observer_list.h"
#include "base/timer/timer.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/ubertoken_fetcher.h"
#include "net/url_request/url_fetcher_delegate.h"

class GaiaAuthFetcher;
class GoogleServiceAuthError;
class OAuth2TokenService;

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}

class MergeSessionHelper : public GaiaAuthConsumer,
                           public UbertokenConsumer,
                           public net::URLFetcherDelegate {
 public:
  class Observer {
   public:
    
    
    
    virtual void MergeSessionCompleted(const std::string& account_id,
                                       const GoogleServiceAuthError& error) = 0;
   protected:
    virtual ~Observer() {}
  };

  
  
  class ExternalCcResultFetcher : public GaiaAuthConsumer,
                                  public net::URLFetcherDelegate {
   public:
    
    
    typedef std::map<GURL, std::pair<std::string, net::URLFetcher*> >
        URLToTokenAndFetcher;

    
    typedef std::map<std::string, std::string> ResultMap;

    ExternalCcResultFetcher(MergeSessionHelper* helper);
    virtual ~ExternalCcResultFetcher();

    
    std::string GetExternalCcResult();

    
    
    void Start();

    
    bool IsRunning();

    
    URLToTokenAndFetcher get_fetcher_map_for_testing() {
      return fetchers_;
    }

    
    void TimeoutForTests();

   private:
    
    virtual void OnGetCheckConnectionInfoSuccess(
        const std::string& data) OVERRIDE;

    
    net::URLFetcher* CreateFetcher(const GURL& url);

    
    virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

    
    void Timeout();

    void CleanupTransientState();

    MergeSessionHelper* helper_;
    base::OneShotTimer<ExternalCcResultFetcher> timer_;
    scoped_ptr<GaiaAuthFetcher> gaia_auth_fetcher_;
    URLToTokenAndFetcher fetchers_;
    ResultMap results_;

    DISALLOW_COPY_AND_ASSIGN(ExternalCcResultFetcher);
  };

  MergeSessionHelper(OAuth2TokenService* token_service,
                     net::URLRequestContextGetter* request_context,
                     Observer* observer);
  virtual ~MergeSessionHelper();

  void LogIn(const std::string& account_id);

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void CancelAll();

  
  
  
  
  void LogOut(const std::string& account_id,
              const std::vector<std::string>& accounts);

  
  void LogOutAllAccounts();

  
  
  
  void SignalComplete(const std::string& account_id,
                      const GoogleServiceAuthError& error);

  
  bool is_running() const { return accounts_.size() > 0; }

  
  
  void StartFetchingExternalCcResult();

  
  
  bool StillFetchingExternalCcResult();

 private:
  net::URLRequestContextGetter* request_context() { return request_context_; }

  
  virtual void OnUbertokenSuccess(const std::string& token) OVERRIDE;
  virtual void OnUbertokenFailure(const GoogleServiceAuthError& error) OVERRIDE;

  
  virtual void OnMergeSessionSuccess(const std::string& data) OVERRIDE;
  virtual void OnMergeSessionFailure(const GoogleServiceAuthError& error)
      OVERRIDE;

  void LogOutInternal(const std::string& account_id,
                      const std::vector<std::string>& accounts);

  
  
  virtual void StartFetching();

  
  virtual void StartLogOutUrlFetch();

  
  void HandleNextAccount();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  OAuth2TokenService* token_service_;
  net::URLRequestContextGetter* request_context_;
  scoped_ptr<GaiaAuthFetcher> gaia_auth_fetcher_;
  scoped_ptr<UbertokenFetcher> uber_token_fetcher_;
  ExternalCcResultFetcher result_fetcher_;

  
  
  
  std::deque<std::string> accounts_;

  
  
  ObserverList<Observer, true> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(MergeSessionHelper);
};

#endif  
