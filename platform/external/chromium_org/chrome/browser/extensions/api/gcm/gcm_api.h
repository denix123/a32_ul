// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_GCM_GCM_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_GCM_GCM_API_H_

#include "chrome/common/extensions/api/gcm.h"
#include "components/gcm_driver/gcm_client.h"
#include "extensions/browser/extension_function.h"

namespace gcm {
class GCMDriver;
class GCMProfileService;
}  

class Profile;

namespace extensions {

class GcmApiFunction : public AsyncExtensionFunction {
 public:
  GcmApiFunction() {}

 protected:
  virtual ~GcmApiFunction() {}

  
  virtual bool RunAsync() OVERRIDE FINAL;

  
  virtual bool DoWork() = 0;

  
  bool IsGcmApiEnabled() const;

  gcm::GCMDriver* GetGCMDriver() const;
};

class GcmRegisterFunction : public GcmApiFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("gcm.register", GCM_REGISTER);

  GcmRegisterFunction();

 protected:
  virtual ~GcmRegisterFunction();

  
  virtual bool DoWork() OVERRIDE FINAL;

 private:
  void CompleteFunctionWithResult(const std::string& registration_id,
                                  gcm::GCMClient::Result result);
};

class GcmUnregisterFunction : public GcmApiFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("gcm.unregister", GCM_UNREGISTER);

  GcmUnregisterFunction();

 protected:
  virtual ~GcmUnregisterFunction();

  
  virtual bool DoWork() OVERRIDE FINAL;

 private:
  void CompleteFunctionWithResult(gcm::GCMClient::Result result);
};

class GcmSendFunction : public GcmApiFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("gcm.send", GCM_SEND);

  GcmSendFunction();

 protected:
  virtual ~GcmSendFunction();

  
  virtual bool DoWork() OVERRIDE FINAL;

 private:
  void CompleteFunctionWithResult(const std::string& message_id,
                                  gcm::GCMClient::Result result);

  
  
  bool ValidateMessageData(const gcm::GCMClient::MessageData& data) const;
};

class GcmJsEventRouter {
 public:
  explicit GcmJsEventRouter(Profile* profile);

  virtual ~GcmJsEventRouter();

  void OnMessage(const std::string& app_id,
                 const gcm::GCMClient::IncomingMessage& message);
  void OnMessagesDeleted(const std::string& app_id);
  void OnSendError(const std::string& app_id,
                   const gcm::GCMClient::SendErrorDetails& send_error_details);

 private:
  
  
  Profile* profile_;
};

}  

#endif  
