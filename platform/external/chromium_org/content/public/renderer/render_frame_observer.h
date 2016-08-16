// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_RENDER_FRAME_OBSERVER_H_
#define CONTENT_PUBLIC_RENDERER_RENDER_FRAME_OBSERVER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "v8/include/v8.h"

namespace blink {
class WebFrame;
struct WebURLError;
}

namespace content {

class RendererPpapiHost;
class RenderFrame;
class RenderFrameImpl;

class CONTENT_EXPORT RenderFrameObserver : public IPC::Listener,
                                           public IPC::Sender {
 public:
  
  
  virtual void OnDestruct();

  
  virtual void DidCreatePepperPlugin(RendererPpapiHost* host) {}

  
  virtual void OnStop() {}

  
  virtual void WasHidden() {}
  virtual void WasShown() {}

  
  virtual void DidCommitProvisionalLoad(bool is_new_navigation) {}
  virtual void DidStartProvisionalLoad() {}
  virtual void DidFailProvisionalLoad(const blink::WebURLError& error) {}
  virtual void DidFinishLoad() {}
  virtual void DidFinishDocumentLoad() {}
  virtual void WillReleaseScriptContext(v8::Handle<v8::Context> context,
                                        int world_id) {}
  virtual void DidClearWindowObject() {}
  virtual void DidChangeName(const base::string16& name) {}
  virtual void DidChangeManifest() {}

  
  
  virtual void FrameWillClose() {}

  
  
  
  
  
  
  virtual void DetailedConsoleMessageAdded(const base::string16& message,
                                           const base::string16& source,
                                           const base::string16& stack_trace,
                                           int32 line_number,
                                           int32 severity_level) {}

  
  virtual void DidCommitCompositorFrame() {}

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual bool Send(IPC::Message* message) OVERRIDE;

  RenderFrame* render_frame() const;
  int routing_id() const { return routing_id_; }

 protected:
  explicit RenderFrameObserver(RenderFrame* render_frame);
  virtual ~RenderFrameObserver();

 private:
  friend class RenderFrameImpl;

  
  
  void RenderFrameGone();

  RenderFrame* render_frame_;
  
  int routing_id_;

  DISALLOW_COPY_AND_ASSIGN(RenderFrameObserver);
};

}  

#endif  
