// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_EXTENDED_AUTHENTICATOR_H_
#define CHROMEOS_LOGIN_AUTH_EXTENDED_AUTHENTICATOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/cryptohome/cryptohome_parameters.h"

namespace chromeos {

class AuthStatusConsumer;
class UserContext;

class CHROMEOS_EXPORT ExtendedAuthenticator
    : public base::RefCountedThreadSafe<ExtendedAuthenticator> {
 public:
  enum AuthState {
    SUCCESS,       
    NO_MOUNT,      
    FAILED_MOUNT,  
    FAILED_TPM,    
  };

  typedef base::Callback<void(const std::string& result)> ResultCallback;
  typedef base::Callback<void(const UserContext& context)> ContextCallback;

  class NewAuthStatusConsumer {
   public:
    virtual ~NewAuthStatusConsumer() {}
    
    virtual void OnAuthenticationFailure(AuthState state) = 0;
  };

  static scoped_refptr<ExtendedAuthenticator> Create(
      NewAuthStatusConsumer* consumer);
  static scoped_refptr<ExtendedAuthenticator> Create(
      AuthStatusConsumer* consumer);

  
  virtual void SetConsumer(AuthStatusConsumer* consumer) = 0;

  
  
  
  
  
  
  virtual void AuthenticateToMount(const UserContext& context,
                                   const ResultCallback& success_callback) = 0;

  
  
  virtual void AuthenticateToCheck(const UserContext& context,
                                   const base::Closure& success_callback) = 0;

  
  
  
  
  
  virtual void CreateMount(const std::string& user_id,
                           const std::vector<cryptohome::KeyDefinition>& keys,
                           const ResultCallback& success_callback) = 0;

  
  
  
  
  
  virtual void AddKey(const UserContext& context,
                      const cryptohome::KeyDefinition& key,
                      bool replace_existing,
                      const base::Closure& success_callback) = 0;

  
  
  
  
  
  virtual void UpdateKeyAuthorized(const UserContext& context,
                                   const cryptohome::KeyDefinition& key,
                                   const std::string& signature,
                                   const base::Closure& success_callback) = 0;

  
  
  
  virtual void RemoveKey(const UserContext& context,
                         const std::string& key_to_remove,
                         const base::Closure& success_callback) = 0;

  
  
  
  virtual void TransformKeyIfNeeded(const UserContext& user_context,
                                    const ContextCallback& callback) = 0;

 protected:
  ExtendedAuthenticator();
  virtual ~ExtendedAuthenticator();

 private:
  friend class base::RefCountedThreadSafe<ExtendedAuthenticator>;

  DISALLOW_COPY_AND_ASSIGN(ExtendedAuthenticator);
};

}  

#endif  
