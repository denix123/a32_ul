// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_INTRANET_REDIRECT_DETECTOR_H_
#define CHROME_BROWSER_INTRANET_REDIRECT_DETECTOR_H_

#include <set>
#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "net/base/network_change_notifier.h"
#include "net/dns/host_resolver_proc.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

class PrefRegistrySimple;

class IntranetRedirectDetector
    : public net::URLFetcherDelegate,
      public net::NetworkChangeNotifier::IPAddressObserver {
 public:
  
  
  
  
  
  
  IntranetRedirectDetector();
  virtual ~IntranetRedirectDetector();

  
  
  static GURL RedirectOrigin();

  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  typedef std::set<net::URLFetcher*> Fetchers;

  
  
  void FinishSleep();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  virtual void OnIPAddressChanged() OVERRIDE;

  GURL redirect_origin_;
  Fetchers fetchers_;
  std::vector<GURL> resulting_origins_;
  bool in_sleep_;  
                   
                   
  base::WeakPtrFactory<IntranetRedirectDetector> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(IntranetRedirectDetector);
};

#endif  
