// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_OMNIBOX_OMNIBOX_CURRENT_PAGE_DELEGATE_H_
#define CHROME_BROWSER_UI_OMNIBOX_OMNIBOX_CURRENT_PAGE_DELEGATE_H_

#include "base/basictypes.h"
#include "chrome/common/instant_types.h"
#include "chrome/common/omnibox_focus_state.h"
#include "ui/base/window_open_disposition.h"

class GURL;
class SessionID;
class TemplateURL;
struct AutocompleteMatch;

namespace content {
class NavigationController;
}

class OmniboxCurrentPageDelegate {
 public:
  virtual ~OmniboxCurrentPageDelegate() {}

  
  
  virtual bool CurrentPageExists() const = 0;

  
  virtual const GURL& GetURL() const = 0;

  
  virtual bool IsInstantNTP() const = 0;

  
  virtual bool IsSearchResultsPage() const = 0;

  
  virtual bool IsLoading() const = 0;

  
  virtual content::NavigationController& GetNavigationController() const = 0;

  
  virtual const SessionID& GetSessionID() const = 0;

  
  
  
  virtual bool ProcessExtensionKeyword(TemplateURL* template_url,
                                       const AutocompleteMatch& match,
                                       WindowOpenDisposition disposition) = 0;

  
  virtual void OnInputStateChanged() = 0;

  
  virtual void OnFocusChanged(OmniboxFocusState state,
                              OmniboxFocusChangeReason reason) = 0;

  
  virtual void DoPrerender(const AutocompleteMatch& match) = 0;

  
  virtual void SetSuggestionToPrefetch(const InstantSuggestion& suggestion) = 0;
};

#endif  
