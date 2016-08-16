// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_EASY_UNLOCK_AUTH_ATTEMPT_H_
#define CHROME_BROWSER_SIGNIN_EASY_UNLOCK_AUTH_ATTEMPT_H_

#include <string>

#include "base/macros.h"

class Profile;

class EasyUnlockAuthAttempt {
 public:
  
  enum Type {
    TYPE_UNLOCK,
    TYPE_SIGNIN
  };

  EasyUnlockAuthAttempt(Profile* profile,
                        const std::string& user_id,
                        Type type);
  ~EasyUnlockAuthAttempt();

  
  
  bool Start(const std::string& user_id);

  
  
  
  void FinalizeUnlock(const std::string& user_id, bool success);

  
  
  
  
  
  void FinalizeSignin(const std::string& user_id,
                      const std::string& wrapped_secret,
                      const std::string& session_key);

 private:
  
  enum State {
    STATE_IDLE,
    STATE_RUNNING,
    STATE_DONE
  };

  
  void Cancel(const std::string& user_id);

  Profile* profile_;
  State state_;
  std::string user_id_;
  Type type_;

  DISALLOW_COPY_AND_ASSIGN(EasyUnlockAuthAttempt);
};

#endif  
