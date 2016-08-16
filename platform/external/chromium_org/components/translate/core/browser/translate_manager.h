// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_MANAGER_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_MANAGER_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback_list.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/translate/core/browser/language_state.h"
#include "components/translate/core/common/translate_errors.h"

class GURL;
class PrefService;

namespace translate {

class TranslateClient;
class TranslateDriver;
class TranslatePrefs;
struct TranslateErrorDetails;


class TranslateManager {
 public:
  
  
  
  TranslateManager(TranslateClient* translate_client,
                   const std::string& accept_language_pref_name);
  virtual ~TranslateManager();

  
  base::WeakPtr<TranslateManager> GetWeakPtr();

  
  TranslateClient* translate_client() { return translate_client_; }

  
  
  void set_current_seq_no(int page_seq_no) { page_seq_no_ = page_seq_no; }

  
  
  
  
  
  
  static std::string GetTargetLanguage(
      const std::vector<std::string>& accept_languages_list);

  
  
  static std::string GetAutoTargetLanguage(const std::string& original_language,
                                           TranslatePrefs* translate_prefs);

  
  
  
  void TranslatePage(const std::string& source_lang,
                     const std::string& target_lang,
                     bool triggered_from_menu);

  
  void InitiateTranslation(const std::string& page_lang);

  
  void PageTranslated(const std::string& source_lang,
                      const std::string& target_lang,
                      TranslateErrors::Type error_type);

  
  void RevertTranslation();

  
  
  
  void ReportLanguageDetectionError();

  
  typedef base::Callback<void(const TranslateErrorDetails&)>
      TranslateErrorCallback;
  typedef base::CallbackList<void(const TranslateErrorDetails&)>
      TranslateErrorCallbackList;

  
  static scoped_ptr<TranslateErrorCallbackList::Subscription>
      RegisterTranslateErrorCallback(const TranslateErrorCallback& callback);

  
  LanguageState& GetLanguageState();

 private:
  
  void DoTranslatePage(const std::string& translate_script,
                       const std::string& source_lang,
                       const std::string& target_lang);

  
  
  void OnTranslateScriptFetchComplete(const std::string& source_lang,
                                      const std::string& target_lang,
                                      bool success,
                                      const std::string& data);

  
  int page_seq_no_;

  
  std::string accept_languages_pref_name_;

  TranslateClient* translate_client_;  
  TranslateDriver* translate_driver_;  

  LanguageState language_state_;

  base::WeakPtrFactory<TranslateManager> weak_method_factory_;

  DISALLOW_COPY_AND_ASSIGN(TranslateManager);
};

}  

#endif  
