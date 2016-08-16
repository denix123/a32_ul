// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_INVALIDATION_GCM_NETWORK_CHANNEL_DELEGATE_H_
#define COMPONENTS_INVALIDATION_GCM_NETWORK_CHANNEL_DELEGATE_H_

#include <string>

#include "base/callback.h"
#include "components/gcm_driver/gcm_client.h"

class GoogleServiceAuthError;

namespace syncer {

class GCMNetworkChannelDelegate {
 public:
  typedef base::Callback<void(const GoogleServiceAuthError& error,
                              const std::string& token)> RequestTokenCallback;
  typedef base::Callback<void(const std::string& registration_id,
                              gcm::GCMClient::Result result)> RegisterCallback;
  typedef base::Callback<void(const std::string& message,
                              const std::string& echo_token)> MessageCallback;
  typedef base::Callback<void(bool online)> ConnectionStateCallback;

  virtual ~GCMNetworkChannelDelegate() {}

  virtual void Initialize(ConnectionStateCallback callback) = 0;
  
  
  virtual void RequestToken(RequestTokenCallback callback) = 0;
  
  virtual void InvalidateToken(const std::string& token) = 0;

  
  
  virtual void Register(RegisterCallback callback) = 0;
  
  virtual void SetMessageReceiver(MessageCallback callback) = 0;
};
}  

#endif  
