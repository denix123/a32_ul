// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_HOST_DELEGATE_H_
#define CONTENT_BROWSER_FRAME_HOST_RENDER_FRAME_HOST_DELEGATE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/i18n/rtl.h"
#include "content/common/content_export.h"
#include "content/common/frame_message_enums.h"
#include "content/public/common/javascript_message_type.h"
#include "content/public/common/media_stream_request.h"
#include "net/http/http_response_headers.h"

#if defined(OS_WIN)
#include "ui/gfx/native_widget_types.h"
#endif

class GURL;

namespace IPC {
class Message;
}

namespace content {
class RenderFrameHost;
class WebContents;
struct AXEventNotificationDetails;
struct ContextMenuParams;
struct TransitionLayerData;

class CONTENT_EXPORT RenderFrameHostDelegate {
 public:
  
  virtual bool OnMessageReceived(RenderFrameHost* render_frame_host,
                                 const IPC::Message& message);

  
  
  virtual const GURL& GetMainFrameLastCommittedURL() const;

  
  virtual bool AddMessageToConsole(int32 level,
                                   const base::string16& message,
                                   int32 line_no,
                                   const base::string16& source_id);

  
  virtual void RenderFrameCreated(RenderFrameHost* render_frame_host) {}

  
  virtual void RenderFrameDeleted(RenderFrameHost* render_frame_host) {}

  
  
  
  
  virtual void DidStartLoading(RenderFrameHost* render_frame_host,
                               bool to_different_document) {}

  
  virtual void SwappedOut(RenderFrameHost* render_frame_host) {}

  
  
  virtual void DidDeferAfterResponseStarted(
      const TransitionLayerData& transition_data) {}

  
  virtual bool WillHandleDeferAfterResponseStarted();

  
  virtual void WorkerCrashed(RenderFrameHost* render_frame_host) {}

  
  
  virtual void ShowContextMenu(RenderFrameHost* render_frame_host,
                               const ContextMenuParams& params) {}

  
  virtual void RunJavaScriptMessage(RenderFrameHost* render_frame_host,
                                    const base::string16& message,
                                    const base::string16& default_prompt,
                                    const GURL& frame_url,
                                    JavaScriptMessageType type,
                                    IPC::Message* reply_msg) {}

  virtual void RunBeforeUnloadConfirm(RenderFrameHost* render_frame_host,
                                      const base::string16& message,
                                      bool is_reload,
                                      IPC::Message* reply_msg) {}

  
  
  virtual void DidAccessInitialDocument() {}

  
  
  virtual void DidDisownOpener(RenderFrameHost* render_frame_host) {}

  
  
  virtual void DocumentOnLoadCompleted(RenderFrameHost* render_frame_host) {}

  
  
  virtual void UpdateTitle(RenderFrameHost* render_frame_host,
                           int32 page_id,
                           const base::string16& title,
                           base::i18n::TextDirection title_direction) {}

  
  
  virtual void UpdateEncoding(RenderFrameHost* render_frame_host,
                              const std::string& encoding) {}

  
  
  virtual WebContents* GetAsWebContents();

  
  
  
  virtual void RequestMediaAccessPermission(
      const MediaStreamRequest& request,
      const MediaResponseCallback& callback);

  
  
  
  virtual bool CheckMediaAccessPermission(const GURL& security_origin,
                                          MediaStreamType type);

  
  virtual AccessibilityMode GetAccessibilityMode() const;

  
  virtual void AccessibilityEventReceived(
      const std::vector<AXEventNotificationDetails>& details) {}

  
  virtual RenderFrameHost* GetGuestByInstanceID(
      int browser_plugin_instance_id);

#if defined(OS_WIN)
  
  virtual gfx::NativeViewAccessible GetParentNativeViewAccessible();
#endif

 protected:
  virtual ~RenderFrameHostDelegate() {}
};

}  

#endif  
