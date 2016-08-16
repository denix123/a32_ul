// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_ERROR_NOTIFIER_ASH_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_ERROR_NOTIFIER_ASH_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_error_controller.h"

class Profile;

class SigninErrorNotifier : public SigninErrorController::Observer,
                            public KeyedService {
 public:
  SigninErrorNotifier(SigninErrorController* controller, Profile* profile);
  virtual ~SigninErrorNotifier();

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnErrorChanged() OVERRIDE;

 private:
  base::string16 GetMessageBody() const;

  
  SigninErrorController* error_controller_;

  
  Profile* profile_;

  
  std::string notification_id_;

  DISALLOW_COPY_AND_ASSIGN(SigninErrorNotifier);
};

#endif  
