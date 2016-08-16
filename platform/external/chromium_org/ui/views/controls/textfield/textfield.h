// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_TEXTFIELD_TEXTFIELD_H_
#define UI_VIEWS_CONTROLS_TEXTFIELD_TEXTFIELD_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/base/ime/text_input_client.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/base/models/simple_menu_model.h"
#include "ui/base/touch/touch_editing_controller.h"
#include "ui/events/keycodes/keyboard_codes.h"
#include "ui/gfx/font_list.h"
#include "ui/gfx/range/range.h"
#include "ui/gfx/selection_model.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/context_menu_controller.h"
#include "ui/views/controls/textfield/textfield_model.h"
#include "ui/views/drag_controller.h"
#include "ui/views/view.h"

namespace views {

class MenuRunner;
class Painter;
class TextfieldController;

class VIEWS_EXPORT Textfield : public View,
                               public TextfieldModel::Delegate,
                               public ContextMenuController,
                               public DragController,
                               public ui::TouchEditable,
                               public ui::TextInputClient {
 public:
  
  static const char kViewClassName[];

  
  static const int kTextPadding;

  
  static size_t GetCaretBlinkMs();

  Textfield();
  virtual ~Textfield();

  
  void set_controller(TextfieldController* controller) {
    controller_ = controller;
  }

  
  bool read_only() const { return read_only_; }
  void SetReadOnly(bool read_only);

  
  void SetTextInputType(ui::TextInputType type);

  
  const base::string16& text() const { return model_->text(); }

  
  
  
  
  void SetText(const base::string16& new_text);

  
  void AppendText(const base::string16& new_text);

  
  void InsertOrReplaceText(const base::string16& new_text);

  
  base::i18n::TextDirection GetTextDirection() const;

  
  base::string16 GetSelectedText() const;

  
  
  
  void SelectAll(bool reversed);

  
  void SelectWordAt(const gfx::Point& point);

  
  void ClearSelection();

  
  bool HasSelection() const;

  
  
  SkColor GetTextColor() const;
  void SetTextColor(SkColor color);
  void UseDefaultTextColor();

  
  
  SkColor GetBackgroundColor() const;
  void SetBackgroundColor(SkColor color);
  void UseDefaultBackgroundColor();

  
  
  SkColor GetSelectionTextColor() const;
  void SetSelectionTextColor(SkColor color);
  void UseDefaultSelectionTextColor();

  
  
  
  SkColor GetSelectionBackgroundColor() const;
  void SetSelectionBackgroundColor(SkColor color);
  void UseDefaultSelectionBackgroundColor();

  
  void SetShadows(const gfx::ShadowValues& shadows);

  
  bool GetCursorEnabled() const;
  void SetCursorEnabled(bool enabled);

  
  const gfx::FontList& GetFontList() const;
  void SetFontList(const gfx::FontList& font_list);

  
  void set_default_width_in_chars(int default_width) {
    default_width_in_chars_ = default_width;
  }

  
  void set_placeholder_text(const base::string16& text) {
    placeholder_text_ = text;
  }
  virtual base::string16 GetPlaceholderText() const;

  SkColor placeholder_text_color() const { return placeholder_text_color_; }
  void set_placeholder_text_color(SkColor color) {
    placeholder_text_color_ = color;
  }

  
  
  gfx::HorizontalAlignment GetHorizontalAlignment() const;
  void SetHorizontalAlignment(gfx::HorizontalAlignment alignment);

  
  void ShowImeIfNeeded();

  
  bool IsIMEComposing() const;

  
  const gfx::Range& GetSelectedRange() const;

  
  void SelectRange(const gfx::Range& range);

  
  const gfx::SelectionModel& GetSelectionModel() const;

  
  void SelectSelectionModel(const gfx::SelectionModel& sel);

  
  size_t GetCursorPosition() const;

  
  
  void SetColor(SkColor value);
  void ApplyColor(SkColor value, const gfx::Range& range);

  
  
  
  void SetStyle(gfx::TextStyle style, bool value);
  void ApplyStyle(gfx::TextStyle style, bool value, const gfx::Range& range);

  
  void ClearEditHistory();

  
  void SetAccessibleName(const base::string16& name);

  
  void ExecuteCommand(int command_id);

  void SetFocusPainter(scoped_ptr<Painter> focus_painter);

  
  bool HasTextBeingDragged();

  
  virtual gfx::Insets GetInsets() const OVERRIDE;
  virtual int GetBaseline() const OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual const char* GetClassName() const OVERRIDE;
  virtual gfx::NativeCursor GetCursor(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnMousePressed(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnMouseDragged(const ui::MouseEvent& event) OVERRIDE;
  virtual void OnMouseReleased(const ui::MouseEvent& event) OVERRIDE;
  virtual bool OnKeyPressed(const ui::KeyEvent& event) OVERRIDE;
  virtual ui::TextInputClient* GetTextInputClient() OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;
  virtual void AboutToRequestFocusFromTabTraversal(bool reverse) OVERRIDE;
  virtual bool SkipDefaultKeyEventProcessing(
      const ui::KeyEvent& event) OVERRIDE;
  virtual bool GetDropFormats(
      int* formats,
      std::set<ui::OSExchangeData::CustomFormat>* custom_formats) OVERRIDE;
  virtual bool CanDrop(const ui::OSExchangeData& data) OVERRIDE;
  virtual int OnDragUpdated(const ui::DropTargetEvent& event) OVERRIDE;
  virtual void OnDragExited() OVERRIDE;
  virtual int OnPerformDrop(const ui::DropTargetEvent& event) OVERRIDE;
  virtual void OnDragDone() OVERRIDE;
  virtual void GetAccessibleState(ui::AXViewState* state) OVERRIDE;
  virtual void OnBoundsChanged(const gfx::Rect& previous_bounds) OVERRIDE;
  virtual bool GetNeedsNotificationWhenVisibleBoundsChange() const OVERRIDE;
  virtual void OnVisibleBoundsChanged() OVERRIDE;
  virtual void OnEnabledChanged() OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;
  virtual gfx::Point GetKeyboardContextMenuLocation() OVERRIDE;
  virtual void OnNativeThemeChanged(const ui::NativeTheme* theme) OVERRIDE;

  
  virtual void OnCompositionTextConfirmedOrCleared() OVERRIDE;

  
  virtual void ShowContextMenuForView(View* source,
                                      const gfx::Point& point,
                                      ui::MenuSourceType source_type) OVERRIDE;

  
  virtual void WriteDragDataForView(View* sender,
                                    const gfx::Point& press_pt,
                                    ui::OSExchangeData* data) OVERRIDE;
  virtual int GetDragOperationsForView(View* sender,
                                       const gfx::Point& p) OVERRIDE;
  virtual bool CanStartDragForView(View* sender,
                                   const gfx::Point& press_pt,
                                   const gfx::Point& p) OVERRIDE;

  
  virtual void SelectRect(const gfx::Point& start,
                          const gfx::Point& end) OVERRIDE;
  virtual void MoveCaretTo(const gfx::Point& point) OVERRIDE;
  virtual void GetSelectionEndPoints(gfx::Rect* p1, gfx::Rect* p2) OVERRIDE;
  virtual gfx::Rect GetBounds() OVERRIDE;
  virtual gfx::NativeView GetNativeView() const OVERRIDE;
  virtual void ConvertPointToScreen(gfx::Point* point) OVERRIDE;
  virtual void ConvertPointFromScreen(gfx::Point* point) OVERRIDE;
  virtual bool DrawsHandles() OVERRIDE;
  virtual void OpenContextMenu(const gfx::Point& anchor) OVERRIDE;
  virtual void DestroyTouchSelection() OVERRIDE;

  
  virtual bool IsCommandIdChecked(int command_id) const OVERRIDE;
  virtual bool IsCommandIdEnabled(int command_id) const OVERRIDE;
  virtual bool GetAcceleratorForCommandId(
      int command_id,
      ui::Accelerator* accelerator) OVERRIDE;
  virtual void ExecuteCommand(int command_id, int event_flags) OVERRIDE;

  
  virtual void SetCompositionText(
      const ui::CompositionText& composition) OVERRIDE;
  virtual void ConfirmCompositionText() OVERRIDE;
  virtual void ClearCompositionText() OVERRIDE;
  virtual void InsertText(const base::string16& text) OVERRIDE;
  virtual void InsertChar(base::char16 ch, int flags) OVERRIDE;
  virtual gfx::NativeWindow GetAttachedWindow() const OVERRIDE;
  virtual ui::TextInputType GetTextInputType() const OVERRIDE;
  virtual ui::TextInputMode GetTextInputMode() const OVERRIDE;
  virtual bool CanComposeInline() const OVERRIDE;
  virtual gfx::Rect GetCaretBounds() const OVERRIDE;
  virtual bool GetCompositionCharacterBounds(uint32 index,
                                             gfx::Rect* rect) const OVERRIDE;
  virtual bool HasCompositionText() const OVERRIDE;
  virtual bool GetTextRange(gfx::Range* range) const OVERRIDE;
  virtual bool GetCompositionTextRange(gfx::Range* range) const OVERRIDE;
  virtual bool GetSelectionRange(gfx::Range* range) const OVERRIDE;
  virtual bool SetSelectionRange(const gfx::Range& range) OVERRIDE;
  virtual bool DeleteRange(const gfx::Range& range) OVERRIDE;
  virtual bool GetTextFromRange(const gfx::Range& range,
                                base::string16* text) const OVERRIDE;
  virtual void OnInputMethodChanged() OVERRIDE;
  virtual bool ChangeTextDirectionAndLayoutAlignment(
      base::i18n::TextDirection direction) OVERRIDE;
  virtual void ExtendSelectionAndDelete(size_t before, size_t after) OVERRIDE;
  virtual void EnsureCaretInRect(const gfx::Rect& rect) OVERRIDE;
  virtual void OnCandidateWindowShown() OVERRIDE;
  virtual void OnCandidateWindowUpdated() OVERRIDE;
  virtual void OnCandidateWindowHidden() OVERRIDE;
  virtual bool IsEditingCommandEnabled(int command_id) OVERRIDE;
  virtual void ExecuteEditingCommand(int command_id) OVERRIDE;

 protected:
  
  gfx::RenderText* GetRenderText() const;

  gfx::Point last_click_location() const { return last_click_location_; }

  
  virtual base::string16 GetSelectionClipboardText() const;

 private:
  friend class TextfieldTestApi;

  
  
  
  void AccessibilitySetValue(const base::string16& new_value);

  
  void UpdateBackgroundColor();

  
  void UpdateAfterChange(bool text_changed, bool cursor_changed);

  
  void UpdateCursor();

  
  void RepaintCursor();

  void PaintTextAndCursor(gfx::Canvas* canvas);

  
  void MoveCursorTo(const gfx::Point& point, bool select);

  
  void SelectThroughLastDragLocation();

  
  void OnCaretBoundsChanged();

  
  void OnBeforeUserAction();

  
  void OnAfterUserAction();

  
  bool Cut();

  
  bool Copy();

  
  
  bool Paste();

  
  void UpdateContextMenu();

  
  void TrackMouseClicks(const ui::MouseEvent& event);

  
  bool ImeEditingAllowed() const;

  
  
  void RevealPasswordChar(int index);

  void CreateTouchSelectionControllerAndNotifyIt();

  
  void UpdateSelectionClipboard() const;

  
  void PasteSelectionClipboard(const ui::MouseEvent& event);

  
  scoped_ptr<TextfieldModel> model_;

  
  TextfieldController* controller_;

  
  bool read_only_;

  
  
  int default_width_in_chars_;

  scoped_ptr<Painter> focus_painter_;

  
  
  bool use_default_text_color_;
  bool use_default_background_color_;
  bool use_default_selection_text_color_;
  bool use_default_selection_background_color_;
  SkColor text_color_;
  SkColor background_color_;
  SkColor selection_text_color_;
  SkColor selection_background_color_;

  
  base::string16 placeholder_text_;

  
  SkColor placeholder_text_color_;

  
  base::string16 accessible_name_;

  
  ui::TextInputType text_input_type_;

  
  base::TimeDelta password_reveal_duration_;
  base::OneShotTimer<Textfield> password_reveal_timer_;

  
  
  bool performing_user_action_;

  
  bool skip_input_method_cancel_composition_;

  
  base::RepeatingTimer<Textfield> cursor_repaint_timer_;
  bool cursor_visible_;

  
  bool drop_cursor_visible_;
  gfx::SelectionModel drop_cursor_position_;

  
  bool initiating_drag_;

  
  base::RepeatingTimer<Textfield> drag_selection_timer_;
  gfx::Point last_drag_location_;

  
  size_t aggregated_clicks_;
  base::TimeDelta last_click_time_;
  gfx::Point last_click_location_;
  gfx::Range double_click_word_;

  scoped_ptr<ui::TouchSelectionController> touch_selection_controller_;

  
  
  gfx::Point drag_start_location_;
  int drag_start_display_offset_;

  
  
  bool touch_handles_hidden_due_to_scroll_;

  
  scoped_ptr<ui::SimpleMenuModel> context_menu_contents_;
  scoped_ptr<views::MenuRunner> context_menu_runner_;

  
  base::WeakPtrFactory<Textfield> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(Textfield);
};

}  

#endif  
