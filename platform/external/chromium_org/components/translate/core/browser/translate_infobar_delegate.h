// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_INFOBAR_DELEGATE_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_INFOBAR_DELEGATE_H_

#include <string>
#include <utility>
#include <vector>

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/infobars/core/infobar_delegate.h"
#include "components/translate/core/browser/translate_prefs.h"
#include "components/translate/core/browser/translate_step.h"
#include "components/translate/core/browser/translate_ui_delegate.h"
#include "components/translate/core/common/translate_constants.h"
#include "components/translate/core/common/translate_errors.h"

namespace infobars {
class InfoBarManager;
}

namespace translate {

class TranslateClient;
class TranslateDriver;
class TranslateManager;

class TranslateInfoBarDelegate : public infobars::InfoBarDelegate {
 public:
  
  enum BackgroundAnimationType {
    NONE,
    NORMAL_TO_ERROR,
    ERROR_TO_NORMAL
  };

  static const size_t kNoIndex;

  virtual ~TranslateInfoBarDelegate();

  
  
  
  
  
  
  
  
  
  
  
  
  static void Create(bool replace_existing_infobar,
                     const base::WeakPtr<TranslateManager>& translate_manager,
                     infobars::InfoBarManager* infobar_manager,
                     bool is_off_the_record,
                     translate::TranslateStep step,
                     const std::string& original_language,
                     const std::string& target_language,
                     TranslateErrors::Type error_type,
                     bool triggered_from_menu);

  
  size_t num_languages() const { return ui_delegate_.GetNumberOfLanguages(); }

  
  std::string language_code_at(size_t index) const {
    return ui_delegate_.GetLanguageCodeAt(index);
  }

  
  base::string16 language_name_at(size_t index) const {
    return ui_delegate_.GetLanguageNameAt(index);
  }

  translate::TranslateStep translate_step() const { return step_; }

  bool is_off_the_record() { return is_off_the_record_; }

  TranslateErrors::Type error_type() const { return error_type_; }

  size_t original_language_index() const {
    return ui_delegate_.GetOriginalLanguageIndex();
  }
  void UpdateOriginalLanguageIndex(size_t language_index);

  size_t target_language_index() const {
    return ui_delegate_.GetTargetLanguageIndex();
  }
  void UpdateTargetLanguageIndex(size_t language_index);

  
  std::string original_language_code() const {
    return ui_delegate_.GetOriginalLanguageCode();
  }
  std::string target_language_code() const {
    return ui_delegate_.GetTargetLanguageCode();
  }

  
  
  bool is_error() const {
    return step_ == translate::TRANSLATE_STEP_TRANSLATE_ERROR;
  }

  
  
  bool triggered_from_menu() const {
    return triggered_from_menu_;
  }

  
  
  BackgroundAnimationType background_animation_type() const {
    return background_animation_;
  }

  virtual void Translate();
  virtual void RevertTranslation();
  void ReportLanguageDetectionError();

  
  
  virtual void TranslationDeclined();

  
  virtual bool IsTranslatableLanguageByPrefs();
  virtual void ToggleTranslatableLanguageByPrefs();
  virtual bool IsSiteBlacklisted();
  virtual void ToggleSiteBlacklist();
  virtual bool ShouldAlwaysTranslate();
  virtual void ToggleAlwaysTranslate();

  
  
  
  void AlwaysTranslatePageLanguage();
  void NeverTranslatePageLanguage();

  
  
  base::string16 GetMessageInfoBarText();
  base::string16 GetMessageInfoBarButtonText();
  void MessageInfoBarButtonPressed();
  bool ShouldShowMessageInfoBarButton();

  
  
  
  
  
  bool ShouldShowNeverTranslateShortcut();
  bool ShouldShowAlwaysTranslateShortcut();

  
  
  
  
  
  
  
  
  
  
  
  
  static void GetAfterTranslateStrings(std::vector<base::string16>* strings,
                                       bool* swap_languages,
                                       bool autodetermined_source_language);

  
  
  TranslateDriver* GetTranslateDriver();

 protected:
  TranslateInfoBarDelegate(
      const base::WeakPtr<TranslateManager>& translate_manager,
      bool is_off_the_record,
      translate::TranslateStep step,
      TranslateInfoBarDelegate* old_delegate,
      const std::string& original_language,
      const std::string& target_language,
      TranslateErrors::Type error_type,
      bool triggered_from_menu);

 private:
  friend class TranslationInfoBarTest;
  typedef std::pair<std::string, base::string16> LanguageNamePair;

  
  virtual void InfoBarDismissed() OVERRIDE;
  virtual int GetIconID() const OVERRIDE;
  virtual infobars::InfoBarDelegate::Type GetInfoBarType() const OVERRIDE;
  virtual bool ShouldExpire(const NavigationDetails& details) const OVERRIDE;
  virtual TranslateInfoBarDelegate* AsTranslateInfoBarDelegate() OVERRIDE;

  bool is_off_the_record_;
  translate::TranslateStep step_;

  
  
  BackgroundAnimationType background_animation_;

  TranslateUIDelegate ui_delegate_;
  base::WeakPtr<TranslateManager> translate_manager_;

  
  TranslateErrors::Type error_type_;

  
  scoped_ptr<TranslatePrefs> prefs_;

  
  
  bool triggered_from_menu_;
  DISALLOW_COPY_AND_ASSIGN(TranslateInfoBarDelegate);
};

}  

#endif  
