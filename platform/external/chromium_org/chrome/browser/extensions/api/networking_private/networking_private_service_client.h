// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_SERVICE_CLIENT_H_
#define CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_SERVICE_CLIENT_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/id_map.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/supports_user_data.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/values.h"
#include "chrome/browser/extensions/api/networking_private/networking_private_delegate.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/wifi/wifi_service.h"
#include "content/public/browser/utility_process_host.h"
#include "content/public/browser/utility_process_host_client.h"
#include "net/base/network_change_notifier.h"

namespace base {
class SequencedTaskRunner;
}

namespace wifi {
class WiFiService;
}

namespace extensions {

using wifi::WiFiService;

class NetworkingPrivateServiceClient
    : public KeyedService,
      public NetworkingPrivateDelegate,
      net::NetworkChangeNotifier::NetworkChangeObserver {
 public:
  
  class CryptoVerify {
   public:
    typedef base::Callback<
        void(const std::string& key_data, const std::string& error)>
        VerifyAndEncryptCredentialsCallback;

    
    struct Credentials {
      Credentials();
      ~Credentials();
      std::string certificate;
      std::string signed_data;
      std::string unsigned_data;
      std::string device_bssid;
      std::string public_key;
    };

    CryptoVerify();
    virtual ~CryptoVerify();

    
    
    static CryptoVerify* Create();

    virtual void VerifyDestination(const Credentials& credentials,
                                   bool* verified,
                                   std::string* error) = 0;

    virtual void VerifyAndEncryptCredentials(
        const std::string& network_guid,
        const Credentials& credentials,
        const VerifyAndEncryptCredentialsCallback& callback) = 0;

    virtual void VerifyAndEncryptData(const Credentials& credentials,
                                      const std::string& data,
                                      std::string* base64_encoded_ciphertext,
                                      std::string* error) = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(CryptoVerify);
  };

  
  class Observer {
   public:
    Observer() {}
    virtual ~Observer() {}

    virtual void OnNetworksChangedEvent(
        const std::vector<std::string>& network_guids) = 0;
    virtual void OnNetworkListChangedEvent(
        const std::vector<std::string>& network_guids) = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  
  
  
  
  NetworkingPrivateServiceClient(wifi::WiFiService* wifi_service,
                                 CryptoVerify* crypto_verify);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void GetProperties(const std::string& guid,
                             const DictionaryCallback& success_callback,
                             const FailureCallback& failure_callback) OVERRIDE;
  virtual void GetManagedProperties(
      const std::string& guid,
      const DictionaryCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void GetState(const std::string& guid,
                        const DictionaryCallback& success_callback,
                        const FailureCallback& failure_callback) OVERRIDE;
  virtual void SetProperties(const std::string& guid,
                             scoped_ptr<base::DictionaryValue> properties_dict,
                             const VoidCallback& success_callback,
                             const FailureCallback& failure_callback) OVERRIDE;
  virtual void CreateNetwork(bool shared,
                             scoped_ptr<base::DictionaryValue> properties_dict,
                             const StringCallback& success_callback,
                             const FailureCallback& failure_callback) OVERRIDE;
  virtual void GetNetworks(const std::string& network_type,
                           bool configured_only,
                           bool visible_only,
                           int limit,
                           const NetworkListCallback& success_callback,
                           const FailureCallback& failure_callback) OVERRIDE;
  virtual void StartConnect(const std::string& guid,
                            const VoidCallback& success_callback,
                            const FailureCallback& failure_callback) OVERRIDE;
  virtual void StartDisconnect(
      const std::string& guid,
      const VoidCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void VerifyDestination(
      const VerificationProperties& verification_properties,
      const BoolCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void VerifyAndEncryptCredentials(
      const std::string& guid,
      const VerificationProperties& verification_properties,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void VerifyAndEncryptData(
      const VerificationProperties& verification_properties,
      const std::string& data,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void SetWifiTDLSEnabledState(
      const std::string& ip_or_mac_address,
      bool enabled,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void GetWifiTDLSStatus(
      const std::string& ip_or_mac_address,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual void GetCaptivePortalStatus(
      const std::string& guid,
      const StringCallback& success_callback,
      const FailureCallback& failure_callback) OVERRIDE;
  virtual scoped_ptr<base::ListValue> GetEnabledNetworkTypes() OVERRIDE;
  virtual bool EnableNetworkType(const std::string& type) OVERRIDE;
  virtual bool DisableNetworkType(const std::string& type) OVERRIDE;
  virtual bool RequestScan() OVERRIDE;

  
  void AddObserver(Observer* network_events_observer);

  
  
  void RemoveObserver(Observer* network_events_observer);

  
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

 private:
  
  
  
  typedef int32 ServiceCallbacksID;
  struct ServiceCallbacks {
    ServiceCallbacks();
    ~ServiceCallbacks();

    DictionaryCallback get_properties_callback;
    VoidCallback start_connect_callback;
    VoidCallback start_disconnect_callback;
    VoidCallback set_properties_callback;
    StringCallback create_network_callback;
    NetworkListCallback get_visible_networks_callback;
    FailureCallback failure_callback;

    BoolCallback verify_destination_callback;
    StringCallback verify_and_encrypt_data_callback;
    StringCallback verify_and_encrypt_credentials_callback;

    ServiceCallbacksID id;
  };
  typedef IDMap<ServiceCallbacks, IDMapOwnPointer> ServiceCallbacksMap;

  virtual ~NetworkingPrivateServiceClient();

  
  void AfterGetProperties(ServiceCallbacksID callback_id,
                          const std::string& network_guid,
                          scoped_ptr<base::DictionaryValue> properties,
                          const std::string* error);
  void AfterSetProperties(ServiceCallbacksID callback_id,
                          const std::string* error);
  void AfterCreateNetwork(ServiceCallbacksID callback_id,
                          const std::string* network_guid,
                          const std::string* error);
  void AfterGetVisibleNetworks(ServiceCallbacksID callback_id,
                               scoped_ptr<base::ListValue> networks);
  void AfterStartConnect(ServiceCallbacksID callback_id,
                         const std::string* error);
  void AfterStartDisconnect(ServiceCallbacksID callback_id,
                            const std::string* error);
  void AfterVerifyDestination(ServiceCallbacksID callback_id,
                              const bool* result,
                              const std::string* error);
  void AfterVerifyAndEncryptData(ServiceCallbacksID callback_id,
                                 const std::string* result,
                                 const std::string* error);
  void AfterVerifyAndEncryptCredentials(ServiceCallbacksID callback_id,
                                        const std::string& encrypted_data,
                                        const std::string& error);

  void OnNetworksChangedEventOnUIThread(
      const WiFiService::NetworkGuidList& network_guid_list);
  void OnNetworkListChangedEventOnUIThread(
      const WiFiService::NetworkGuidList& network_guid_list);

  
  ServiceCallbacks* AddServiceCallbacks();
  
  void RemoveServiceCallbacks(ServiceCallbacksID callback_id);

  
  ServiceCallbacksMap callbacks_map_;
  
  ObserverList<Observer> network_events_observers_;
  
  
  scoped_ptr<CryptoVerify> crypto_verify_;
  
  scoped_ptr<wifi::WiFiService> wifi_service_;
  
  base::SequencedWorkerPool::SequenceToken sequence_token_;
  
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  
  base::WeakPtrFactory<NetworkingPrivateServiceClient> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateServiceClient);
};

}  

#endif  
