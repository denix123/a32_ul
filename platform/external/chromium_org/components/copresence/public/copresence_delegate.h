// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COPRESENCE_PUBLIC_COPRESENCE_DELEGATE_H_
#define COMPONENTS_COPRESENCE_PUBLIC_COPRESENCE_DELEGATE_H_

#include <string>
#include <vector>

#include "base/callback_forward.h"

namespace net {
class URLRequestContextGetter;
}

namespace copresence {

class Message;
class WhispernetClient;

enum CopresenceStatus { SUCCESS, FAIL };

typedef base::Callback<void(CopresenceStatus)> StatusCallback;

class CopresenceDelegate {
 public:
  
  
  virtual void HandleMessages(
      const std::string& app_id,
      const std::string& subscription_id,
      const std::vector<Message>& message) = 0;

  virtual net::URLRequestContextGetter* GetRequestContext() const = 0;

  virtual const std::string GetPlatformVersionString() const = 0;

  virtual const std::string GetAPIKey() const = 0;

  virtual WhispernetClient* GetWhispernetClient() = 0;
};

}  

#endif  
