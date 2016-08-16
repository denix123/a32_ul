// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_IME_IME_KEYBOARD_H_
#define CHROMEOS_IME_IME_KEYBOARD_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "chromeos/chromeos_export.h"

namespace chromeos {
namespace input_method {

struct AutoRepeatRate {
  AutoRepeatRate() : initial_delay_in_ms(0), repeat_interval_in_ms(0) {}
  unsigned int initial_delay_in_ms;
  unsigned int repeat_interval_in_ms;
};

enum ModifierKey {
  kSearchKey = 0,  
  kControlKey,  
  kAltKey,  
  kVoidKey,
  kCapsLockKey,
  kEscapeKey,
  
  
  kNumModifierKeys,
};

class InputMethodUtil;

class CHROMEOS_EXPORT ImeKeyboard {
 public:
  class Observer {
   public:
    
    virtual void OnCapsLockChanged(bool enabled) = 0;
  };

  virtual ~ImeKeyboard() {}

  
  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

  
  
  virtual bool SetCurrentKeyboardLayoutByName(
      const std::string& layout_name) = 0;

  
  
  
  virtual bool ReapplyCurrentKeyboardLayout() = 0;

  
  
  
  
  
  
  
  
  
  virtual void ReapplyCurrentModifierLockStatus() = 0;

  
  virtual void DisableNumLock() = 0;

  
  
  virtual void SetCapsLockEnabled(bool enable_caps_lock) = 0;

  
  
  virtual bool CapsLockIsEnabled() = 0;

  
  virtual bool IsISOLevel5ShiftAvailable() const = 0;

  
  virtual bool IsAltGrAvailable() const = 0;

  
  
  virtual bool SetAutoRepeatEnabled(bool enabled) = 0;

  
  
  
  virtual bool SetAutoRepeatRate(const AutoRepeatRate& rate) = 0;

  
  
  static CHROMEOS_EXPORT bool GetAutoRepeatEnabledForTesting();

  
  
  static CHROMEOS_EXPORT bool GetAutoRepeatRateForTesting(
      AutoRepeatRate* out_rate);

  
  static CHROMEOS_EXPORT bool CheckLayoutNameForTesting(
      const std::string& layout_name);

  
  
  static ImeKeyboard* Create();
};

}  
}  

#endif  
