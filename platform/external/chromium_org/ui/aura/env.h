// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_ENV_H_
#define UI_AURA_ENV_H_

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/supports_user_data.h"
#include "ui/aura/aura_export.h"
#include "ui/events/event_handler.h"
#include "ui/events/event_target.h"
#include "ui/gfx/point.h"

namespace ui {
class ContextFactory;
class PlatformEventSource;
}
namespace aura {

namespace test {
class EnvTestHelper;
}

class EnvObserver;
class InputStateLookup;
class Window;
class WindowTreeHost;

class AURA_EXPORT Env : public ui::EventTarget, public base::SupportsUserData {
 public:
  
  
  
  
  static void CreateInstance(bool create_event_source);
  static Env* GetInstance();
  static void DeleteInstance();

  void AddObserver(EnvObserver* observer);
  void RemoveObserver(EnvObserver* observer);

  int mouse_button_flags() const { return mouse_button_flags_; }
  void set_mouse_button_flags(int mouse_button_flags) {
    mouse_button_flags_ = mouse_button_flags;
  }
  
  
  bool IsMouseButtonDown() const;

  
  
  const gfx::Point& last_mouse_location() const { return last_mouse_location_; }
  void set_last_mouse_location(const gfx::Point& last_mouse_location) {
    last_mouse_location_ = last_mouse_location;
  }

  
  bool is_touch_down() const { return is_touch_down_; }
  void set_touch_down(bool value) { is_touch_down_ = value; }

  void set_context_factory(ui::ContextFactory* context_factory) {
    context_factory_ = context_factory;
  }
  ui::ContextFactory* context_factory() { return context_factory_; }

 private:
  friend class test::EnvTestHelper;
  friend class Window;
  friend class WindowTreeHost;

  Env();
  virtual ~Env();

  
  void Init(bool create_event_source);

  
  void NotifyWindowInitialized(Window* window);

  
  void NotifyHostInitialized(WindowTreeHost* host);

  
  void NotifyHostActivated(WindowTreeHost* host);

  
  virtual bool CanAcceptEvent(const ui::Event& event) OVERRIDE;
  virtual ui::EventTarget* GetParentTarget() OVERRIDE;
  virtual scoped_ptr<ui::EventTargetIterator> GetChildIterator() const OVERRIDE;
  virtual ui::EventTargeter* GetEventTargeter() OVERRIDE;

  ObserverList<EnvObserver> observers_;

  int mouse_button_flags_;
  
  gfx::Point last_mouse_location_;
  bool is_touch_down_;

  scoped_ptr<InputStateLookup> input_state_lookup_;
  scoped_ptr<ui::PlatformEventSource> event_source_;

  ui::ContextFactory* context_factory_;

  DISALLOW_COPY_AND_ASSIGN(Env);
};

}  

#endif  
