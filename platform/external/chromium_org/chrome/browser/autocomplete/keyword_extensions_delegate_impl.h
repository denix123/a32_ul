// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_AUTOCOMPLETE_KEYWORD_EXTENSIONS_DELEGATE_IMPL_H_
#define CHROME_BROWSER_AUTOCOMPLETE_KEYWORD_EXTENSIONS_DELEGATE_IMPL_H_

#include <vector>

#include "base/compiler_specific.h"
#include "components/omnibox/autocomplete_input.h"
#include "components/omnibox/autocomplete_match.h"
#include "components/omnibox/autocomplete_provider_listener.h"
#include "components/omnibox/keyword_extensions_delegate.h"
#include "components/omnibox/keyword_provider.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

#if !defined(ENABLE_EXTENSIONS)
#error "Should not be included when extensions are disabled"
#endif

class Profile;

class KeywordExtensionsDelegateImpl : public KeywordExtensionsDelegate,
                                      public content::NotificationObserver {
 public:
  KeywordExtensionsDelegateImpl(Profile* profile, KeywordProvider* provider);
  virtual ~KeywordExtensionsDelegateImpl();

 private:
  
  virtual void IncrementInputId() OVERRIDE;
  virtual bool IsEnabledExtension(const std::string& extension_id) OVERRIDE;
  virtual bool Start(const AutocompleteInput& input,
                     bool minimal_changes,
                     const TemplateURL* template_url,
                     const base::string16& remaining_input) OVERRIDE;
  virtual void EnterExtensionKeywordMode(
      const std::string& extension_id) OVERRIDE;
  virtual void MaybeEndExtensionKeywordMode() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  ACMatches* matches() { return &provider_->matches_; }
  void set_done(bool done) {
    provider_->done_ = done;
  }

  
  void OnProviderUpdate(bool updated_matches);

  
  
  
  int current_input_id_;

  
  
  AutocompleteInput extension_suggest_last_input_;

  
  
  std::vector<AutocompleteMatch> extension_suggest_matches_;

  
  
  std::string current_keyword_extension_id_;

  Profile* profile_;

  
  KeywordProvider* provider_;

  content::NotificationRegistrar registrar_;

  
  
  static int global_input_uid_;

  DISALLOW_COPY_AND_ASSIGN(KeywordExtensionsDelegateImpl);
};

#endif  
