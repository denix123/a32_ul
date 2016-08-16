// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_BROWSER_PLUGIN_BROWSER_PLUGIN_MESSAGE_FILTER_H_
#define CONTENT_BROWSER_BROWSER_PLUGIN_BROWSER_PLUGIN_MESSAGE_FILTER_H_

#include "content/public/browser/browser_message_filter.h"

struct FrameHostMsg_BuffersSwappedACK_Params;

namespace content {

class BrowserContext;

class BrowserPluginMessageFilter : public BrowserMessageFilter {
 public:
  BrowserPluginMessageFilter(int render_process_id);

  
  virtual void OverrideThreadForMessage(
    const IPC::Message& message,
    BrowserThread::ID* thread) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnDestruct() const OVERRIDE;

 private:
  friend class BrowserThread;
  friend class base::DeleteHelper<BrowserPluginMessageFilter>;

  virtual ~BrowserPluginMessageFilter();

  void ForwardMessageToGuest(const IPC::Message& message);

  int render_process_id_;

  DISALLOW_COPY_AND_ASSIGN(BrowserPluginMessageFilter);
};

} 

#endif  
