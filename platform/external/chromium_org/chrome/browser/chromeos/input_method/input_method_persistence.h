// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_PERSISTENCE_H_
#define CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_PERSISTENCE_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chromeos/ime/input_method_manager.h"

class PrefService;

namespace chromeos {
namespace input_method {

class InputMethodPersistence : public InputMethodManager::Observer {
 public:
  
  
  
  
  explicit InputMethodPersistence(InputMethodManager* input_method_manager);
  virtual ~InputMethodPersistence();

  
  void OnSessionStateChange(InputMethodManager::UISessionState new_session);

  
  virtual void InputMethodChanged(InputMethodManager* manager,
                                  bool show_message) OVERRIDE;

 private:
  InputMethodManager* input_method_manager_;
  InputMethodManager::UISessionState ui_session_;
  DISALLOW_COPY_AND_ASSIGN(InputMethodPersistence);
};

void SetUserLRUInputMethodPreferenceForTesting(const std::string& username,
                                               const std::string& input_method,
                                               PrefService* local_state);

}  
}  

#endif  
