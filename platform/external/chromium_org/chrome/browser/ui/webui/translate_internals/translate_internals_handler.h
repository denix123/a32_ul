// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_TRANSLATE_INTERNALS_TRANSLATE_INTERNALS_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_TRANSLATE_INTERNALS_TRANSLATE_INTERNALS_HANDLER_H_

#include <string>

#include "base/callback_list.h"
#include "base/memory/scoped_ptr.h"
#include "components/translate/core/browser/translate_language_list.h"
#include "components/translate/core/browser/translate_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "content/public/common/webplugininfo.h"

namespace translate {
struct LanguageDetectionDetails;
struct TranslateErrorDetails;
struct TranslateEventDetails;
}

namespace base {
class DictionaryValue;
class ListValue;
class Value;
}

namespace content {
class NotificationDetails;
class NotificationSource;
}

class TranslateInternalsHandler : public content::WebUIMessageHandler,
                                  public content::NotificationObserver {
 public:
  TranslateInternalsHandler();
  virtual ~TranslateInternalsHandler();

  
  virtual void RegisterMessages() OVERRIDE;

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  void OnTranslateError(const translate::TranslateErrorDetails& details);

  
  virtual void OnTranslateEvent(
      const translate::TranslateEventDetails& details);

  
  
  void OnRemovePrefItem(const base::ListValue* args);

  
  
  
  
  void OnRequestInfo(const base::ListValue* args);

  
  void SendMessageToJs(const std::string& message, const base::Value& value);

  
  void SendPrefsToJs();

  
  void SendSupportedLanguagesToJs();

  
  scoped_ptr<translate::TranslateLanguageList::EventCallbackList::Subscription>
      event_subscription_;

  
  scoped_ptr<
      translate::TranslateManager::TranslateErrorCallbackList::Subscription>
      error_subscription_;

  content::NotificationRegistrar notification_registrar_;

  DISALLOW_COPY_AND_ASSIGN(TranslateInternalsHandler);
};

#endif  
