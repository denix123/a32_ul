// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_CHROMEOS_IME_BRIDGE_H_
#define UI_BASE_IME_CHROMEOS_IME_BRIDGE_H_

#include <string>
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/strings/string16.h"
#include "ui/base/ime/text_input_mode.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/base/ui_base_export.h"

namespace gfx {
class Rect;
}  

namespace ui {
class CandidateWindow;
class KeyEvent;
}  

namespace chromeos {

class CompositionText;

class UI_BASE_EXPORT IMEInputContextHandlerInterface {
 public:
  
  virtual void CommitText(const std::string& text) = 0;

  
  virtual void UpdateCompositionText(const CompositionText& text,
                                     uint32 cursor_pos,
                                     bool visible) = 0;

  
  virtual void DeleteSurroundingText(int32 offset, uint32 length) = 0;
};


class UI_BASE_EXPORT IMEEngineHandlerInterface {
 public:
  typedef base::Callback<void (bool consumed)> KeyEventDoneCallback;

  
  
  
  struct InputContext {
    InputContext(ui::TextInputType type_, ui::TextInputMode mode_) :
      type(type_), mode(mode_) {}

    
    
    ui::TextInputType type;
    
    
    
    
    ui::TextInputMode mode;
  };

  virtual ~IMEEngineHandlerInterface() {}

  
  virtual void FocusIn(const InputContext& input_context) = 0;

  
  virtual void FocusOut() = 0;

  
  virtual void Enable(const std::string& component_id) = 0;

  
  virtual void Disable() = 0;

  
  virtual void PropertyActivate(const std::string& property_name) = 0;

  
  virtual void Reset() = 0;

  
  
  virtual void ProcessKeyEvent(const ui::KeyEvent& key_event,
                               const KeyEventDoneCallback& callback) = 0;

  
  
  virtual void CandidateClicked(uint32 index) = 0;

  
  
  
  
  virtual void SetSurroundingText(const std::string& text, uint32 cursor_pos,
                                  uint32 anchor_pos) = 0;

 protected:
  IMEEngineHandlerInterface() {}
};

class UI_BASE_EXPORT IMECandidateWindowHandlerInterface {
 public:
  virtual ~IMECandidateWindowHandlerInterface() {}

  
  virtual void UpdateLookupTable(const ui::CandidateWindow& candidate_window,
                                 bool visible) = 0;

  
  
  virtual void UpdatePreeditText(const base::string16& text,
                                 uint32 cursor_pos,
                                 bool visible) = 0;

  
  virtual void SetCursorBounds(const gfx::Rect& cursor_bounds,
                               const gfx::Rect& composition_head) = 0;

  
  
  virtual void FocusStateChanged(bool is_focused) {}

 protected:
  IMECandidateWindowHandlerInterface() {}
};


class UI_BASE_EXPORT IMEBridge {
 public:
  virtual ~IMEBridge();

  
  static void Initialize();

  
  static void Shutdown();

  
  static IMEBridge* Get();

  
  
  virtual IMEInputContextHandlerInterface* GetInputContextHandler() const = 0;

  
  
  virtual void SetInputContextHandler(
      IMEInputContextHandlerInterface* handler) = 0;

  
  
  virtual void SetCurrentEngineHandler(IMEEngineHandlerInterface* handler) = 0;

  
  
  virtual IMEEngineHandlerInterface* GetCurrentEngineHandler() const = 0;

  
  
  virtual IMECandidateWindowHandlerInterface* GetCandidateWindowHandler()
      const = 0;

  
  
  virtual void SetCandidateWindowHandler(
      IMECandidateWindowHandlerInterface* handler) = 0;

  
  virtual void SetCurrentTextInputType(ui::TextInputType input_type) = 0;

  
  virtual ui::TextInputType GetCurrentTextInputType() const = 0;

 protected:
  IMEBridge();

 private:
  DISALLOW_COPY_AND_ASSIGN(IMEBridge);
};

}  

#endif  
