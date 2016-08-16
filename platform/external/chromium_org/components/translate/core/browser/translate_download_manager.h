// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_DOWNLOAD_MANAGER_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_DOWNLOAD_MANAGER_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "components/translate/core/browser/translate_language_list.h"
#include "components/translate/core/browser/translate_script.h"
#include "net/url_request/url_request_context_getter.h"

template <typename T> struct DefaultSingletonTraits;

class PrefService;

namespace translate {

class TranslateDownloadManager {
 public:
  
  static TranslateDownloadManager* GetInstance();

  
  
  net::URLRequestContextGetter* request_context() {
    return request_context_.get();
  }
  void set_request_context(net::URLRequestContextGetter* context) {
      request_context_ = context;
  }

  
  
  const std::string& application_locale() { return application_locale_; }
  void set_application_locale(const std::string& locale) {
    application_locale_ = locale;
  }

  
  TranslateLanguageList* language_list() { return language_list_.get(); }

  
  TranslateScript* script() { return script_.get(); }

  
  
  
  static void RequestLanguageList(PrefService* prefs);

  
  static void RequestLanguageList();

  
  
  static void GetSupportedLanguages(std::vector<std::string>* languages);

  
  
  static base::Time GetSupportedLanguagesLastUpdated();

  
  
  
  static std::string GetLanguageCode(const std::string& language);

  
  static bool IsSupportedLanguage(const std::string& language);

  
  
  static bool IsAlphaLanguage(const std::string& language);

  
  void Shutdown();

  
  void ClearTranslateScriptForTesting();

  
  void ResetForTesting();

  
  
  
  void SetTranslateScriptExpirationDelay(int delay_ms);

 private:
  friend struct DefaultSingletonTraits<TranslateDownloadManager>;
  TranslateDownloadManager();
  virtual ~TranslateDownloadManager();

  scoped_ptr<TranslateLanguageList> language_list_;

  
  
  scoped_ptr<TranslateScript> script_;

  std::string application_locale_;
  scoped_refptr<net::URLRequestContextGetter> request_context_;
};

}  

#endif  
