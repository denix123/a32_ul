// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_ENGINE_H_
#define CHROME_BROWSER_CHROMEOS_INPUT_METHOD_INPUT_METHOD_ENGINE_H_

#include <map>
#include <string>
#include <vector>
#include "base/time/time.h"
#include "chrome/browser/chromeos/input_method/input_method_engine_interface.h"
#include "chromeos/ime/input_method_descriptor.h"
#include "url/gurl.h"

class Profile;

namespace ui {
class CandidateWindow;
class KeyEvent;
}  

namespace ash {
namespace ime {
struct InputMethodMenuItem;
}  
}  

namespace chromeos {

class CompositionText;

namespace input_method {
struct KeyEventHandle;
}  

class InputMethodEngine : public InputMethodEngineInterface {
 public:
  InputMethodEngine();

  virtual ~InputMethodEngine();

  void Initialize(scoped_ptr<InputMethodEngineInterface::Observer> observer,
                  const char* extension_id);

  
  virtual const std::string& GetActiveComponentId() const OVERRIDE;
  virtual bool SetComposition(int context_id,
                              const char* text,
                              int selection_start,
                              int selection_end,
                              int cursor,
                              const std::vector<SegmentInfo>& segments,
                              std::string* error) OVERRIDE;
  virtual bool ClearComposition(int context_id, std::string* error) OVERRIDE;
  virtual bool CommitText(int context_id, const char* text,
                          std::string* error) OVERRIDE;
  virtual bool SendKeyEvents(int context_id,
                             const std::vector<KeyboardEvent>& events) OVERRIDE;
  virtual const CandidateWindowProperty&
    GetCandidateWindowProperty() const OVERRIDE;
  virtual void SetCandidateWindowProperty(
      const CandidateWindowProperty& property) OVERRIDE;
  virtual bool SetCandidateWindowVisible(bool visible,
                                         std::string* error) OVERRIDE;
  virtual bool SetCandidates(int context_id,
                             const std::vector<Candidate>& candidates,
                             std::string* error) OVERRIDE;
  virtual bool SetCursorPosition(int context_id, int candidate_id,
                                 std::string* error) OVERRIDE;
  virtual bool SetMenuItems(const std::vector<MenuItem>& items) OVERRIDE;
  virtual bool UpdateMenuItems(const std::vector<MenuItem>& items) OVERRIDE;
  virtual bool IsActive() const OVERRIDE;
  virtual bool DeleteSurroundingText(int context_id,
                                     int offset,
                                     size_t number_of_chars,
                                     std::string* error) OVERRIDE;

  
  virtual void FocusIn(
      const IMEEngineHandlerInterface::InputContext& input_context) OVERRIDE;
  virtual void FocusOut() OVERRIDE;
  virtual void Enable(const std::string& component_id) OVERRIDE;
  virtual void Disable() OVERRIDE;
  virtual void PropertyActivate(const std::string& property_name) OVERRIDE;
  virtual void Reset() OVERRIDE;
  virtual void ProcessKeyEvent(const ui::KeyEvent& key_event,
                               const KeyEventDoneCallback& callback) OVERRIDE;
  virtual void CandidateClicked(uint32 index) OVERRIDE;
  virtual void SetSurroundingText(const std::string& text, uint32 cursor_pos,
                                  uint32 anchor_pos) OVERRIDE;
  virtual void HideInputView() OVERRIDE;

  int GetCotextIdForTesting() { return context_id_; }

 private:
  
  void MenuItemToProperty(const MenuItem& item,
                          ash::ime::InputMethodMenuItem* property);

  
  void EnableInputView();

  ui::TextInputType current_input_type_;

  
  int context_id_;

  
  int next_context_id_;

  
  std::string active_component_id_;

  
  std::string extension_id_;

  
  scoped_ptr<InputMethodEngineInterface::Observer> observer_;

  
  scoped_ptr<CompositionText> composition_text_;
  int composition_cursor_;

  
  scoped_ptr<ui::CandidateWindow> candidate_window_;

  
  CandidateWindowProperty candidate_window_property_;

  
  bool window_visible_;

  
  std::vector<int> candidate_ids_;

  
  std::map<int, int> candidate_indexes_;

  
  
  const ui::KeyEvent* sent_key_event_;
};

}  

#endif  
