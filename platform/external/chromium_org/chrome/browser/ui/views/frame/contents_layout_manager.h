// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_FRAME_CONTENTS_LAYOUT_MANAGER_H_
#define CHROME_BROWSER_UI_VIEWS_FRAME_CONTENTS_LAYOUT_MANAGER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/browser/devtools/devtools_contents_resizing_strategy.h"
#include "ui/views/layout/layout_manager.h"

class ContentsLayoutManager : public views::LayoutManager {
 public:
  ContentsLayoutManager(views::View* devtools_view, views::View* contents_view);
  virtual ~ContentsLayoutManager();

  
  
  void SetActiveTopMargin(int margin);

  
  void SetContentsResizingStrategy(
      const DevToolsContentsResizingStrategy& strategy);

  
  virtual void Layout(views::View* host) OVERRIDE;
  virtual gfx::Size GetPreferredSize(const views::View* host) const OVERRIDE;
  virtual void Installed(views::View* host) OVERRIDE;
  virtual void Uninstalled(views::View* host) OVERRIDE;

 private:
  views::View* devtools_view_;
  views::View* contents_view_;

  views::View* host_;

  DevToolsContentsResizingStrategy strategy_;
  int active_top_margin_;

  DISALLOW_COPY_AND_ASSIGN(ContentsLayoutManager);
};

#endif  
