// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_UTILITY_WIFI_WIFI_SERVICE_H_
#define CHROME_UTILITY_WIFI_WIFI_SERVICE_H_

#include <list>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/threading/sequenced_worker_pool.h"
#include "base/values.h"
#include "components/wifi/wifi_export.h"

namespace wifi {

class WIFI_EXPORT WiFiService {
 public:
  typedef std::vector<std::string> NetworkGuidList;
  typedef base::Callback<
      void(const NetworkGuidList& network_guid_list)> NetworkGuidListCallback;

  virtual ~WiFiService() {}

  
  virtual void Initialize(
      scoped_refptr<base::SequencedTaskRunner> task_runner) = 0;

  
  virtual void UnInitialize() = 0;

  
  static WiFiService* Create();

  
  
  virtual void GetProperties(const std::string& network_guid,
                             base::DictionaryValue* properties,
                             std::string* error) = 0;

  
  
  
  
  virtual void GetManagedProperties(const std::string& network_guid,
                                    base::DictionaryValue* managed_properties,
                                    std::string* error) = 0;

  
  
  
  
  
  virtual void GetState(const std::string& network_guid,
                        base::DictionaryValue* properties,
                        std::string* error) = 0;

  
  
  virtual void SetProperties(const std::string& network_guid,
                             scoped_ptr<base::DictionaryValue> properties,
                             std::string* error) = 0;

  
  
  
  
  virtual void CreateNetwork(bool shared,
                             scoped_ptr<base::DictionaryValue> properties,
                             std::string* network_guid,
                             std::string* error) = 0;

  
  
  virtual void GetVisibleNetworks(const std::string& network_type,
                                  base::ListValue* network_list,
                                  bool include_details) = 0;

  
  virtual void RequestNetworkScan() = 0;

  
  
  virtual void StartConnect(const std::string& network_guid,
                            std::string* error) = 0;

  
  
  virtual void StartDisconnect(const std::string& network_guid,
                               std::string* error) = 0;

  
  
  
  
  virtual void GetKeyFromSystem(const std::string& network_guid,
                                std::string* key_data,
                                std::string* error) = 0;

  
  
  virtual void SetEventObservers(
      scoped_refptr<base::MessageLoopProxy> message_loop_proxy,
      const NetworkGuidListCallback& networks_changed_observer,
      const NetworkGuidListCallback& network_list_changed_observer) = 0;

  
  
  virtual void RequestConnectedNetworkUpdate() = 0;

 protected:
  WiFiService() {}

  
  static const char kErrorAssociateToNetwork[];
  static const char kErrorInvalidData[];
  static const char kErrorNotConfigured[];
  static const char kErrorNotConnected[];
  static const char kErrorNotFound[];
  static const char kErrorNotImplemented[];
  static const char kErrorScanForNetworksWithName[];
  static const char kErrorWiFiService[];

 private:
  DISALLOW_COPY_AND_ASSIGN(WiFiService);
};

}  

#endif  
