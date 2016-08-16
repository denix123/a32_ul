// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SESSION_MANAGER_CORE_SESSION_MANAGER_H_
#define COMPONENTS_SESSION_MANAGER_CORE_SESSION_MANAGER_H_

#include "base/memory/scoped_ptr.h"
#include "components/session_manager/session_manager_export.h"

namespace session_manager {

class SessionManagerDelegate;

enum SESSION_EXPORT SessionState {
  
  SESSION_STATE_UNKNOWN = 0,

  
  SESSION_STATE_OOBE,

  
  SESSION_STATE_LOGIN_PRIMARY,

  
  
  
  
  
  SESSION_STATE_LOGGED_IN_NOT_ACTIVE,

  
  
  SESSION_STATE_ACTIVE,

  
  
  SESSION_STATE_LOGIN_SECONDARY,
};

class SESSION_EXPORT SessionManager {
 public:
  SessionManager();
  virtual ~SessionManager();

  
  
  static SessionManager* Get();

  SessionState session_state() const { return session_state_; }
  virtual void SetSessionState(SessionState state);

  
  
  void Start();

  
  
  static bool HasBrowserRestarted();

 protected:
  
  void Initialize(SessionManagerDelegate* delegate);

  
  static void SetInstance(SessionManager* session_manager);

 private:
  
  
  
  
  
  static SessionManager* instance;

  SessionState session_state_;
  scoped_ptr<SessionManagerDelegate> delegate_;

  DISALLOW_COPY_AND_ASSIGN(SessionManager);
};

class SESSION_EXPORT SessionManagerDelegate {
 public:
  SessionManagerDelegate();
  virtual ~SessionManagerDelegate();

  virtual void SetSessionManager(
      session_manager::SessionManager* session_manager);

  
  virtual void Start() = 0;

 protected:
  session_manager::SessionManager* session_manager_;

 private:
  DISALLOW_COPY_AND_ASSIGN(SessionManagerDelegate);
};

}  

#endif  
