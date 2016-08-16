// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TRANSLATE_TRANSLATE_SERVICE_H_
#define CHROME_BROWSER_TRANSLATE_TRANSLATE_SERVICE_H_

#include "chrome/browser/web_resource/resource_request_allowed_notifier.h"

class GURL;
class PrefService;

class TranslateService : public ResourceRequestAllowedNotifier::Observer {
 public:
   
  static void Initialize();

  
  static void Shutdown(bool cleanup_pending_fetcher);

  
  
  
  static void InitializeForTesting();

  
  
  static void ShutdownForTesting();

  
  
  
  static void FetchLanguageListFromTranslateServer(PrefService* prefs);

  
  static bool IsTranslateBubbleEnabled();

  
  
  
  
  
  
  static std::string GetTargetLanguage(PrefService* prefs);

  
  static bool IsTranslatableURL(const GURL& url);

 private:
  TranslateService();
  ~TranslateService();

  
  virtual void OnResourceRequestsAllowed() OVERRIDE;

  
  ResourceRequestAllowedNotifier resource_request_allowed_notifier_;
};

#endif  
