// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_DRIVER_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_DRIVER_H_

#include <string>

class GURL;

namespace translate {

class TranslateDriver {
 public:
  
  virtual bool IsLinkNavigation() = 0;

  
  virtual void OnTranslateEnabledChanged() = 0;

  
  virtual void OnIsPageTranslatedChanged() = 0;

  
  virtual void TranslatePage(int page_seq_no,
                             const std::string& translate_script,
                             const std::string& source_lang,
                             const std::string& target_lang) = 0;

  
  virtual void RevertTranslation(int page_seq_no) = 0;

  
  virtual bool IsOffTheRecord() = 0;

  
  virtual const std::string& GetContentsMimeType() = 0;

  
  
  virtual const GURL& GetLastCommittedURL() = 0;

  
  virtual const GURL& GetActiveURL() = 0;

  
  virtual const GURL& GetVisibleURL() = 0;

  
  virtual bool HasCurrentPage() = 0;

  
  virtual void OpenUrlInNewTab(const GURL& url) = 0;
};

}  

#endif  
