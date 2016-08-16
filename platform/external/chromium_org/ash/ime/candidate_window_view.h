// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_IME_CANDIDATE_WINDOW_VIEW_H_
#define ASH_IME_CANDIDATE_WINDOW_VIEW_H_

#include "ash/ash_export.h"
#include "ui/base/ime/candidate_window.h"
#include "ui/views/bubble/bubble_delegate.h"
#include "ui/views/controls/button/button.h"

namespace ash {
namespace ime {

class CandidateView;
class InformationTextArea;

class ASH_EXPORT CandidateWindowView : public views::BubbleDelegateView,
                                       public views::ButtonListener {
 public:
  
  class Observer {
   public:
    virtual ~Observer() {}
    
    virtual void OnCandidateCommitted(int index) = 0;
  };

  explicit CandidateWindowView(gfx::NativeView parent);
  virtual ~CandidateWindowView();
  views::Widget* InitWidget();

  
  void AddObserver(Observer* observer) {
    observers_.AddObserver(observer);
  }

  
  void RemoveObserver(Observer* observer) {
    observers_.RemoveObserver(observer);
  }

  
  void HideLookupTable();

  
  void HideAuxiliaryText();

  
  void HidePreeditText();

  
  void ShowLookupTable();

  
  void ShowAuxiliaryText();

  
  void ShowPreeditText();

  
  void UpdatePreeditText(const base::string16& text);

  
  
  void UpdateCandidates(const ui::CandidateWindow& candidate_window);

  void SetCursorBounds(const gfx::Rect& cursor_bounds,
                       const gfx::Rect& composition_head);

 private:
  friend class CandidateWindowViewTest;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  void SelectCandidateAt(int index_in_page);
  void UpdateVisibility();

  
  void MaybeInitializeCandidateViews(
      const ui::CandidateWindow& candidate_window);

  
  ui::CandidateWindow candidate_window_;

  
  int selected_candidate_index_in_page_;

  
  ObserverList<Observer> observers_;

  
  
  InformationTextArea* auxiliary_text_;
  InformationTextArea* preedit_;
  views::View* candidate_area_;

  
  std::vector<CandidateView*> candidate_views_;

  
  gfx::Size previous_shortcut_column_size_;
  gfx::Size previous_candidate_column_size_;
  gfx::Size previous_annotation_column_size_;

  
  gfx::Rect cursor_bounds_;

  
  gfx::Rect composition_head_bounds_;

  
  
  bool should_show_at_composition_head_;

  
  
  bool should_show_upper_side_;

  
  
  bool was_candidate_window_open_;

  DISALLOW_COPY_AND_ASSIGN(CandidateWindowView);
};

}  
}  

#endif  
