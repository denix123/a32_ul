// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef UI_BASE_ACCELERATORS_ACCELERATOR_H_
#define UI_BASE_ACCELERATORS_ACCELERATOR_H_

#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "ui/base/accelerators/platform_accelerator.h"
#include "ui/base/ui_base_export.h"
#include "ui/events/event_constants.h"
#include "ui/events/keycodes/keyboard_codes.h"

namespace ui {

class PlatformAccelerator;

class UI_BASE_EXPORT Accelerator {
 public:
  Accelerator();
  Accelerator(ui::KeyboardCode keycode, int modifiers);
  Accelerator(const Accelerator& accelerator);
  ~Accelerator();

  Accelerator& operator=(const Accelerator& accelerator);

  
  
  bool operator <(const Accelerator& rhs) const;

  bool operator ==(const Accelerator& rhs) const;

  bool operator !=(const Accelerator& rhs) const;

  ui::KeyboardCode key_code() const { return key_code_; }

  
  
  void set_type(ui::EventType type) { type_ = type; }
  ui::EventType type() const { return type_; }

  int modifiers() const { return modifiers_; }

  bool IsShiftDown() const;
  bool IsCtrlDown() const;
  bool IsAltDown() const;
  bool IsCmdDown() const;
  bool IsRepeat() const;

  
  base::string16 GetShortcutText() const;

  void set_platform_accelerator(scoped_ptr<PlatformAccelerator> p) {
    platform_accelerator_ = p.Pass();
  }

  
  const PlatformAccelerator* platform_accelerator() const {
    return platform_accelerator_.get();
  }

  void set_is_repeat(bool is_repeat) { is_repeat_ = is_repeat; }

 protected:
  
  KeyboardCode key_code_;

  
  EventType type_;

  
  int modifiers_;

  
  bool is_repeat_;

  
  scoped_ptr<PlatformAccelerator> platform_accelerator_;
};

class UI_BASE_EXPORT AcceleratorTarget {
 public:
  
  virtual bool AcceleratorPressed(const Accelerator& accelerator) = 0;

  
  
  
  virtual bool CanHandleAccelerators() const = 0;

 protected:
  virtual ~AcceleratorTarget() {}
};

class AcceleratorProvider {
 public:
  
  
  virtual bool GetAcceleratorForCommandId(int command_id,
                                          ui::Accelerator* accelerator) = 0;

 protected:
  virtual ~AcceleratorProvider() {}
};

}  

#endif  
