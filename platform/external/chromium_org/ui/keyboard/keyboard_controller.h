// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_KEYBOARD_KEYBOARD_CONTROLLER_H_
#define UI_KEYBOARD_KEYBOARD_CONTROLLER_H_

#include "base/basictypes.h"
#include "base/event_types.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "ui/aura/window_observer.h"
#include "ui/base/ime/input_method_observer.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/gfx/rect.h"
#include "ui/keyboard/keyboard_export.h"
#include "url/gurl.h"

namespace aura {
class Window;
}
namespace ui {
class InputMethod;
class TextInputClient;
}

namespace keyboard {

class CallbackAnimationObserver;
class WindowBoundsChangeObserver;
class KeyboardControllerObserver;
class KeyboardControllerProxy;

const int kAnimationDistance = 30;

class KEYBOARD_EXPORT KeyboardController : public ui::InputMethodObserver,
                                           public aura::WindowObserver {
 public:
  
  enum HideReason {
    
    HIDE_REASON_AUTOMATIC,
    
    HIDE_REASON_MANUAL,
  };

  
  explicit KeyboardController(KeyboardControllerProxy* proxy);
  virtual ~KeyboardController();

  
  
  aura::Window* GetContainerWindow();

  
  bool keyboard_container_initialized() const {
    return container_.get() != NULL;
  }

  
  
  void Reload();

  
  
  
  
  void HideKeyboard(HideReason reason);

  
  void NotifyKeyboardBoundsChanging(const gfx::Rect& new_bounds);

  
  virtual void AddObserver(KeyboardControllerObserver* observer);
  virtual void RemoveObserver(KeyboardControllerObserver* observer);

  KeyboardControllerProxy* proxy() { return proxy_.get(); }

  void set_lock_keyboard(bool lock) { lock_keyboard_ = lock; }

  
  
  void ShowKeyboard(bool lock);

  
  
  
  static void ResetInstance(KeyboardController* controller);

  
  static KeyboardController* GetInstance();

  
  bool keyboard_visible() { return keyboard_visible_; }

  bool show_on_resize() { return show_on_resize_; }

  
  
  const gfx::Rect& current_keyboard_bounds() {
    return current_keyboard_bounds_;
  }

  
  bool ShouldEnableInsets(aura::Window* window);

  
  void UpdateWindowInsets(aura::Window* window);

 private:
  
  friend class KeyboardControllerTest;

  
  virtual void OnWindowHierarchyChanged(
      const HierarchyChangeParams& params) OVERRIDE;

  
  virtual void OnTextInputTypeChanged(
      const ui::TextInputClient* client) OVERRIDE {}
  virtual void OnFocus() OVERRIDE {}
  virtual void OnBlur() OVERRIDE {}
  virtual void OnCaretBoundsChanged(
      const ui::TextInputClient* client) OVERRIDE {}
  virtual void OnTextInputStateChanged(
      const ui::TextInputClient* client) OVERRIDE;
  virtual void OnInputMethodDestroyed(
      const ui::InputMethod* input_method) OVERRIDE;
  virtual void OnShowImeIfNeeded() OVERRIDE;

  
  void ShowKeyboardInternal();

  
  void ResetWindowInsets();

  
  bool WillHideKeyboard() const;

  
  
  void ShowAnimationFinished();
  void HideAnimationFinished();

  
  
  
  void AddBoundsChangedObserver(aura::Window* window);

  scoped_ptr<KeyboardControllerProxy> proxy_;
  scoped_ptr<aura::Window> container_;
  
  
  scoped_ptr<CallbackAnimationObserver> animation_observer_;

  scoped_ptr<WindowBoundsChangeObserver> window_bounds_observer_;

  ui::InputMethod* input_method_;
  bool keyboard_visible_;
  bool show_on_resize_;
  bool lock_keyboard_;
  ui::TextInputType type_;

  ObserverList<KeyboardControllerObserver> observer_list_;

  
  gfx::Rect current_keyboard_bounds_;

  static KeyboardController* instance_;

  base::WeakPtrFactory<KeyboardController> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(KeyboardController);
};

}  

#endif  
