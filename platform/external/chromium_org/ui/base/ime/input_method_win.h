// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_INPUT_METHOD_WIN_H_
#define UI_BASE_IME_INPUT_METHOD_WIN_H_

#include <windows.h>

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/base/ime/input_method_base.h"
#include "ui/base/ime/win/imm32_manager.h"

namespace ui {

class UI_BASE_EXPORT InputMethodWin : public InputMethodBase {
 public:
  InputMethodWin(internal::InputMethodDelegate* delegate,
                 HWND toplevel_window_handle);

  
  virtual void Init(bool focused) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;
  virtual bool OnUntranslatedIMEMessage(const base::NativeEvent& event,
                                        NativeEventResult* result) OVERRIDE;
  virtual bool DispatchKeyEvent(const ui::KeyEvent& event) OVERRIDE;
  virtual void OnTextInputTypeChanged(const TextInputClient* client) OVERRIDE;
  virtual void OnCaretBoundsChanged(const TextInputClient* client) OVERRIDE;
  virtual void CancelComposition(const TextInputClient* client) OVERRIDE;
  virtual void OnInputLocaleChanged() OVERRIDE;
  virtual std::string GetInputLocale() OVERRIDE;
  virtual bool IsActive() OVERRIDE;
  virtual bool IsCandidatePopupOpen() const OVERRIDE;

 protected:
  
  
  
  virtual void OnWillChangeFocusedClient(TextInputClient* focused_before,
                                         TextInputClient* focused) OVERRIDE;
  virtual void OnDidChangeFocusedClient(TextInputClient* focused_before,
                                        TextInputClient* focused) OVERRIDE;

 private:
  
  LRESULT OnChar(HWND window_handle,
                 UINT message,
                 WPARAM wparam,
                 LPARAM lparam,
                 BOOL* handled);

  LRESULT OnImeSetContext(HWND window_handle,
                          UINT message,
                          WPARAM wparam,
                          LPARAM lparam,
                          BOOL* handled);
  LRESULT OnImeStartComposition(HWND window_handle,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam,
                                BOOL* handled);
  LRESULT OnImeComposition(HWND window_handle,
                           UINT message,
                           WPARAM wparam,
                           LPARAM lparam,
                           BOOL* handled);
  LRESULT OnImeEndComposition(HWND window_handle,
                              UINT message,
                              WPARAM wparam,
                              LPARAM lparam,
                              BOOL* handled);
  LRESULT OnImeNotify(UINT message,
                      WPARAM wparam,
                      LPARAM lparam,
                      BOOL* handled);

  
  
  
  LRESULT OnImeRequest(UINT message,
                       WPARAM wparam,
                       LPARAM lparam,
                       BOOL* handled);
  LRESULT OnDocumentFeed(RECONVERTSTRING* reconv);
  LRESULT OnReconvertString(RECONVERTSTRING* reconv);
  LRESULT OnQueryCharPosition(IMECHARPOSITION* char_positon);

  
  
  HWND GetAttachedWindowHandle(const TextInputClient* text_input_client) const;

  
  
  bool IsWindowFocused(const TextInputClient* client) const;

  bool DispatchFabricatedKeyEvent(const ui::KeyEvent& event);

  
  void ConfirmCompositionText();

  
  void UpdateIMEState();

  
  
  ui::IMM32Manager imm32_manager_;

  
  
  const HWND toplevel_window_handle_;

  
  std::string locale_;

  
  
  
  base::i18n::TextDirection pending_requested_direction_;

  
  
  
  
  bool accept_carriage_return_;

  
  bool active_;

  
  bool enabled_;

  
  bool is_candidate_popup_open_;

  
  
  HWND composing_window_handle_;

  DISALLOW_COPY_AND_ASSIGN(InputMethodWin);
};

}  

#endif  
