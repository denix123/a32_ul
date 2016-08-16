// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_SYNC_INTERNALS_MESSAGE_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_SYNC_INTERNALS_MESSAGE_HANDLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "base/scoped_observer.h"
#include "base/values.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "chrome/browser/sync/protocol_event_observer.h"
#include "content/public/browser/web_ui_message_handler.h"
#include "sync/internal_api/public/sessions/type_debug_info_observer.h"
#include "sync/js/js_controller.h"
#include "sync/js/js_event_handler.h"

class ProfileSyncService;

class SyncInternalsMessageHandler : public content::WebUIMessageHandler,
                                    public syncer::JsEventHandler,
                                    public ProfileSyncServiceObserver,
                                    public browser_sync::ProtocolEventObserver,
                                    public syncer::TypeDebugInfoObserver {
 public:
  SyncInternalsMessageHandler();
  virtual ~SyncInternalsMessageHandler();

  virtual void RegisterMessages() OVERRIDE;

  
  void HandleRegisterForEvents(const base::ListValue* args);

  
  void HandleRegisterForPerTypeCounters(const base::ListValue* args);

  
  void HandleRequestUpdatedAboutInfo(const base::ListValue* args);

  
  void HandleRequestListOfTypes(const base::ListValue* args);

  
  void HandleGetAllNodes(const base::ListValue* args);

  
  virtual void HandleJsEvent(
      const std::string& name,
      const syncer::JsEventDetails& details) OVERRIDE;

  
  void OnReceivedAllNodes(int request_id, scoped_ptr<base::ListValue> nodes);

  
  virtual void OnStateChanged() OVERRIDE;

  
  virtual void OnProtocolEvent(const syncer::ProtocolEvent& e) OVERRIDE;

  
  virtual void OnCommitCountersUpdated(
      syncer::ModelType type,
      const syncer::CommitCounters& counters) OVERRIDE;
  virtual void OnUpdateCountersUpdated(
      syncer::ModelType type,
      const syncer::UpdateCounters& counters) OVERRIDE;
  virtual void OnStatusCountersUpdated(
      syncer::ModelType type,
      const syncer::StatusCounters& counters) OVERRIDE;

  
  
  
  
  
  void EmitCounterUpdate(syncer::ModelType type,
                         const std::string& counter_type,
                         scoped_ptr<base::DictionaryValue> value);

 private:
  
  
  void SendAboutInfo();

  ProfileSyncService* GetProfileSyncService();

  base::WeakPtr<syncer::JsController> js_controller_;

  
  bool is_registered_;

  
  
  bool is_registered_for_counters_;

  base::WeakPtrFactory<SyncInternalsMessageHandler> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncInternalsMessageHandler);
};

#endif  
