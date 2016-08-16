// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_SERVICE_WORKER_SERVICE_WORKER_SCRIPT_CONTEXT_H_
#define CONTENT_RENDERER_SERVICE_WORKER_SERVICE_WORKER_SCRIPT_CONTEXT_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/id_map.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "content/child/webmessageportchannel_impl.h"
#include "content/common/service_worker/service_worker_types.h"
#include "content/renderer/service_worker/service_worker_cache_storage_dispatcher.h"
#include "third_party/WebKit/public/platform/WebMessagePortChannel.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerClientsInfo.h"
#include "third_party/WebKit/public/platform/WebServiceWorkerEventResult.h"

namespace blink {
class WebServiceWorkerContextProxy;
}

namespace IPC {
class Message;
}

namespace content {

class EmbeddedWorkerContextClient;

class ServiceWorkerScriptContext {
 public:
  ServiceWorkerScriptContext(
      EmbeddedWorkerContextClient* embedded_context,
      blink::WebServiceWorkerContextProxy* proxy);
  ~ServiceWorkerScriptContext();

  void OnMessageReceived(const IPC::Message& message);

  void DidHandleActivateEvent(int request_id,
                              blink::WebServiceWorkerEventResult);
  void DidHandleInstallEvent(int request_id,
                             blink::WebServiceWorkerEventResult result);
  void DidHandleFetchEvent(int request_id,
                           ServiceWorkerFetchEventResult result,
                           const ServiceWorkerResponse& response);
  void DidHandleSyncEvent(int request_id);
  void GetClientDocuments(
      blink::WebServiceWorkerClientsCallbacks* callbacks);
  void PostMessageToDocument(
      int client_id,
      const base::string16& message,
      scoped_ptr<blink::WebMessagePortChannelArray> channels);

  
  void Send(IPC::Message* message);

  
  
  int GetRoutingID() const;

  blink::WebServiceWorkerCacheStorage* cache_storage() {
    return cache_storage_dispatcher_.get();
  }

 private:
  typedef IDMap<blink::WebServiceWorkerClientsCallbacks, IDMapOwnPointer>
      ClientsCallbacksMap;


  void OnActivateEvent(int request_id);
  void OnInstallEvent(int request_id, int active_version_id);
  void OnFetchEvent(int request_id, const ServiceWorkerFetchRequest& request);
  void OnSyncEvent(int request_id);
  void OnPushEvent(int request_id, const std::string& data);
  void OnPostMessage(const base::string16& message,
                     const std::vector<int>& sent_message_port_ids,
                     const std::vector<int>& new_routing_ids);
  void OnDidGetClientDocuments(
      int request_id, const std::vector<int>& client_ids);

  scoped_ptr<ServiceWorkerCacheStorageDispatcher> cache_storage_dispatcher_;

  
  EmbeddedWorkerContextClient* embedded_context_;

  
  blink::WebServiceWorkerContextProxy* proxy_;

  
  
  
  int current_request_id_;

  
  ClientsCallbacksMap pending_clients_callbacks_;

  DISALLOW_COPY_AND_ASSIGN(ServiceWorkerScriptContext);
};

}  

#endif  
