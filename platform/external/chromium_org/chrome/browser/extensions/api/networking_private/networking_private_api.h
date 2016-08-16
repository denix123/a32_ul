// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_API_H_

#include <string>

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "extensions/browser/extension_function.h"

namespace extensions {

namespace networking_private {

extern const char kErrorInvalidNetworkGuid[];
extern const char kErrorNetworkUnavailable[];
extern const char kErrorEncryptionError[];
extern const char kErrorNotReady[];
extern const char kErrorNotSupported[];

}  

class NetworkingPrivateGetPropertiesFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetPropertiesFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getProperties",
                             NETWORKINGPRIVATE_GETPROPERTIES);

 protected:
  virtual ~NetworkingPrivateGetPropertiesFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success(scoped_ptr<base::DictionaryValue> result);
  void Failure(const std::string& error_name);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetPropertiesFunction);
};

class NetworkingPrivateGetManagedPropertiesFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetManagedPropertiesFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getManagedProperties",
                             NETWORKINGPRIVATE_GETMANAGEDPROPERTIES);

 protected:
  virtual ~NetworkingPrivateGetManagedPropertiesFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success(scoped_ptr<base::DictionaryValue> result);
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetManagedPropertiesFunction);
};

class NetworkingPrivateGetStateFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetStateFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getState",
                             NETWORKINGPRIVATE_GETSTATE);

 protected:
  virtual ~NetworkingPrivateGetStateFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success(scoped_ptr<base::DictionaryValue> result);
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetStateFunction);
};

class NetworkingPrivateSetPropertiesFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateSetPropertiesFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.setProperties",
                             NETWORKINGPRIVATE_SETPROPERTIES);

 protected:
  virtual ~NetworkingPrivateSetPropertiesFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success();
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateSetPropertiesFunction);
};

class NetworkingPrivateCreateNetworkFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateCreateNetworkFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.createNetwork",
                             NETWORKINGPRIVATE_CREATENETWORK);

 protected:
  virtual ~NetworkingPrivateCreateNetworkFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success(const std::string& guid);
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateCreateNetworkFunction);
};

class NetworkingPrivateGetNetworksFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetNetworksFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getNetworks",
                             NETWORKINGPRIVATE_GETNETWORKS);

 protected:
  virtual ~NetworkingPrivateGetNetworksFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success(scoped_ptr<base::ListValue> network_list);
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetNetworksFunction);
};

class NetworkingPrivateGetVisibleNetworksFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetVisibleNetworksFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getVisibleNetworks",
                             NETWORKINGPRIVATE_GETVISIBLENETWORKS);

 protected:
  virtual ~NetworkingPrivateGetVisibleNetworksFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success(scoped_ptr<base::ListValue> network_list);
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetVisibleNetworksFunction);
};

class NetworkingPrivateGetEnabledNetworkTypesFunction
    : public SyncExtensionFunction {
 public:
  NetworkingPrivateGetEnabledNetworkTypesFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getEnabledNetworkTypes",
                             NETWORKINGPRIVATE_GETENABLEDNETWORKTYPES);

 protected:
  virtual ~NetworkingPrivateGetEnabledNetworkTypesFunction();

  
  virtual bool RunSync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetEnabledNetworkTypesFunction);
};

class NetworkingPrivateEnableNetworkTypeFunction
    : public SyncExtensionFunction {
 public:
  NetworkingPrivateEnableNetworkTypeFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.enableNetworkType",
                             NETWORKINGPRIVATE_ENABLENETWORKTYPE);

 protected:
  virtual ~NetworkingPrivateEnableNetworkTypeFunction();

  
  virtual bool RunSync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateEnableNetworkTypeFunction);
};

class NetworkingPrivateDisableNetworkTypeFunction
    : public SyncExtensionFunction {
 public:
  NetworkingPrivateDisableNetworkTypeFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.disableNetworkType",
                             NETWORKINGPRIVATE_DISABLENETWORKTYPE);

 protected:
  virtual ~NetworkingPrivateDisableNetworkTypeFunction();

  
  virtual bool RunSync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateDisableNetworkTypeFunction);
};

class NetworkingPrivateRequestNetworkScanFunction
    : public SyncExtensionFunction {
 public:
  NetworkingPrivateRequestNetworkScanFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.requestNetworkScan",
                             NETWORKINGPRIVATE_REQUESTNETWORKSCAN);

 protected:
  virtual ~NetworkingPrivateRequestNetworkScanFunction();

  
  virtual bool RunSync() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateRequestNetworkScanFunction);
};


class NetworkingPrivateStartConnectFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateStartConnectFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.startConnect",
                             NETWORKINGPRIVATE_STARTCONNECT);

 protected:
  virtual ~NetworkingPrivateStartConnectFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success();
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateStartConnectFunction);
};

class NetworkingPrivateStartDisconnectFunction : public AsyncExtensionFunction {
 public:
  NetworkingPrivateStartDisconnectFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.startDisconnect",
                             NETWORKINGPRIVATE_STARTDISCONNECT);

 protected:
  virtual ~NetworkingPrivateStartDisconnectFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void Success();
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateStartDisconnectFunction);
};

class NetworkingPrivateVerifyDestinationFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateVerifyDestinationFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.verifyDestination",
                             NETWORKINGPRIVATE_VERIFYDESTINATION);

 protected:
  virtual ~NetworkingPrivateVerifyDestinationFunction();

  
  virtual bool RunAsync() OVERRIDE;

  void Success(bool result);
  void Failure(const std::string& error);

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateVerifyDestinationFunction);
};

class NetworkingPrivateVerifyAndEncryptCredentialsFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateVerifyAndEncryptCredentialsFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.verifyAndEncryptCredentials",
                             NETWORKINGPRIVATE_VERIFYANDENCRYPTCREDENTIALS);

 protected:
  virtual ~NetworkingPrivateVerifyAndEncryptCredentialsFunction();

  
  virtual bool RunAsync() OVERRIDE;

  void Success(const std::string& result);
  void Failure(const std::string& error);

 private:
  DISALLOW_COPY_AND_ASSIGN(
      NetworkingPrivateVerifyAndEncryptCredentialsFunction);
};

class NetworkingPrivateVerifyAndEncryptDataFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateVerifyAndEncryptDataFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.verifyAndEncryptData",
                             NETWORKINGPRIVATE_VERIFYANDENCRYPTDATA);

 protected:
  virtual ~NetworkingPrivateVerifyAndEncryptDataFunction();

  
  virtual bool RunAsync() OVERRIDE;

  void Success(const std::string& result);
  void Failure(const std::string& error);

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateVerifyAndEncryptDataFunction);
};

class NetworkingPrivateSetWifiTDLSEnabledStateFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateSetWifiTDLSEnabledStateFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.setWifiTDLSEnabledState",
                             NETWORKINGPRIVATE_SETWIFITDLSENABLEDSTATE);

 protected:
  virtual ~NetworkingPrivateSetWifiTDLSEnabledStateFunction();

  
  virtual bool RunAsync() OVERRIDE;

  void Success(const std::string& result);
  void Failure(const std::string& error);

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateSetWifiTDLSEnabledStateFunction);
};

class NetworkingPrivateGetWifiTDLSStatusFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetWifiTDLSStatusFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getWifiTDLSStatus",
                             NETWORKINGPRIVATE_GETWIFITDLSSTATUS);

 protected:
  virtual ~NetworkingPrivateGetWifiTDLSStatusFunction();

  
  virtual bool RunAsync() OVERRIDE;

  void Success(const std::string& result);
  void Failure(const std::string& error);

 private:
  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetWifiTDLSStatusFunction);
};

class NetworkingPrivateGetCaptivePortalStatusFunction
    : public AsyncExtensionFunction {
 public:
  NetworkingPrivateGetCaptivePortalStatusFunction() {}
  DECLARE_EXTENSION_FUNCTION("networkingPrivate.getCaptivePortalStatus",
                             NETWORKINGPRIVATE_GETCAPTIVEPORTALSTATUS);

  
  virtual bool RunAsync() OVERRIDE;

 protected:
  virtual ~NetworkingPrivateGetCaptivePortalStatusFunction();

 private:
  void Success(const std::string& result);
  void Failure(const std::string& error);

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateGetCaptivePortalStatusFunction);
};

}  

#endif  
