// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_SYNC_AUTH_PROVIDER_H_
#define SYNC_INTERNAL_API_PUBLIC_SYNC_AUTH_PROVIDER_H_

#include "base/callback.h"

class GoogleServiceAuthError;

namespace syncer {

class SyncAuthProvider {
 public:
  typedef base::Callback<void(const GoogleServiceAuthError& error,
                              const std::string& token)> RequestTokenCallback;

  virtual ~SyncAuthProvider() {}

  
  
  virtual void RequestAccessToken(const RequestTokenCallback& callback) = 0;

  
  virtual void InvalidateAccessToken(const std::string& token) = 0;
};

}  

#endif  
