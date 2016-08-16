// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_LOGIN_STATE_H_
#define CHROMEOS_LOGIN_LOGIN_STATE_H_

#include "base/basictypes.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"

namespace chromeos {

class CHROMEOS_EXPORT LoginState {
 public:
  enum LoggedInState {
    LOGGED_IN_NONE,       
    LOGGED_IN_SAFE_MODE,  
    LOGGED_IN_ACTIVE      
  };

  enum LoggedInUserType {
    LOGGED_IN_USER_NONE,             
    LOGGED_IN_USER_REGULAR,          
    LOGGED_IN_USER_OWNER,            
    LOGGED_IN_USER_GUEST,            
    LOGGED_IN_USER_RETAIL_MODE,      
    LOGGED_IN_USER_PUBLIC_ACCOUNT,   
    LOGGED_IN_USER_SUPERVISED,       
    LOGGED_IN_USER_KIOSK_APP         
  };

  class Observer {
   public:
    
    virtual void LoggedInStateChanged() = 0;

   protected:
    virtual ~Observer() {}
  };

  
  static void Initialize();
  static void Shutdown();
  static LoginState* Get();
  static bool IsInitialized();

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  void SetLoggedInStateAndPrimaryUser(
      LoggedInState state,
      LoggedInUserType type,
      const std::string& primary_user_hash);

  
  
  
  void SetLoggedInState(LoggedInState state, LoggedInUserType type);

  
  LoggedInUserType GetLoggedInUserType() const;

  
  bool IsUserLoggedIn() const;

  
  
  bool IsInSafeMode() const;

  
  bool IsGuestSessionUser() const;

  
  bool IsPublicSessionUser() const;

  
  bool IsKioskApp() const;

  
  bool UserHasNetworkProfile() const;

  
  
  bool IsUserAuthenticated() const;

  
  
  bool IsUserGaiaAuthenticated() const;

  void set_always_logged_in(bool always_logged_in) {
    always_logged_in_ = always_logged_in;
  }

  const std::string& primary_user_hash() const { return primary_user_hash_; }

 private:
  LoginState();
  virtual ~LoginState();

  void NotifyObservers();

  LoggedInState logged_in_state_;
  LoggedInUserType logged_in_user_type_;
  std::string primary_user_hash_;
  ObserverList<Observer> observer_list_;

  
  
  
  bool always_logged_in_;

  DISALLOW_COPY_AND_ASSIGN(LoginState);
};

}  

#endif  
