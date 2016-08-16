// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_ONLINE_ATTEMPT_H_
#define CHROMEOS_LOGIN_AUTH_ONLINE_ATTEMPT_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/login/auth/auth_status_consumer.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/google_service_auth_error.h"

class GaiaAuthFetcher;

namespace net {
class URLRequestContextGetter;
}

namespace chromeos {
class AuthAttemptState;
class AuthAttemptStateResolver;

class CHROMEOS_EXPORT OnlineAttempt : public GaiaAuthConsumer {
 public:
  OnlineAttempt(AuthAttemptState* current_attempt,
                AuthAttemptStateResolver* callback);
  virtual ~OnlineAttempt();

  
  
  
  
  void Initiate(net::URLRequestContextGetter* request_context);

  
  virtual void OnClientLoginFailure(
      const GoogleServiceAuthError& error) OVERRIDE;
  virtual void OnClientLoginSuccess(
      const GaiaAuthConsumer::ClientLoginResult& credentials) OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(OnlineAttemptTest, LoginSuccess);
  FRIEND_TEST_ALL_PREFIXES(OnlineAttemptTest, TwoFactorSuccess);

  
  static const int kClientLoginTimeoutMs;

  void TryClientLogin();
  void CancelClientLogin();

  void TriggerResolve(const AuthFailure& outcome);

  bool HasPendingFetch();
  void CancelRequest();

  scoped_refptr<base::MessageLoopProxy> message_loop_;

  AuthAttemptState* const attempt_;
  AuthAttemptStateResolver* const resolver_;

  
  scoped_ptr<GaiaAuthFetcher> client_fetcher_;

  
  bool try_again_;

  
  base::WeakPtrFactory<OnlineAttempt> weak_factory_;

  friend class OnlineAttemptTest;
  DISALLOW_COPY_AND_ASSIGN(OnlineAttempt);
};

}  

#endif  
