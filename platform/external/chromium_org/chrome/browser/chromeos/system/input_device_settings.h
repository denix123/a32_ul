// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_SYSTEM_INPUT_DEVICE_SETTINGS_H_
#define CHROME_BROWSER_CHROMEOS_SYSTEM_INPUT_DEVICE_SETTINGS_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/logging.h"

namespace chromeos {
namespace system {

namespace internal {

template <typename T>
class Optional {
 public:
  Optional()
    : value_(),
      is_set_(false) {
  }

  Optional& operator=(const Optional& other) {
    if (&other != this) {
      value_ = other.value_;
      is_set_ = other.is_set_;
    }
    return *this;
  }

  void Set(const T& value) {
    is_set_ = true;
    value_ = value;
  }

  bool is_set() const {
    return is_set_;
  }

  T value() const {
    DCHECK(is_set());
    return value_;
  }

  
  
  
  bool Update(const Optional& update) {
    if (update.is_set_ && (!is_set_ || value_ != update.value_)) {
      value_ = update.value_;
      is_set_ = true;
      return true;
    }
    return false;
  }

 private:
  T value_;
  bool is_set_;
};

}  

const int kMinPointerSensitivity = 1;
const int kMaxPointerSensitivity = 5;

class TouchpadSettings {
 public:
  TouchpadSettings();
  TouchpadSettings& operator=(const TouchpadSettings& other);

  void SetSensitivity(int value);
  int GetSensitivity() const;

  void SetTapToClick(bool enabled);
  bool GetTapToClick() const;

  void SetThreeFingerClick(bool enabled);
  bool GetThreeFingerClick() const;

  void SetTapDragging(bool enabled);
  bool GetTapDragging() const;

  void SetNaturalScroll(bool enabled);
  bool GetNaturalScroll() const;

  
  
  
  
  bool Update(const TouchpadSettings& settings, std::vector<std::string>* argv);

 private:
  internal::Optional<int> sensitivity_;
  internal::Optional<bool> tap_to_click_;
  internal::Optional<bool> three_finger_click_;
  internal::Optional<bool> tap_dragging_;
  internal::Optional<bool> natural_scroll_;
};

class MouseSettings {
 public:
  MouseSettings();
  MouseSettings& operator=(const MouseSettings& other);

  void SetSensitivity(int value);
  int GetSensitivity() const;

  void SetPrimaryButtonRight(bool right);
  bool GetPrimaryButtonRight() const;

  
  
  
  
  bool Update(const MouseSettings& update, std::vector<std::string>* argv);

 private:
  internal::Optional<int> sensitivity_;
  internal::Optional<bool> primary_button_right_;
};

class InputDeviceSettings {
 public:
  typedef base::Callback<void(bool)> DeviceExistsCallback;

  virtual ~InputDeviceSettings() {}

  
  static InputDeviceSettings* Get();

  
  
  
  static void SetSettingsForTesting(InputDeviceSettings* test_settings);

  
  
  virtual void TouchpadExists(const DeviceExistsCallback& callback) = 0;

  
  
  
  virtual void UpdateTouchpadSettings(const TouchpadSettings& settings) = 0;

  
  
  virtual void SetTouchpadSensitivity(int value) = 0;

  
  virtual void SetTapToClick(bool enabled) = 0;

  
  virtual void SetThreeFingerClick(bool enabled) = 0;

  
  virtual void SetTapDragging(bool enabled) = 0;

  
  virtual void SetNaturalScroll(bool enabled) = 0;

  
  virtual void MouseExists(const DeviceExistsCallback& callback) = 0;

  
  
  
  virtual void UpdateMouseSettings(const MouseSettings& settings) = 0;

  
  
  virtual void SetMouseSensitivity(int value) = 0;

  
  virtual void SetPrimaryButtonRight(bool right) = 0;

  
  
  virtual bool ForceKeyboardDrivenUINavigation() = 0;

  
  virtual void ReapplyTouchpadSettings() = 0;

  
  virtual void ReapplyMouseSettings() = 0;
};

}  
}  

#endif  
