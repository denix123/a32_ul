// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_LOCAL_DISCOVERY_LOCAL_DISCOVERY_UI_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_LOCAL_DISCOVERY_LOCAL_DISCOVERY_UI_HANDLER_H_

#include <map>
#include <string>
#include <vector>

#include "base/cancelable_callback.h"
#include "base/prefs/pref_member.h"
#include "chrome/browser/local_discovery/cloud_device_list.h"
#include "chrome/browser/local_discovery/cloud_print_printer_list.h"
#include "chrome/browser/local_discovery/privet_device_lister.h"
#include "chrome/browser/local_discovery/privet_http.h"
#include "chrome/browser/local_discovery/privetv3_setup_flow.h"
#include "components/signin/core/browser/signin_manager.h"
#include "content/public/browser/web_ui_message_handler.h"

#if defined(ENABLE_FULL_PRINTING) && !defined(OS_CHROMEOS)
#define CLOUD_PRINT_CONNECTOR_UI_AVAILABLE
#endif

#if defined(ENABLE_WIFI_BOOTSTRAPPING)
#include "chrome/browser/local_discovery/wifi/bootstrapping_device_lister.h"
#include "chrome/browser/local_discovery/wifi/wifi_manager.h"
#endif

namespace local_discovery {

class PrivetConfirmApiCallFlow;
class PrivetHTTPAsynchronousFactory;
class PrivetHTTPResolution;
class PrivetV1HTTPClient;
class ServiceDiscoverySharedClient;

class LocalDiscoveryUIHandler : public content::WebUIMessageHandler,
                                public PrivetRegisterOperation::Delegate,
                                public PrivetV3SetupFlow::Delegate,
                                public PrivetDeviceLister::Delegate,
                                public CloudDeviceListDelegate,
                                public SigninManagerBase::Observer {
 public:
  LocalDiscoveryUIHandler();
  virtual ~LocalDiscoveryUIHandler();

  static bool GetHasVisible();

  
  virtual void RegisterMessages() OVERRIDE;
  
  virtual void OnPrivetRegisterClaimToken(
      PrivetRegisterOperation* operation,
      const std::string& token,
      const GURL& url) OVERRIDE;
  virtual void OnPrivetRegisterError(
      PrivetRegisterOperation* operation,
      const std::string& action,
      PrivetRegisterOperation::FailureReason reason,
      int printer_http_code,
      const base::DictionaryValue* json) OVERRIDE;
  virtual void OnPrivetRegisterDone(
      PrivetRegisterOperation* operation,
      const std::string& device_id) OVERRIDE;

  
  virtual scoped_ptr<GCDApiFlow> CreateApiFlow() OVERRIDE;
  virtual void GetWiFiCredentials(const CredentialsCallback& callback) OVERRIDE;
  virtual void SwitchToSetupWiFi(const ResultCallback& callback) OVERRIDE;
  virtual void CreatePrivetV3Client(
      const std::string& service_name,
      const PrivetClientCallback& callback) OVERRIDE;
  virtual void ConfirmSecurityCode(const std::string& confirmation_code,
                                   const ResultCallback& callback) OVERRIDE;
  virtual void RestoreWifi(const ResultCallback& callback) OVERRIDE;
  virtual void OnSetupDone() OVERRIDE;
  virtual void OnSetupError() OVERRIDE;

  
  virtual void DeviceChanged(bool added,
                             const std::string& name,
                             const DeviceDescription& description) OVERRIDE;
  virtual void DeviceRemoved(const std::string& name) OVERRIDE;
  virtual void DeviceCacheFlushed() OVERRIDE;

  
  virtual void OnDeviceListReady(const std::vector<Device>& devices) OVERRIDE;
  virtual void OnDeviceListUnavailable() OVERRIDE;

  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

 private:
  typedef std::map<std::string, DeviceDescription> DeviceDescriptionMap;

  
  
  void HandleStart(const base::ListValue* args);

  
  void HandleIsVisible(const base::ListValue* args);

  
  void HandleRegisterDevice(const base::ListValue* args);

  
  void HandleConfirmCode(const base::ListValue* args);

  
  void HandleCancelRegistration(const base::ListValue* args);

  
  void HandleRequestDeviceList(const base::ListValue* args);

  
  
  void HandleOpenCloudPrintURL(const base::ListValue* args);

  
  void HandleShowSyncUI(const base::ListValue* args);

  
  void StartRegisterHTTP(scoped_ptr<PrivetHTTPClient> http_client);

  
  
  void OnConfirmDone(GCDApiFlow::Status status);

  
  void SendRegisterError();

  
  void SendRegisterDone(const std::string& service_name);

  
  void SetIsVisible(bool visible);

  
  std::string GetSyncAccount();

  
  void ResetCurrentRegistration();

  
  
  void PrivetClientToV3(const PrivetClientCallback& callback,
                        scoped_ptr<PrivetHTTPClient> client);

  
  
  
  void OnAnnouncementTimeoutReached();

  void CheckUserLoggedIn();

  void CheckListingDone();

  bool IsUserSupervisedOrOffTheRecord();

#if defined(CLOUD_PRINT_CONNECTOR_UI_AVAILABLE)
  void StartCloudPrintConnector();
  void OnCloudPrintPrefsChanged();
  void ShowCloudPrintSetupDialog(const base::ListValue* args);
  void HandleDisableCloudPrintConnector(const base::ListValue* args);
  void SetupCloudPrintConnectorSection();
  void RemoveCloudPrintConnectorSection();
  void RefreshCloudPrintStatusFromService();
#endif

#if defined(ENABLE_WIFI_BOOTSTRAPPING)
  void StartWifiBootstrapping();
  void OnBootstrappingDeviceChanged(
      bool available,
      const wifi::BootstrappingDeviceDescription& description);
#endif

  
  DeviceDescriptionMap device_descriptions_;

  
  scoped_refptr<ServiceDiscoverySharedClient> service_discovery_client_;

  
  scoped_ptr<PrivetHTTPAsynchronousFactory> privet_http_factory_;

  
  scoped_ptr<PrivetHTTPResolution> privet_resolution_;

  
  scoped_ptr<PrivetV1HTTPClient> current_http_client_;

  
  scoped_ptr<PrivetRegisterOperation> current_register_operation_;

  
  scoped_ptr<PrivetV3SetupFlow> current_setup_operation_;

  
  scoped_ptr<GCDApiFlow> confirm_api_call_flow_;

  
  scoped_ptr<PrivetDeviceLister> privet_lister_;

  
  bool is_visible_;

  
  scoped_ptr<GCDApiFlow> cloud_print_printer_list_;
  scoped_ptr<GCDApiFlow> cloud_device_list_;
  std::vector<Device> cloud_devices_;
  int failed_list_count_;
  int succeded_list_count_;
  ResultCallback device_code_callback_;

#if defined(CLOUD_PRINT_CONNECTOR_UI_AVAILABLE)
  StringPrefMember cloud_print_connector_email_;
  BooleanPrefMember cloud_print_connector_enabled_;
  bool cloud_print_connector_ui_enabled_;
#endif

#if defined(ENABLE_WIFI_BOOTSTRAPPING)
  scoped_ptr<wifi::WifiManager> wifi_manager_;
  scoped_ptr<wifi::BootstrappingDeviceLister> bootstrapping_device_lister_;
#endif

  DISALLOW_COPY_AND_ASSIGN(LocalDiscoveryUIHandler);
};

#undef CLOUD_PRINT_CONNECTOR_UI_AVAILABLE

}  
#endif  
