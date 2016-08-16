// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_CLIENT_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_CLIENT_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "components/translate/core/browser/translate_prefs.h"
#include "components/translate/core/browser/translate_step.h"
#include "components/translate/core/common/translate_errors.h"

class GURL;
class PrefService;

namespace infobars {
class InfoBar;
}

namespace translate {

class TranslateAcceptLanguages;
class TranslateDriver;
class TranslateInfoBarDelegate;

class TranslateClient {
 public:
  
  virtual TranslateDriver* GetTranslateDriver() = 0;

  
  virtual PrefService* GetPrefs() = 0;

  
  virtual scoped_ptr<TranslatePrefs> GetTranslatePrefs() = 0;

  
  virtual TranslateAcceptLanguages* GetTranslateAcceptLanguages() = 0;

  
  virtual int GetInfobarIconID() const = 0;

  
  virtual scoped_ptr<infobars::InfoBar> CreateInfoBar(
      scoped_ptr<TranslateInfoBarDelegate> delegate) const = 0;

  
  
  virtual void ShowTranslateUI(translate::TranslateStep step,
                               const std::string source_language,
                               const std::string target_language,
                               TranslateErrors::Type error_type,
                               bool triggered_from_menu) = 0;

  
  virtual bool IsTranslatableURL(const GURL& url) = 0;

  
  
  
  virtual void ShowReportLanguageDetectionErrorUI(const GURL& report_url) = 0;
};

}  

#endif  
