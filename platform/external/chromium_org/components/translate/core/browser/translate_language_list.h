// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_LANGUAGE_LIST_H_
#define COMPONENTS_TRANSLATE_CORE_BROWSER_TRANSLATE_LANGUAGE_LIST_H_

#include <set>
#include <string>
#include <vector>

#include "base/callback_list.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"

class GURL;

namespace translate {

struct TranslateEventDetails;
class TranslateURLFetcher;

class TranslateLanguageList {
 public:
  static const int kFetcherId = 1;

  TranslateLanguageList();
  virtual ~TranslateLanguageList();

  
  
  base::Time last_updated() { return last_updated_; }

  
  
  void GetSupportedLanguages(std::vector<std::string>* languages);

  
  
  
  std::string GetLanguageCode(const std::string& language);

  
  
  bool IsSupportedLanguage(const std::string& language);

  
  
  bool IsAlphaLanguage(const std::string& language);

  
  
  void RequestLanguageList();

  
  
  void SetResourceRequestsAllowed(bool allowed);

  typedef base::Callback<void(const TranslateEventDetails&)> EventCallback;
  typedef base::CallbackList<void(const TranslateEventDetails&)>
      EventCallbackList;

  
  
  scoped_ptr<EventCallbackList::Subscription> RegisterEventCallback(
      const EventCallback& callback);

  
  static void DisableUpdate();

  
  static const char kLanguageListCallbackName[];
  static const char kTargetLanguagesKey[];
  static const char kAlphaLanguagesKey[];

 private:
  
  void OnLanguageListFetchComplete(int id,
                                   bool success,
                                   const std::string& data);

  
  void NotifyEvent(int line, const std::string& message);

  
  
  void SetSupportedLanguages(const std::string& language_list);

  
  GURL TranslateLanguageUrl();

  
  EventCallbackList callback_list_;

  
  bool resource_requests_allowed_;

  
  bool request_pending_;

  
  std::set<std::string> all_supported_languages_;

  
  std::set<std::string> alpha_languages_;

  
  
  scoped_ptr<TranslateURLFetcher> language_list_fetcher_;

  
  base::Time last_updated_;

  DISALLOW_COPY_AND_ASSIGN(TranslateLanguageList);
};

}  

#endif  
