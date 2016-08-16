// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_GLOBAL_ERROR_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_GLOBAL_ERROR_H_

#include <set>
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "chrome/browser/ui/global_error/global_error.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_error_controller.h"

class Profile;

class SigninGlobalError : public GlobalErrorWithStandardBubble,
                          public SigninErrorController::Observer,
                          public KeyedService {
 public:
  SigninGlobalError(SigninErrorController* error_controller,
                    Profile* profile);
  virtual ~SigninGlobalError();

  
  bool HasError();

  
  
  void AttemptToFixError(Browser* browser);

 private:
  FRIEND_TEST_ALL_PREFIXES(SigninGlobalErrorTest, NoErrorAuthStatusProviders);
  FRIEND_TEST_ALL_PREFIXES(SigninGlobalErrorTest, ErrorAuthStatusProvider);
  FRIEND_TEST_ALL_PREFIXES(SigninGlobalErrorTest, AuthStatusEnumerateAllErrors);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual bool HasMenuItem() OVERRIDE;
  virtual int MenuItemCommandID() OVERRIDE;
  virtual base::string16 MenuItemLabel() OVERRIDE;
  virtual void ExecuteMenuItem(Browser* browser) OVERRIDE;
  virtual bool HasBubbleView() OVERRIDE;
  virtual base::string16 GetBubbleViewTitle() OVERRIDE;
  virtual std::vector<base::string16> GetBubbleViewMessages() OVERRIDE;
  virtual base::string16 GetBubbleViewAcceptButtonLabel() OVERRIDE;
  virtual base::string16 GetBubbleViewCancelButtonLabel() OVERRIDE;
  virtual void OnBubbleViewDidClose(Browser* browser) OVERRIDE;
  virtual void BubbleViewAcceptButtonPressed(Browser* browser) OVERRIDE;
  virtual void BubbleViewCancelButtonPressed(Browser* browser) OVERRIDE;

  
  virtual void OnErrorChanged() OVERRIDE;

  
  Profile* profile_;

  
  SigninErrorController* error_controller_;

  
  bool is_added_to_global_error_service_;

  DISALLOW_COPY_AND_ASSIGN(SigninGlobalError);
};

#endif  
