// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_NAMES_IO_THREAD_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_NAMES_IO_THREAD_H_

#include <set>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/signin/signin_manager_factory.h"
#include "components/signin/core/browser/signin_manager_base.h"

class SigninNamesOnIOThread : public SigninManagerBase::Observer,
                              public SigninManagerFactory::Observer {
 public:
  typedef std::set<base::string16> EmailSet;

  
  SigninNamesOnIOThread();
  virtual ~SigninNamesOnIOThread();

  
  
  const EmailSet& GetEmails() const;

  
  
  void ReleaseResourcesOnUIThread();

 private:
  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  
  virtual void SigninManagerCreated(SigninManagerBase* manager) OVERRIDE;
  virtual void SigninManagerShutdown(SigninManagerBase* manager) OVERRIDE;

  
  void CheckOnIOThread() const;

  
  void CheckOnUIThread() const;

  
  
  void PostTaskToIOThread(bool add, const base::string16& email);

  
  void UpdateOnIOThread(bool add, const base::string16& email);

  EmailSet emails_;

  
  
  std::set<SigninManagerBase*> observed_managers_;
  bool resources_released_;

  DISALLOW_COPY_AND_ASSIGN(SigninNamesOnIOThread);
};

#endif  
