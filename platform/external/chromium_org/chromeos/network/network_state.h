// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_NETWORK_STATE_H_
#define CHROMEOS_NETWORK_NETWORK_STATE_H_

#include <string>
#include <vector>

#include "base/values.h"
#include "chromeos/network/managed_state.h"
#include "components/onc/onc_constants.h"
#include "url/gurl.h"

namespace base {
class DictionaryValue;
class Value;
}

namespace chromeos {

class CHROMEOS_EXPORT NetworkState : public ManagedState {
 public:
  explicit NetworkState(const std::string& path);
  virtual ~NetworkState();

  
  
  virtual bool PropertyChanged(const std::string& key,
                               const base::Value& value) OVERRIDE;
  virtual bool InitialPropertiesReceived(
      const base::DictionaryValue& properties) OVERRIDE;
  virtual void GetStateProperties(
      base::DictionaryValue* dictionary) const OVERRIDE;

  void IPConfigPropertiesChanged(const base::DictionaryValue& properties);

  
  bool RequiresActivation() const;

  
  bool visible() const { return visible_; }
  const std::string& security() const { return security_; }
  const std::string& device_path() const { return device_path_; }
  const std::string& guid() const { return guid_; }
  const std::string& profile_path() const { return profile_path_; }
  const std::string& error() const { return error_; }
  const std::string& last_error() const { return last_error_; }
  void clear_last_error() { last_error_.clear(); }

  
  std::string connection_state() const;

  const base::DictionaryValue& proxy_config() const { return proxy_config_; }

  
  
  const std::string& ip_address() const { return ip_address_; }
  const std::string& gateway() const { return gateway_; }
  const std::vector<std::string>& dns_servers() const { return dns_servers_; }
  const GURL& web_proxy_auto_discovery_url() const {
    return web_proxy_auto_discovery_url_;
  }

  
  bool connectable() const { return connectable_; }
  int signal_strength() const { return signal_strength_; }

  
  const std::string& eap_method() const { return eap_method_; }

  
  const std::string& network_technology() const {
    return network_technology_;
  }
  const std::string& activation_type() const { return activation_type_; }
  const std::string& activation_state() const { return activation_state_; }
  const std::string& roaming() const { return roaming_; }
  const std::string& payment_url() const { return payment_url_; }
  bool cellular_out_of_credits() const { return cellular_out_of_credits_; }

  
  bool HasCACertNSS() const { return has_ca_cert_nss_; }

  
  bool IsConnectedState() const;
  bool IsConnectingState() const;

  
  bool IsInProfile() const;

  
  bool IsPrivate() const;

  
  std::string GetDnsServersAsString() const;

  
  std::string GetNetmask() const;

  
  
  
  std::string GetSpecifier() const;

  
  void SetGuid(const std::string& guid);

  
  static bool StateIsConnected(const std::string& connection_state);
  static bool StateIsConnecting(const std::string& connection_state);
  static bool ErrorIsValid(const std::string& error);

 private:
  friend class MobileActivatorTest;
  friend class NetworkStateHandler;
  friend class NetworkChangeNotifierChromeosUpdateTest;

  
  
  bool UpdateName(const base::DictionaryValue& properties);

  
  bool visible_;

  
  
  
  std::string security_;
  std::string eap_method_;  
  std::string device_path_;
  std::string guid_;
  std::string connection_state_;
  std::string profile_path_;
  bool connectable_;

  
  
  std::string error_;

  
  
  std::string last_error_;

  
  
  
  std::string ip_address_;
  std::string gateway_;
  std::vector<std::string> dns_servers_;
  int prefix_length_;  
  GURL web_proxy_auto_discovery_url_;

  
  int signal_strength_;

  
  std::string network_technology_;
  std::string activation_type_;
  std::string activation_state_;
  std::string roaming_;
  std::string payment_url_;
  bool cellular_out_of_credits_;

  
  
  bool has_ca_cert_nss_;

  
  
  base::DictionaryValue proxy_config_;

  DISALLOW_COPY_AND_ASSIGN(NetworkState);
};

}  

#endif  
