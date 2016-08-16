// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_SEARCH_BUTTON_H_
#define CHROME_BROWSER_UI_VIEWS_LOCATION_BAR_SEARCH_BUTTON_H_

#include "ui/views/controls/button/label_button.h"

class SearchButton : public views::LabelButton {
 public:
  explicit SearchButton(views::ButtonListener* listener);
  virtual ~SearchButton();

  
  
  void UpdateIcon(bool is_search);

 private:
  DISALLOW_COPY_AND_ASSIGN(SearchButton);
};

#endif  
