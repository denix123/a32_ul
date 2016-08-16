// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SESSION_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SESSION_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/local_discovery/privet_url_fetcher.h"
#include "chrome/common/extensions/api/gcd_private.h"

namespace base {
class DictionaryValue;
}

namespace local_discovery {

class PrivetHTTPClient;

class PrivetV3Session {
 private:
  class FetcherDelegate;

 public:
  
  class Delegate {
   public:
    virtual ~Delegate();

    
    virtual void OnSetupConfirmationNeeded(
        const std::string& confirmation_code,
        extensions::api::gcd_private::ConfirmationType confirmation_type) = 0;

    virtual void OnSessionStatus(
        extensions::api::gcd_private::Status status) = 0;
  };

  
  class Request {
   public:
    Request();
    virtual ~Request();

    virtual std::string GetName() = 0;
    virtual const base::DictionaryValue& GetInput() = 0;
    virtual void OnError(PrivetURLFetcher::ErrorType error) = 0;
    virtual void OnParsedJson(const base::DictionaryValue& value,
                              bool has_error) = 0;

   private:
    friend class PrivetV3Session;
    scoped_ptr<FetcherDelegate> fetcher_delegate_;
  };

  PrivetV3Session(scoped_ptr<PrivetHTTPClient> client, Delegate* delegate);
  ~PrivetV3Session();

  
  
  void Start();

  void ConfirmCode(const std::string& code);

  
  void StartRequest(Request* request);

 private:
  void ConfirmFakeCode();

  Delegate* delegate_;
  scoped_ptr<PrivetHTTPClient> client_;
  bool code_confirmed_;
  base::WeakPtrFactory<PrivetV3Session> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(PrivetV3Session);
};

}  

#endif  
