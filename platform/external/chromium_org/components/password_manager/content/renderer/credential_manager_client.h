// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PASSWORD_MANAGER_CONTENT_RENDERER_CREDENTIAL_MANAGER_CLIENT_H_
#define COMPONENTS_PASSWORD_MANAGER_CONTENT_RENDERER_CREDENTIAL_MANAGER_CLIENT_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/id_map.h"
#include "content/public/renderer/render_view_observer.h"
#include "ipc/ipc_listener.h"
#include "third_party/WebKit/public/platform/WebCredentialManagerClient.h"
#include "third_party/WebKit/public/platform/WebVector.h"

namespace blink {
class WebCredential;
class WebURL;
}

namespace content {
class RenderThread;
class RenderView;
}

namespace password_manager {

struct CredentialInfo;

class CredentialManagerClient : public blink::WebCredentialManagerClient,
                                public content::RenderViewObserver {
 public:
  explicit CredentialManagerClient(content::RenderView* render_view);
  virtual ~CredentialManagerClient();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void OnAcknowledgeFailedSignIn(int request_id);
  virtual void OnAcknowledgeSignedIn(int request_id);
  virtual void OnAcknowledgeSignedOut(int request_id);
  virtual void OnSendCredential(int request_id,
                                const CredentialInfo& credential_info);

  
  virtual void dispatchFailedSignIn(
      const blink::WebCredential& credential,
      WebCredentialManagerClient::NotificationCallbacks* callbacks) OVERRIDE;
  virtual void dispatchSignedIn(
      const blink::WebCredential& credential,
      WebCredentialManagerClient::NotificationCallbacks* callbacks) OVERRIDE;
  virtual void dispatchSignedOut(NotificationCallbacks* callbacks) OVERRIDE;
  virtual void dispatchRequest(
      bool zero_click_only,
      const blink::WebVector<blink::WebURL>& federations,
      RequestCallbacks* callbacks) OVERRIDE;

 private:
  typedef IDMap<blink::WebCredentialManagerClient::RequestCallbacks,
                IDMapOwnPointer> RequestCallbacksMap;
  typedef IDMap<blink::WebCredentialManagerClient::NotificationCallbacks,
                IDMapOwnPointer> NotificationCallbacksMap;

  void RespondToNotificationCallback(int request_id,
                                     NotificationCallbacksMap* map);

  
  
  NotificationCallbacksMap failed_sign_in_callbacks_;
  NotificationCallbacksMap signed_in_callbacks_;
  NotificationCallbacksMap signed_out_callbacks_;
  RequestCallbacksMap request_callbacks_;

  DISALLOW_COPY_AND_ASSIGN(CredentialManagerClient);
};

}  

#endif  
