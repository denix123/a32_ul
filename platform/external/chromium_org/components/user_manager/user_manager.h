// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_MANAGER_H_
#define COMPONENTS_USER_MANAGER_USER_MANAGER_H_

#include <string>

#include "components/user_manager/user.h"
#include "components/user_manager/user_manager_export.h"

namespace chromeos {
class ScopedUserManagerEnabler;
}

namespace user_manager {

class RemoveUserDelegate;

class USER_MANAGER_EXPORT UserManager {
 public:
  
  
  class Observer {
   public:
    
    virtual void LocalStateChanged(UserManager* user_manager);

   protected:
    virtual ~Observer();
  };

  
  
  
  class UserSessionStateObserver {
   public:
    
    virtual void ActiveUserChanged(const User* active_user);

    
    virtual void UserAddedToSession(const User* added_user);

    
    
    virtual void ActiveUserHashChanged(const std::string& hash);

   protected:
    virtual ~UserSessionStateObserver();
  };

  
  class UserAccountData {
   public:
    UserAccountData(const base::string16& display_name,
                    const base::string16& given_name,
                    const std::string& locale);
    ~UserAccountData();
    const base::string16& display_name() const { return display_name_; }
    const base::string16& given_name() const { return given_name_; }
    const std::string& locale() const { return locale_; }

   private:
    const base::string16 display_name_;
    const base::string16 given_name_;
    const std::string locale_;

    DISALLOW_COPY_AND_ASSIGN(UserAccountData);
  };

  
  
  
  
  void Initialize();

  
  
  static bool IsInitialized();

  
  
  
  
  virtual void Shutdown() = 0;

  
  
  void Destroy();

  
  
  
  static UserManager* Get();

  virtual ~UserManager();

  
  
  virtual const UserList& GetUsers() const = 0;

  
  
  
  
  
  
  virtual UserList GetUsersAdmittedForMultiProfile() const = 0;

  
  virtual const UserList& GetLoggedInUsers() const = 0;

  
  
  
  virtual const UserList& GetLRULoggedInUsers() const = 0;

  
  
  
  
  
  
  virtual UserList GetUnlockUsers() const = 0;

  
  
  virtual const std::string& GetOwnerEmail() const = 0;

  
  
  
  
  
  virtual void UserLoggedIn(const std::string& user_id,
                            const std::string& username_hash,
                            bool browser_restart) = 0;

  
  virtual void SwitchActiveUser(const std::string& user_id) = 0;

  
  
  virtual void SwitchToLastActiveUser() = 0;

  
  
  
  
  
  
  
  virtual void SessionStarted() = 0;

  
  
  
  virtual void RemoveUser(const std::string& user_id,
                          RemoveUserDelegate* delegate) = 0;

  
  
  virtual void RemoveUserFromList(const std::string& user_id) = 0;

  
  
  virtual bool IsKnownUser(const std::string& user_id) const = 0;

  
  
  virtual const User* FindUser(const std::string& user_id) const = 0;

  
  
  
  virtual User* FindUserAndModify(const std::string& user_id) = 0;

  
  
  
  virtual const User* GetLoggedInUser() const = 0;
  virtual User* GetLoggedInUser() = 0;

  
  
  
  virtual const User* GetActiveUser() const = 0;
  virtual User* GetActiveUser() = 0;

  
  
  virtual const User* GetPrimaryUser() const = 0;

  
  virtual void SaveUserOAuthStatus(
      const std::string& user_id,
      User::OAuthTokenStatus oauth_token_status) = 0;

  
  
  virtual void SaveForceOnlineSignin(const std::string& user_id,
                                     bool force_online_signin) = 0;

  
  
  virtual void SaveUserDisplayName(const std::string& user_id,
                                   const base::string16& display_name) = 0;

  
  virtual void UpdateUserAccountData(const std::string& user_id,
                                     const UserAccountData& account_data) = 0;

  
  
  
  virtual base::string16 GetUserDisplayName(
      const std::string& user_id) const = 0;

  
  
  virtual void SaveUserDisplayEmail(const std::string& user_id,
                                    const std::string& display_email) = 0;

  
  
  
  virtual std::string GetUserDisplayEmail(const std::string& user_id) const = 0;

  
  virtual bool IsCurrentUserOwner() const = 0;

  
  virtual bool IsCurrentUserNew() const = 0;

  
  
  
  virtual bool IsCurrentUserNonCryptohomeDataEphemeral() const = 0;

  
  
  virtual bool CanCurrentUserLock() const = 0;

  
  virtual bool IsUserLoggedIn() const = 0;

  
  virtual bool IsLoggedInAsRegularUser() const = 0;

  
  virtual bool IsLoggedInAsDemoUser() const = 0;

  
  virtual bool IsLoggedInAsPublicAccount() const = 0;

  
  virtual bool IsLoggedInAsGuest() const = 0;

  
  virtual bool IsLoggedInAsSupervisedUser() const = 0;

  
  virtual bool IsLoggedInAsKioskApp() const = 0;

  
  virtual bool IsLoggedInAsStub() const = 0;

  
  
  
  virtual bool IsSessionStarted() const = 0;

  
  
  
  virtual bool IsUserNonCryptohomeDataEphemeral(
      const std::string& user_id) const = 0;

  virtual void AddObserver(Observer* obs) = 0;
  virtual void RemoveObserver(Observer* obs) = 0;

  virtual void AddSessionStateObserver(UserSessionStateObserver* obs) = 0;
  virtual void RemoveSessionStateObserver(UserSessionStateObserver* obs) = 0;

  virtual void NotifyLocalStateChanged() = 0;

  
  virtual bool AreSupervisedUsersAllowed() const = 0;

  
  virtual void ForceUpdateState() {}

 protected:
  
  static void SetInstance(UserManager* user_manager);

  
  
  
  
  
  static UserManager* instance;

 private:
  friend class chromeos::ScopedUserManagerEnabler;

  
  static UserManager* GetForTesting();

  
  
  static UserManager* SetForTesting(UserManager* user_manager);
};

}  

#endif  
