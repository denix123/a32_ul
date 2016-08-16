// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_ONLINE_ATTEMPT_HOST_H_
#define CHROMEOS_LOGIN_AUTH_ONLINE_ATTEMPT_HOST_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/login/auth/auth_attempt_state_resolver.h"
#include "chromeos/login/auth/user_context.h"

namespace net {
class URLRequestContextGetter;
}

namespace chromeos {

class AuthAttemptState;
class OnlineAttempt;
class UserContext;

class CHROMEOS_EXPORT OnlineAttemptHost : public AuthAttemptStateResolver {
 public:
  class Delegate {
   public:
    
    virtual void OnChecked(const std::string& username, bool success) = 0;
  };

  explicit OnlineAttemptHost(Delegate* delegate);
  virtual ~OnlineAttemptHost();

  
  
  
  
  
  
  void Check(net::URLRequestContextGetter* request_context,
             const UserContext& user_context);

  
  void Reset();

  
  
  virtual void Resolve() OVERRIDE;

  
  void ResolveOnUIThread(bool success);

 private:
  scoped_refptr<base::MessageLoopProxy> message_loop_;
  Delegate* delegate_;
  UserContext current_attempt_user_context_;
  scoped_ptr<OnlineAttempt> online_attempt_;
  scoped_ptr<AuthAttemptState> state_;
  base::WeakPtrFactory<OnlineAttemptHost> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(OnlineAttemptHost);
};

}  

#endif  
