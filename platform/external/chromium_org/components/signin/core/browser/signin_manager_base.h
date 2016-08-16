// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_MANAGER_BASE_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_MANAGER_BASE_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/prefs/pref_member.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_internals_util.h"
#include "google_apis/gaia/google_service_auth_error.h"

class PrefService;

class SigninClient;

class SigninManagerBase : public KeyedService {
 public:
  class Observer {
   public:
    
    virtual void GoogleSigninFailed(const GoogleServiceAuthError& error) {}

    
    virtual void GoogleSigninSucceeded(const std::string& account_id,
                                       const std::string& username,
                                       const std::string& password) {}

    
    virtual void GoogleSignedOut(const std::string& account_id,
                                 const std::string& username) {}

   protected:
    virtual ~Observer() {}
  };

  SigninManagerBase(SigninClient* client);
  virtual ~SigninManagerBase();

  
  virtual void Initialize(PrefService* local_state);
  bool IsInitialized() const;

  
  
  
  
  
  
  virtual bool IsSigninAllowed() const;

  
  
  
  const std::string& GetAuthenticatedUsername() const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  const std::string& GetAuthenticatedAccountId() const;

  
  
  
  
  void SetAuthenticatedUsername(const std::string& username);

  
  bool IsAuthenticated() const;

  
  virtual bool AuthInProgress() const;

  
  virtual void Shutdown() OVERRIDE;

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void AddSigninDiagnosticsObserver(
      signin_internals_util::SigninDiagnosticsObserver* observer);
  void RemoveSigninDiagnosticsObserver(
      signin_internals_util::SigninDiagnosticsObserver* observer);

 protected:
  
  
  
  void clear_authenticated_username();

  
  
  ObserverList<Observer, true> observer_list_;

  
  void NotifyDiagnosticsObservers(
      const signin_internals_util::UntimedSigninStatusField& field,
      const std::string& value);
  void NotifyDiagnosticsObservers(
      const signin_internals_util::TimedSigninStatusField& field,
      const std::string& value);

 private:
  friend class FakeSigninManagerBase;
  friend class FakeSigninManager;

  SigninClient* client_;
  bool initialized_;

  
  std::string authenticated_username_;

  
  ObserverList<signin_internals_util::SigninDiagnosticsObserver, true>
      signin_diagnostics_observers_;

  base::WeakPtrFactory<SigninManagerBase> weak_pointer_factory_;

  DISALLOW_COPY_AND_ASSIGN(SigninManagerBase);
};

#endif  
