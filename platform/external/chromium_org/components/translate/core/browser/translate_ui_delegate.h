// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_UI_DELEGATE_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_UI_DELEGATE_H_

#include <string>
#include <vector>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "components/translate/core/common/translate_errors.h"

namespace translate {

class LanguageState;
class TranslateClient;
class TranslateDriver;
class TranslateManager;
class TranslatePrefs;

class TranslateUIDelegate {
 public:
  static const size_t kNoIndex = static_cast<size_t>(-1);

  TranslateUIDelegate(const base::WeakPtr<TranslateManager>& translate_manager,
                      const std::string& original_language,
                      const std::string& target_language);
  virtual ~TranslateUIDelegate();

  
  void OnErrorShown(TranslateErrors::Type error_type);

  
  const LanguageState& GetLanguageState();

  
  size_t GetNumberOfLanguages() const;

  
  size_t GetOriginalLanguageIndex() const;

  
  void UpdateOriginalLanguageIndex(size_t language_index);

  
  size_t GetTargetLanguageIndex() const;

  
  void UpdateTargetLanguageIndex(size_t language_index);

  
  std::string GetLanguageCodeAt(size_t index) const;

  
  base::string16 GetLanguageNameAt(size_t index) const;

  
  std::string GetOriginalLanguageCode() const;

  
  std::string GetTargetLanguageCode() const;

  
  void Translate();

  
  void RevertTranslation();

  
  void TranslationDeclined(bool explicitly_closed);

  
  bool IsLanguageBlocked();

  
  void SetLanguageBlocked(bool value);

  
  bool IsSiteBlacklisted();

  
  void SetSiteBlacklist(bool value);

  
  
  bool ShouldAlwaysTranslate();

  
  
  void SetAlwaysTranslate(bool value);

 private:
  
  
  std::string GetPageHost();

  TranslateDriver* translate_driver_;
  base::WeakPtr<TranslateManager> translate_manager_;

  typedef std::pair<std::string, base::string16> LanguageNamePair;

  
  
  
  
  std::vector<LanguageNamePair> languages_;

  
  size_t original_language_index_;

  
  
  
  
  
  size_t initial_original_language_index_;

  
  size_t target_language_index_;

  
  scoped_ptr<TranslatePrefs> prefs_;

  DISALLOW_COPY_AND_ASSIGN(TranslateUIDelegate);
};

}  

#endif  
