// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_EVENT_RECORDER_H_
#define CHROMEOS_LOGIN_EVENT_RECORDER_H_

#include <string>

#include "base/macros.h"
#include "chromeos/chromeos_export.h"

namespace chromeos {

class CHROMEOS_EXPORT LoginEventRecorder {
 public:
  class Delegate {
   public:
  
  
  
  
    virtual void AddLoginTimeMarker(const std::string& marker_name,
                                    bool send_to_uma) = 0;

  
    virtual void RecordAuthenticationSuccess() = 0;

  
    virtual void RecordAuthenticationFailure() = 0;
  };
  LoginEventRecorder();
  virtual ~LoginEventRecorder();

  static LoginEventRecorder* Get();

  void SetDelegate(Delegate* delegate);

  
  
  
  
  void AddLoginTimeMarker(const std::string& marker_name, bool send_to_uma);

  
  void RecordAuthenticationSuccess();

  
  void RecordAuthenticationFailure();

 private:
  Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(LoginEventRecorder);
};

}  

#endif  
