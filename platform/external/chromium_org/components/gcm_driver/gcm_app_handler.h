// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_APP_HANDLER_H_
#define COMPONENTS_GCM_DRIVER_GCM_APP_HANDLER_H_

#include <string>

#include "base/basictypes.h"
#include "components/gcm_driver/gcm_client.h"

namespace gcm {

class GCMAppHandler {
 public:
  GCMAppHandler();
  virtual ~GCMAppHandler();

  
  
  
  virtual void ShutdownHandler() = 0;

  
  virtual void OnMessage(const std::string& app_id,
                         const GCMClient::IncomingMessage& message) = 0;

  
  virtual void OnMessagesDeleted(const std::string& app_id) = 0;

  
  virtual void OnSendError(
      const std::string& app_id,
      const GCMClient::SendErrorDetails& send_error_details) = 0;

  
  virtual void OnSendAcknowledged(const std::string& app_id,
                                  const std::string& message_id) = 0;

  
  
  
  virtual bool CanHandle(const std::string& app_id) const;
};

}  

#endif  
