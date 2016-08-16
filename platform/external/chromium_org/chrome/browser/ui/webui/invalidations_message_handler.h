// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_INVALIDATIONS_MESSAGE_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_INVALIDATIONS_MESSAGE_HANDLER_H_

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "components/invalidation/invalidation_logger_observer.h"
#include "components/invalidation/invalidation_util.h"
#include "content/public/browser/web_ui_message_handler.h"

class Profile;

namespace invalidation {
class InvalidationLogger;
}  

namespace syncer {
class InvalidationHandler;
}  

class InvalidationsMessageHandler
    : public content::WebUIMessageHandler,
      public invalidation::InvalidationLoggerObserver {
 public:
  InvalidationsMessageHandler();
  virtual ~InvalidationsMessageHandler();

  
  virtual void OnRegistrationChange(
      const std::multiset<std::string>& registered_handlers) OVERRIDE;
  virtual void OnStateChange(const syncer::InvalidatorState& new_state,
                             const base::Time& last_change_timestamp)
      OVERRIDE;
  virtual void OnUpdateIds(const std::string& handler_name,
                           const syncer::ObjectIdCountMap& ids_set) OVERRIDE;
  virtual void OnDebugMessage(const base::DictionaryValue& details) OVERRIDE;
  virtual void OnInvalidation(
      const syncer::ObjectIdInvalidationMap& new_invalidations) OVERRIDE;
  virtual void OnDetailedStatus(const base::DictionaryValue& network_details)
      OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  
  void UpdateContent(const base::ListValue* args);

  
  void UIReady(const base::ListValue* args);

  
  void HandleRequestDetailedStatus(const base::ListValue* args);

 private:
  
  
  
  invalidation::InvalidationLogger* logger_;

  base::WeakPtrFactory<InvalidationsMessageHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(InvalidationsMessageHandler);
};

#endif  
