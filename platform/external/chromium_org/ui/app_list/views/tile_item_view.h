// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_APP_LIST_VIEWS_TILE_ITEM_VIEW_H_
#define UI_APP_LIST_VIEWS_TILE_ITEM_VIEW_H_

#include "ui/app_list/app_list_export.h"
#include "ui/app_list/search_result_observer.h"
#include "ui/views/controls/button/button.h"
#include "ui/views/controls/button/custom_button.h"

namespace views {
class ImageView;
class Label;
}

namespace app_list {

class SearchResult;

class APP_LIST_EXPORT TileItemView : public views::CustomButton,
                                     public views::ButtonListener,
                                     public SearchResultObserver {
 public:
  TileItemView();
  virtual ~TileItemView();

  void SetSearchResult(SearchResult* item);

 private:
  
  virtual gfx::Size GetPreferredSize() const OVERRIDE;

  
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;

  
  virtual void OnIconChanged() OVERRIDE;
  virtual void OnResultDestroying() OVERRIDE;

  
  SearchResult* item_;

  views::ImageView* icon_;  
  views::Label* title_;     

  DISALLOW_COPY_AND_ASSIGN(TileItemView);
};

}  

#endif  
