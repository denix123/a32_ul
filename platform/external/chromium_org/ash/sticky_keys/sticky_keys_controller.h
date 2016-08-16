// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_STICKY_KEYS_STICKY_KEYS_CONTROLLER_H_
#define ASH_STICKY_KEYS_STICKY_KEYS_CONTROLLER_H_

#include "ash/ash_export.h"
#include "ash/sticky_keys/sticky_keys_state.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/event_constants.h"
#include "ui/events/event_handler.h"
#include "ui/events/event_rewriter.h"
#include "ui/events/keycodes/keyboard_codes.h"

namespace ui {
class Event;
class KeyEvent;
class MouseEvent;
}  

namespace aura {
class Window;
}  

namespace ash {

class StickyKeysOverlay;
class StickyKeysHandler;

class ASH_EXPORT StickyKeysController {
 public:
  StickyKeysController();
  virtual ~StickyKeysController();

  
  void Enable(bool enabled);

  void SetModifiersEnabled(bool mod3_enabled, bool altgr_enabled);

  
  
  StickyKeysOverlay* GetOverlayForTest();

  
  
  
  
  // - Returns ui::EVENT_REWRITE_REWRITTEN if the event needs to be modified
  
  
  
  
  
  
  
  ui::EventRewriteStatus RewriteKeyEvent(const ui::KeyEvent& event,
                                         ui::KeyboardCode key_code,
                                         int* flags);

  
  ui::EventRewriteStatus RewriteMouseEvent(const ui::MouseEvent& event,
                                           int* flags);

  
  ui::EventRewriteStatus RewriteScrollEvent(const ui::ScrollEvent& event,
                                            int* flags);

  
  
  
  
  
  
  
  
  ui::EventRewriteStatus NextDispatchEvent(scoped_ptr<ui::Event>* new_event);

 private:
  
  
  
  bool HandleKeyEvent(const ui::KeyEvent& event,
                      ui::KeyboardCode key_code,
                      int* mod_down_flags,
                      bool* released);

  
  
  bool HandleMouseEvent(const ui::MouseEvent& event,
                        int* mod_down_flags,
                        bool* released);

  
  
  bool HandleScrollEvent(const ui::ScrollEvent& event,
                         int* mod_down_flags,
                         bool* released);

  
  void UpdateOverlay();

  
  bool enabled_;

  
  bool mod3_enabled_;

  
  bool altgr_enabled_;

  
  scoped_ptr<StickyKeysHandler> shift_sticky_key_;
  scoped_ptr<StickyKeysHandler> alt_sticky_key_;
  scoped_ptr<StickyKeysHandler> altgr_sticky_key_;
  scoped_ptr<StickyKeysHandler> ctrl_sticky_key_;
  scoped_ptr<StickyKeysHandler> mod3_sticky_key_;

  scoped_ptr<StickyKeysOverlay> overlay_;

  DISALLOW_COPY_AND_ASSIGN(StickyKeysController);
};

class ASH_EXPORT StickyKeysHandler {
 public:
  explicit StickyKeysHandler(ui::EventFlags modifier_flag);
  ~StickyKeysHandler();

  
  
  
  bool HandleKeyEvent(const ui::KeyEvent& event,
                      ui::KeyboardCode key_code,
                      int* mod_down_flags,
                      bool* released);

  
  
  
  bool HandleMouseEvent(const ui::MouseEvent& event,
                        int* mod_down_flags,
                        bool* released);

  
  
  
  bool HandleScrollEvent(const ui::ScrollEvent& event,
                         int* mod_down_flags,
                         bool* released);

  
  
  
  int GetModifierUpEvent(scoped_ptr<ui::Event>* new_event);

  
  StickyKeyState current_state() const { return current_state_; }

 private:
  
  enum KeyEventType {
    TARGET_MODIFIER_DOWN,  
    TARGET_MODIFIER_UP,  
    NORMAL_KEY_DOWN,  
    NORMAL_KEY_UP,  
    OTHER_MODIFIER_DOWN,  
    OTHER_MODIFIER_UP,  
  };

  
  KeyEventType TranslateKeyEvent(ui::EventType type, ui::KeyboardCode key_code);

  
  
  bool HandleDisabledState(const ui::KeyEvent& event,
                           ui::KeyboardCode key_code);

  
  
  bool HandleEnabledState(const ui::KeyEvent& event,
                          ui::KeyboardCode key_code,
                          int* mod_down_flags,
                          bool* released);

  
  
  bool HandleLockedState(const ui::KeyEvent& event,
                         ui::KeyboardCode key_code,
                         int* mod_down_flags,
                         bool* released);

  
  const ui::EventFlags modifier_flag_;

  
  StickyKeyState current_state_;

  
  
  
  
  bool preparing_to_enable_;

  
  
  
  int scroll_delta_;

  
  scoped_ptr<ui::KeyEvent> modifier_up_event_;

  DISALLOW_COPY_AND_ASSIGN(StickyKeysHandler);
};

}  

#endif  
