// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_USER_USER_ACCOUNTS_DELEGATE_H_
#define ASH_SYSTEM_USER_USER_ACCOUNTS_DELEGATE_H_

#include <string>
#include <vector>

#include "ash/ash_export.h"
#include "base/macros.h"
#include "base/observer_list.h"

namespace ash {
namespace tray {

class ASH_EXPORT UserAccountsDelegate {
 public:
  class Observer {
   public:
    Observer() {}
    virtual ~Observer() {}

    
    virtual void AccountListChanged() = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  UserAccountsDelegate();
  virtual ~UserAccountsDelegate();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  virtual std::string GetPrimaryAccountId() = 0;

  
  virtual std::vector<std::string> GetSecondaryAccountIds() = 0;

  
  virtual std::string GetAccountDisplayName(const std::string& account_id) = 0;

  
  
  virtual void DeleteAccount(const std::string& account_id) = 0;

  
  virtual void LaunchAddAccountDialog() = 0;

 protected:
  void NotifyAccountListChanged();

 private:
  ObserverList<Observer> observers_;

  DISALLOW_COPY_AND_ASSIGN(UserAccountsDelegate);
};

}  
}  

#endif  
