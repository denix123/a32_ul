// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_DELEGATE_H_
#define CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_DELEGATE_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"

namespace content {
class BrowserContext;
}

namespace extensions {

namespace api {
namespace networking_private {

struct VerificationProperties;

}  
}  

class NetworkingPrivateDelegate {
 public:
  typedef base::Callback<void(scoped_ptr<base::DictionaryValue>)>
      DictionaryCallback;
  typedef base::Callback<void()> VoidCallback;
  typedef base::Callback<void(bool)> BoolCallback;
  typedef base::Callback<void(const std::string&)> StringCallback;
  typedef base::Callback<void(scoped_ptr<base::ListValue>)> NetworkListCallback;
  typedef base::Callback<void(const std::string&)> FailureCallback;
  typedef api::networking_private::VerificationProperties
      VerificationProperties;

  static NetworkingPrivateDelegate* GetForBrowserContext(
      content::BrowserContext* browser_context);

  
  virtual void GetProperties(const std::string& guid,
                             const DictionaryCallback& success_callback,
                             const FailureCallback& failure_callback) = 0;
  virtual void GetManagedProperties(
      const std::string& guid,
      const DictionaryCallback& success_callback,
      const FailureCallback& failure_callback) = 0;
  virtual void GetState(const std::string& guid,
                        const DictionaryCallback& success_callback,
                        const FailureCallback& failure_callback) = 0;
  virtual void SetProperties(const std::string& guid,
                             scoped_ptr<base::DictionaryValue> properties,
                             const VoidCallback& success_callback,
                             const FailureCallback& failure_callback) = 0;
  virtual void CreateNetwork(bool shared,
                             scoped_ptr<base::DictionaryValue> properties,
                             const StringCallback& success_callback,
                             const FailureCallback& failure_callback) = 0;
  virtual void GetNetworks(const std::string& network_type,
                           bool configured_only,
                           bool visible_only,
                           int limit,
                           const NetworkListCallback& success_callback,
                           const FailureCallback& failure_callback) = 0;
  virtual void StartConnect(const std::string& guid,
                            const VoidCallback& success_callback,
                            const FailureCallback& failure_callback) = 0;
  virtual void StartDisconnect(const std::string& guid,
                               const VoidCallback& success_callback,
                               const FailureCallback& failure_callback) = 0;
  virtual void VerifyDestination(
      const VerificationProperties& verification_properties,
      const BoolCallback& success_callback,
      const FailureCallback& failure_callback) = 0;
  virtual void VerifyAndEncryptCredentials(
      const std::string& guid,
      const VerificationProperties& verification_properties,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) = 0;
  virtual void VerifyAndEncryptData(
      const VerificationProperties& verification_properties,
      const std::string& data,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) = 0;
  virtual void SetWifiTDLSEnabledState(
      const std::string& ip_or_mac_address,
      bool enabled,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) = 0;
  virtual void GetWifiTDLSStatus(
      const std::string& ip_or_mac_address,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) = 0;
  virtual void GetCaptivePortalStatus(
      const std::string& guid,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) = 0;

  

  
  virtual scoped_ptr<base::ListValue> GetEnabledNetworkTypes() = 0;

  
  virtual bool EnableNetworkType(const std::string& type) = 0;

  
  virtual bool DisableNetworkType(const std::string& type) = 0;

  
  
  virtual bool RequestScan() = 0;

 protected:
  virtual ~NetworkingPrivateDelegate() {}
};

}  

#endif  
