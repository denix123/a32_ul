// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_SEARCH_SEARCH_TAB_HELPER_DELEGATE_H_
#define CHROME_BROWSER_UI_SEARCH_SEARCH_TAB_HELPER_DELEGATE_H_

#include <set>
#include <string>

#include "ui/base/window_open_disposition.h"

namespace content {
class WebContents;
}

class GURL;
class OmniboxView;

class SearchTabHelperDelegate {
 public:
  
  
  
  
  
  
  
  
  virtual void NavigateOnThumbnailClick(const GURL& url,
                                        WindowOpenDisposition disposition,
                                        content::WebContents* source_contents);

  
  virtual void OnWebContentsInstantSupportDisabled(
      const content::WebContents* web_contents);

  
  virtual OmniboxView* GetOmniboxView();

  
  virtual std::set<std::string> GetOpenUrls();

 protected:
  virtual ~SearchTabHelperDelegate();
};

#endif  
