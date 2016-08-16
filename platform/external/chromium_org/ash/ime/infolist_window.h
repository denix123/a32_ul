// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_IME_INFOLIST_WINDOW_H_
#define ASH_IME_INFOLIST_WINDOW_H_

#include <string>
#include <vector>

#include "ash/ash_export.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "ui/base/ime/infolist_entry.h"
#include "ui/gfx/font_list.h"
#include "ui/views/bubble/bubble_delegate.h"

namespace ash {
namespace ime {

class InfolistEntryView;

class ASH_EXPORT InfolistWindow : public views::BubbleDelegateView {
 public:
  InfolistWindow(views::View* candidate_window,
                 const std::vector<ui::InfolistEntry>& entries);
  virtual ~InfolistWindow();
  void InitWidget();

  
  void Relayout(const std::vector<ui::InfolistEntry>& entries);

  
  void ShowWithDelay();
  void HideWithDelay();

  
  void ShowImmediately();
  void HideImmediately();

 private:
  
  virtual void WindowClosing() OVERRIDE;

  
  std::vector<InfolistEntryView*> entry_views_;

  
  gfx::FontList title_font_list_;

  
  gfx::FontList description_font_list_;

  base::OneShotTimer<views::Widget> show_hide_timer_;

  DISALLOW_COPY_AND_ASSIGN(InfolistWindow);
};

}  
}  

#endif  
