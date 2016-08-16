// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CONTENT_BROWSER_CONTENT_TRANSLATE_DRIVER_H_
#define COMPONENTS_TRANSLATE_CONTENT_BROWSER_CONTENT_TRANSLATE_DRIVER_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "components/translate/core/browser/translate_driver.h"
#include "components/translate/core/common/translate_errors.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {
class NavigationController;
class WebContents;
}

namespace translate {

struct LanguageDetectionDetails;
class TranslateManager;

class ContentTranslateDriver : public TranslateDriver,
                               public content::WebContentsObserver {
 public:

  
  class Observer {
   public:
    
    virtual void OnIsPageTranslatedChanged(content::WebContents* source) {};

    
    virtual void OnTranslateEnabledChanged(content::WebContents* source) {};

    
    virtual void OnLanguageDetermined(
        const translate::LanguageDetectionDetails& details) {};

    
    virtual void OnPageTranslated(
        const std::string& original_lang,
        const std::string& translated_lang,
        translate::TranslateErrors::Type error_type) {};

   protected:
    virtual ~Observer() {}
  };

  ContentTranslateDriver(content::NavigationController* nav_controller);
  virtual ~ContentTranslateDriver();

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void set_translate_max_reload_attempts(int attempts) {
    max_reload_check_attempts_ = attempts;
  }

  
  void set_translate_manager(TranslateManager* manager) {
    translate_manager_ = manager;
  }

  
  void InitiateTranslation(const std::string& page_lang, int attempt);

  
  virtual void OnIsPageTranslatedChanged() OVERRIDE;
  virtual void OnTranslateEnabledChanged() OVERRIDE;
  virtual bool IsLinkNavigation() OVERRIDE;
  virtual void TranslatePage(int page_seq_no,
                             const std::string& translate_script,
                             const std::string& source_lang,
                             const std::string& target_lang) OVERRIDE;
  virtual void RevertTranslation(int page_seq_no) OVERRIDE;
  virtual bool IsOffTheRecord() OVERRIDE;
  virtual const std::string& GetContentsMimeType() OVERRIDE;
  virtual const GURL& GetLastCommittedURL() OVERRIDE;
  virtual const GURL& GetActiveURL() OVERRIDE;
  virtual const GURL& GetVisibleURL() OVERRIDE;
  virtual bool HasCurrentPage() OVERRIDE;
  virtual void OpenUrlInNewTab(const GURL& url) OVERRIDE;

  
  virtual void NavigationEntryCommitted(
      const content::LoadCommittedDetails& load_details) OVERRIDE;
  virtual void DidNavigateAnyFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  void OnTranslateAssignedSequenceNumber(int page_seq_no);
  void OnLanguageDetermined(const LanguageDetectionDetails& details,
                            bool page_needs_translation);
  void OnPageTranslated(const std::string& original_lang,
                        const std::string& translated_lang,
                        TranslateErrors::Type error_type);

 private:
  
  content::NavigationController* navigation_controller_;

  TranslateManager* translate_manager_;

  ObserverList<Observer, true> observer_list_;

  
  int max_reload_check_attempts_;

  base::WeakPtrFactory<ContentTranslateDriver> weak_pointer_factory_;

  DISALLOW_COPY_AND_ASSIGN(ContentTranslateDriver);
};

}  

#endif  
