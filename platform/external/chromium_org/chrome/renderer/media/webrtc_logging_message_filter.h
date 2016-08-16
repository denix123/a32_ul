// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_MEDIA_WEBRTC_LOGGING_MESSAGE_FILTER_H_
#define CHROME_RENDERER_MEDIA_WEBRTC_LOGGING_MESSAGE_FILTER_H_

#include "chrome/common/media/webrtc_logging_message_data.h"
#include "ipc/message_filter.h"

namespace base {
class MessageLoopProxy;
}

class ChromeWebRtcLogMessageDelegate;

class WebRtcLoggingMessageFilter : public IPC::MessageFilter {
 public:
  explicit WebRtcLoggingMessageFilter(
      const scoped_refptr<base::MessageLoopProxy>& io_message_loop);

  virtual void AddLogMessages(
      const std::vector<WebRtcLoggingMessageData>& messages);
  virtual void LoggingStopped();

  const scoped_refptr<base::MessageLoopProxy>& io_message_loop() {
    return io_message_loop_;
  }

 protected:
  virtual ~WebRtcLoggingMessageFilter();

  scoped_refptr<base::MessageLoopProxy> io_message_loop_;

  
  
  
  
  
  
  
  
  ChromeWebRtcLogMessageDelegate* log_message_delegate_;

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnFilterAdded(IPC::Sender* sender) OVERRIDE;
  virtual void OnFilterRemoved() OVERRIDE;
  virtual void OnChannelClosing() OVERRIDE;

  void CreateLoggingHandler();

  void OnStartLogging();
  void OnStopLogging();
  void Send(IPC::Message* message);

  IPC::Sender* sender_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcLoggingMessageFilter);
};

#endif  
