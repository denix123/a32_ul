// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SETUP_FLOW_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVETV3_SETUP_FLOW_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/local_discovery/gcd_api_flow.h"
#include "chrome/browser/local_discovery/privet_http.h"
#include "chrome/browser/local_discovery/privetv3_session.h"

namespace local_discovery {

class PrivetV3SetupFlow : public PrivetV3Session::Delegate {
 public:
  
  class Delegate {
   public:
    typedef base::Callback<void(bool success)> ResultCallback;
    
    
    typedef base::Callback<void(const std::string& ssid,
                                const std::string& key)> CredentialsCallback;

    typedef base::Callback<void(scoped_ptr<PrivetHTTPClient>)>
        PrivetClientCallback;

    virtual ~Delegate();

    
    virtual scoped_ptr<GCDApiFlow> CreateApiFlow() = 0;

    
    virtual void GetWiFiCredentials(const CredentialsCallback& callback) = 0;

    
    
    virtual void SwitchToSetupWiFi(const ResultCallback& callback) = 0;

    
    
    virtual void CreatePrivetV3Client(const std::string& service_name,
                                      const PrivetClientCallback& callback) = 0;

    
    virtual void ConfirmSecurityCode(const std::string& confirmation_code,
                                     const ResultCallback& callback) = 0;

    
    virtual void RestoreWifi(const ResultCallback& callback) = 0;

    
    virtual void OnSetupDone() = 0;

    
    virtual void OnSetupError() = 0;
  };

  explicit PrivetV3SetupFlow(Delegate* delegate);
  virtual ~PrivetV3SetupFlow();

  
  void Register(const std::string& service_name);

#if defined(ENABLE_WIFI_BOOTSTRAPPING)
  void SetupWifiAndRegister(const std::string& device_ssid);
#endif  

  
  virtual void OnSetupConfirmationNeeded(
      const std::string& confirmation_code,
      extensions::api::gcd_private::ConfirmationType confirmation_type)
      OVERRIDE;
  virtual void OnSessionStatus(
      extensions::api::gcd_private::Status status) OVERRIDE;

  void OnSetupError();
  void OnDeviceRegistered();

  const std::string& service_name() const { return service_name_; }

 private:
  void OnTicketCreated(const std::string& ticket_id,
                       const std::string& device_id);
  void OnPrivetClientCreated(scoped_ptr<PrivetHTTPClient> privet_http_client);
  void OnCodeConfirmed(const std::string& code, bool success);

  Delegate* delegate_;
  std::string service_name_;
  std::string device_id_;
  scoped_ptr<GCDApiFlow> ticket_request_;
  scoped_ptr<PrivetV3Session> session_;
  scoped_ptr<PrivetV3Session::Request> setup_request_;
  base::WeakPtrFactory<PrivetV3SetupFlow> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrivetV3SetupFlow);
};

}  

#endif  
