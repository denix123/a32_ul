// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EVENTS_EVENT_REWRITER_H_
#define CHROME_BROWSER_CHROMEOS_EVENTS_EVENT_REWRITER_H_

#include <map>
#include <set>
#include <string>

#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/event.h"
#include "ui/events/event_rewriter.h"

class PrefService;

namespace ash {
class StickyKeysController;
}

namespace chromeos {
namespace input_method {
class ImeKeyboard;
}

class EventRewriter : public ui::EventRewriter {
 public:
  enum DeviceType {
    kDeviceUnknown = 0,
    kDeviceAppleKeyboard,
  };

  
  
  
  explicit EventRewriter(ash::StickyKeysController* sticky_keys_controller);
  virtual ~EventRewriter();

  
  DeviceType KeyboardDeviceAddedForTesting(int device_id,
                                           const std::string& device_name);

  
  void RewriteMouseButtonEventForTesting(
      const ui::MouseEvent& event,
      scoped_ptr<ui::Event>* rewritten_event);

  const std::map<int, DeviceType>& device_id_to_type_for_testing() const {
    return device_id_to_type_;
  }
  void set_last_keyboard_device_id_for_testing(int device_id) {
    last_keyboard_device_id_ = device_id;
  }
  void set_pref_service_for_testing(const PrefService* pref_service) {
    pref_service_for_testing_ = pref_service;
  }
  void set_ime_keyboard_for_testing(
      chromeos::input_method::ImeKeyboard* ime_keyboard) {
    ime_keyboard_for_testing_ = ime_keyboard;
  }

  
  virtual ui::EventRewriteStatus RewriteEvent(
      const ui::Event& event,
      scoped_ptr<ui::Event>* rewritten_event) OVERRIDE;
  virtual ui::EventRewriteStatus NextDispatchEvent(
      const ui::Event& last_event,
      scoped_ptr<ui::Event>* new_event) OVERRIDE;

  
  
  static void BuildRewrittenKeyEvent(const ui::KeyEvent& key_event,
                                     ui::KeyboardCode key_code,
                                     int flags,
                                     scoped_ptr<ui::Event>* rewritten_event);

 private:
  
  struct MutableKeyState {
    int flags;
    ui::KeyboardCode key_code;
  };

  
  struct KeyboardRemapping {
    ui::KeyboardCode input_key_code;
    int input_flags;
    ui::KeyboardCode output_key_code;
    int output_flags;
  };

  void DeviceKeyPressedOrReleased(int device_id);

  
  const PrefService* GetPrefService() const;

  
  void KeyboardDeviceAdded(int device_id);

  
  
  DeviceType KeyboardDeviceAddedInternal(int device_id,
                                         const std::string& device_name);

  
  bool IsAppleKeyboard() const;

  
  // keys instead of having them rewritten into back, forward, brightness,
  
  
  bool TopRowKeysAreFunctionKeys(const ui::KeyEvent& event) const;

  
  
  int GetRemappedModifierMasks(const PrefService& pref_service,
                               const ui::Event& event,
                               int original_flags) const;

  
  
  
  bool RewriteWithKeyboardRemappingsByKeyCode(
      const KeyboardRemapping* remappings,
      size_t num_remappings,
      const MutableKeyState& input,
      MutableKeyState* remapped_state);

  
  ui::EventRewriteStatus RewriteKeyEvent(
      const ui::KeyEvent& key_event,
      scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus RewriteMouseButtonEvent(
      const ui::MouseEvent& mouse_event,
      scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus RewriteMouseWheelEvent(
      const ui::MouseWheelEvent& mouse_event,
      scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus RewriteTouchEvent(
      const ui::TouchEvent& touch_event,
      scoped_ptr<ui::Event>* rewritten_event);
  ui::EventRewriteStatus RewriteScrollEvent(
      const ui::ScrollEvent& scroll_event,
      scoped_ptr<ui::Event>* rewritten_event);

  
  
  void RewriteModifierKeys(const ui::KeyEvent& event, MutableKeyState* state);
  void RewriteNumPadKeys(const ui::KeyEvent& event, MutableKeyState* state);
  void RewriteExtendedKeys(const ui::KeyEvent& event, MutableKeyState* state);
  void RewriteFunctionKeys(const ui::KeyEvent& event, MutableKeyState* state);
  void RewriteLocatedEvent(const ui::Event& event, int* flags);
  int RewriteModifierClick(const ui::MouseEvent& event, int* flags);

  // A set of device IDs whose press event has been rewritten.
  // This is to ensure that press and release events are rewritten consistently.
  std::set<int> pressed_device_ids_;

  std::map<int, DeviceType> device_id_to_type_;

  
  
  int last_keyboard_device_id_;

  chromeos::input_method::ImeKeyboard* ime_keyboard_for_testing_;
  const PrefService* pref_service_for_testing_;

  
  
  ash::StickyKeysController* sticky_keys_controller_;

  
  
  
  
  
  int current_diamond_key_modifier_flags_;

  DISALLOW_COPY_AND_ASSIGN(EventRewriter);
};

}  

#endif  
