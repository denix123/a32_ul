// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_CHROME_BROWSER_POLICY_CONNECTOR_H_
#define CHROME_BROWSER_POLICY_CHROME_BROWSER_POLICY_CONNECTOR_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "components/policy/core/browser/browser_policy_connector.h"

class PrefService;

namespace net {
class URLRequestContextGetter;
}

namespace policy {

class ConfigurationPolicyProvider;

class ChromeBrowserPolicyConnector : public BrowserPolicyConnector {
 public:
  
  
  static const int64 kServiceInitializationStartupDelay = 5000;

  
  
  ChromeBrowserPolicyConnector();

  virtual ~ChromeBrowserPolicyConnector();

  virtual void Init(
      PrefService* local_state,
      scoped_refptr<net::URLRequestContextGetter> request_context) OVERRIDE;

 private:
  ConfigurationPolicyProvider* CreatePlatformProvider();

  
  
  
  
 void AppendExtraFlagPerPolicy();

  DISALLOW_COPY_AND_ASSIGN(ChromeBrowserPolicyConnector);
};

}  

#endif  
