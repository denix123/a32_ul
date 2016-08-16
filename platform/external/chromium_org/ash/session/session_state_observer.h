// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SESSION_SESSION_STATE_OBSERVER_H_
#define ASH_SESSION_SESSION_STATE_OBSERVER_H_

#include <string>

#include "ash/ash_export.h"
#include "ash/session/session_state_delegate.h"
#include "base/basictypes.h"

namespace ash {

class ASH_EXPORT SessionStateObserver {
 public:
  
  virtual void ActiveUserChanged(const std::string& user_id) {}

  
  virtual void UserAddedToSession(const std::string& user_id) {}

  
  virtual void SessionStateChanged(SessionStateDelegate::SessionState state) {}

 protected:
  virtual ~SessionStateObserver() {}
};

class ASH_EXPORT ScopedSessionStateObserver {
 public:
  explicit ScopedSessionStateObserver(ash::SessionStateObserver* observer);
  virtual ~ScopedSessionStateObserver();

 private:
  ash::SessionStateObserver* observer_;

  DISALLOW_COPY_AND_ASSIGN(ScopedSessionStateObserver);
};

}  

#endif  