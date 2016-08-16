// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_LANGUAGE_STATE_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_LANGUAGE_STATE_H_

#include <string>

#include "base/basictypes.h"

namespace translate {

class TranslateDriver;

class LanguageState {
 public:
  explicit LanguageState(TranslateDriver* driver);
  ~LanguageState();

  
  
  void DidNavigate(bool in_page_navigation, bool is_main_frame, bool reload);

  
  
  
  void LanguageDetermined(const std::string& page_language,
                          bool page_needs_translation);

  
  
  
  
  std::string AutoTranslateTo() const;

  
  bool InTranslateNavigation() const;

  
  bool IsPageTranslated() const { return original_lang_ != current_lang_; }

  const std::string& original_language() const { return original_lang_; }

  void SetCurrentLanguage(const std::string& language);
  const std::string& current_language() const { return current_lang_; }

  bool page_needs_translation() const { return page_needs_translation_; }

  
  bool translation_pending() const { return translation_pending_; }
  void set_translation_pending(bool value) { translation_pending_ = value; }

  
  bool translation_declined() const { return translation_declined_; }
  void set_translation_declined(bool value) { translation_declined_ = value; }

  
  
  bool in_page_navigation() const { return in_page_navigation_; }

  
  bool translate_enabled() const { return translate_enabled_; }
  void SetTranslateEnabled(bool value);

  
  
  bool HasLanguageChanged() const;

 private:
  void SetIsPageTranslated(bool value);

  
  bool is_page_translated_;

  
  
  
  
  std::string original_lang_;
  std::string current_lang_;

  
  std::string prev_original_lang_;
  std::string prev_current_lang_;

  
  
  TranslateDriver* translate_driver_;

  
  
  
  bool page_needs_translation_;

  
  
  
  
  
  
  bool translation_pending_;

  
  
  
  bool translation_declined_;

  
  bool in_page_navigation_;

  
  bool translate_enabled_;

  DISALLOW_COPY_AND_ASSIGN(LanguageState);
};

}  

#endif  
