// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_VIEWS_CONTROLS_TEXTFIELD_TEXTFIELD_MODEL_H_
#define UI_VIEWS_CONTROLS_TEXTFIELD_TEXTFIELD_MODEL_H_

#include <list>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "ui/base/ime/composition_text.h"
#include "ui/gfx/render_text.h"
#include "ui/gfx/text_constants.h"
#include "ui/views/views_export.h"

namespace views {

namespace internal {
class Edit;

enum MergeType {
  
  DO_NOT_MERGE,
  
  MERGEABLE,
  
  FORCE_MERGE,
};

}  

class VIEWS_EXPORT TextfieldModel {
 public:
  
  
  class VIEWS_EXPORT Delegate {
   public:
    
    virtual void OnCompositionTextConfirmedOrCleared() = 0;

   protected:
    virtual ~Delegate();
  };

  explicit TextfieldModel(Delegate* delegate);
  virtual ~TextfieldModel();

  

  const base::string16& text() const { return render_text_->text(); }
  
  
  
  
  
  bool SetText(const base::string16& new_text);

  gfx::RenderText* render_text() { return render_text_.get(); }

  
  
  void InsertText(const base::string16& new_text) {
    InsertTextInternal(new_text, false);
  }

  
  void InsertChar(base::char16 c) {
    InsertTextInternal(base::string16(&c, 1), true);
  }

  
  
  void ReplaceText(const base::string16& new_text) {
    ReplaceTextInternal(new_text, false);
  }

  
  void ReplaceChar(base::char16 c) {
    ReplaceTextInternal(base::string16(&c, 1), true);
  }

  
  
  void Append(const base::string16& new_text);

  
  
  
  
  bool Delete();

  
  
  
  
  bool Backspace();

  

  
  size_t GetCursorPosition() const;

  
  
  void MoveCursor(gfx::BreakType break_type,
                  gfx::VisualCursorDirection direction,
                  bool select);

  
  
  bool MoveCursorTo(const gfx::SelectionModel& cursor);

  
  bool MoveCursorTo(const gfx::Point& point, bool select);

  

  
  base::string16 GetSelectedText() const;

  
  
  
  void SelectRange(const gfx::Range& range);

  
  
  void SelectSelectionModel(const gfx::SelectionModel& sel);

  
  
  
  
  void SelectAll(bool reversed);

  
  
  
  
  void SelectWord();

  
  
  void ClearSelection();

  
  bool CanUndo();

  
  bool CanRedo();

  
  bool Undo();

  
  bool Redo();

  
  
  bool Cut();

  
  
  bool Copy();

  
  
  bool Paste();

  
  
  bool HasSelection() const;

  
  
  void DeleteSelection();

  
  void DeleteSelectionAndInsertTextAt(const base::string16& new_text,
                                      size_t position);

  
  base::string16 GetTextFromRange(const gfx::Range& range) const;

  
  void GetTextRange(gfx::Range* range) const;

  
  
  
  
  
  
  void SetCompositionText(const ui::CompositionText& composition);

  
  void ConfirmCompositionText();

  
  void CancelCompositionText();

  
  void GetCompositionTextRange(gfx::Range* range) const;

  
  bool HasCompositionText() const;

  
  void ClearEditHistory();

 private:
  friend class internal::Edit;

  FRIEND_TEST_ALL_PREFIXES(TextfieldModelTest, UndoRedo_BasicTest);
  FRIEND_TEST_ALL_PREFIXES(TextfieldModelTest, UndoRedo_CutCopyPasteTest);
  FRIEND_TEST_ALL_PREFIXES(TextfieldModelTest, UndoRedo_ReplaceTest);

  
  
  void InsertTextInternal(const base::string16& new_text, bool mergeable);

  
  
  void ReplaceTextInternal(const base::string16& new_text, bool mergeable);

  
  void ClearRedoHistory();

  
  void ExecuteAndRecordDelete(gfx::Range range, bool mergeable);
  void ExecuteAndRecordReplaceSelection(internal::MergeType merge_type,
                                        const base::string16& new_text);
  void ExecuteAndRecordReplace(internal::MergeType merge_type,
                               size_t old_cursor_pos,
                               size_t new_cursor_pos,
                               const base::string16& new_text,
                               size_t new_text_start);
  void ExecuteAndRecordInsert(const base::string16& new_text, bool mergeable);

  
  
  bool AddOrMergeEditHistory(internal::Edit* edit);

  
  
  
  
  
  void ModifyText(size_t delete_from,
                  size_t delete_to,
                  const base::string16& new_text,
                  size_t new_text_insert_at,
                  size_t new_cursor_pos);

  void ClearComposition();

  
  Delegate* delegate_;

  
  scoped_ptr<gfx::RenderText> render_text_;

  typedef std::list<internal::Edit*> EditHistory;
  EditHistory edit_history_;

  
  
  
  
  
  
  
  
  
  
  
  
  EditHistory::iterator current_edit_;

  DISALLOW_COPY_AND_ASSIGN(TextfieldModel);
};

}  

#endif  
