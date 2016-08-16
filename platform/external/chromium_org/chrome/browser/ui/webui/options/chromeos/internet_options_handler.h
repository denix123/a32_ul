// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_INTERNET_OPTIONS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_OPTIONS_CHROMEOS_INTERNET_OPTIONS_HANDLER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/webui/options/options_ui.h"
#include "chromeos/network/network_state_handler_observer.h"
#include "ui/gfx/native_widget_types.h"

class Browser;
class PrefService;

namespace chromeos {
class DeviceState;
class NetworkState;
class NetworkStateHandlerObserver;
}

namespace gfx {
class ImageSkia;
}

namespace views {
class WidgetDelegate;
}

namespace chromeos {
namespace options {

class InternetOptionsHandler
    : public ::options::OptionsPageUIHandler,
      public chromeos::NetworkStateHandlerObserver {
 public:
  InternetOptionsHandler();
  virtual ~InternetOptionsHandler();

 private:
  
  virtual void GetLocalizedValues(
      base::DictionaryValue* localized_strings) OVERRIDE;
  virtual void InitializePage() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  
  void ShowMorePlanInfoCallback(const base::ListValue* args);
  void SetApnCallback(const base::ListValue* args);
  void SetApnProperties(const base::ListValue* args,
                        const std::string& service_path,
                        const base::DictionaryValue& shill_properties);
  void CarrierStatusCallback();
  void SetCarrierCallback(const base::ListValue* args);
  void SimOperationCallback(const base::ListValue* args);

  
  void DisableNetworkTypeCallback(const base::ListValue* args);
  void EnableNetworkTypeCallback(const base::ListValue* args);
  void GetManagedPropertiesCallback(const base::ListValue* args);
  void RequestNetworkScanCallback(const base::ListValue* args);
  void StartConnectCallback(const base::ListValue* args);
  void StartDisconnectCallback(const base::ListValue* args);

  
  std::string GetIconDataUrl(int resource_id) const;

  
  void RefreshNetworkData();

  
  
  void UpdateConnectionData(const std::string& service_path);
  void UpdateConnectionDataCallback(
      const std::string& service_path,
      const base::DictionaryValue& shill_properties);
  
  void UpdateCarrier();

  
  virtual void DeviceListChanged() OVERRIDE;
  virtual void NetworkListChanged() OVERRIDE;
  virtual void NetworkConnectionStateChanged(
      const chromeos::NetworkState* network) OVERRIDE;
  virtual void NetworkPropertiesUpdated(
      const chromeos::NetworkState* network) OVERRIDE;
  virtual void DevicePropertiesUpdated(
      const chromeos::DeviceState* device) OVERRIDE;

  
  void UpdateLoggedInUserType();

  
  void SetServerHostnameCallback(const base::ListValue* args);
  void SetPreferNetworkCallback(const base::ListValue* args);
  void SetAutoConnectCallback(const base::ListValue* args);
  void SetIPConfigCallback(const base::ListValue* args);
  void SetIPConfigProperties(const base::ListValue* args,
                             const std::string& service_path,
                             const base::DictionaryValue& shill_properties);

  
  
  void PopulateDictionaryDetailsCallback(
      const std::string& service_path,
      const base::DictionaryValue& shill_properties);

  
  gfx::NativeWindow GetNativeWindow() const;

  
  float GetScaleFactor() const;

  
  const PrefService* GetPrefs() const;

  
  
  
  
  void NetworkCommandCallback(const base::ListValue* args);

  
  void AddConnection(const std::string& type);
  void SendShowDetailedInfo(const std::string& service_path);

  
  base::ListValue* GetWiredList();

  
  base::ListValue* GetWirelessList();

  
  base::ListValue* GetVPNList();

  
  base::ListValue* GetRememberedList();

  
  void FillNetworkInfo(base::DictionaryValue* dictionary);

  
  std::string details_path_;

  
  
  
  base::WeakPtrFactory<InternetOptionsHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(InternetOptionsHandler);
};

}  
}  

#endif  
