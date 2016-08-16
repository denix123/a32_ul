// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_HOST_EXTENSION_SESSION_H_
#define REMOTING_HOST_HOST_EXTENSION_SESSION_H_

#include "base/memory/scoped_ptr.h"

namespace webrtc {
class DesktopCapturer;
}

namespace remoting {

class ClientSessionControl;
class VideoEncoder;

namespace protocol {
class ExtensionMessage;
class ClientStub;
}  

class HostExtensionSession {
 public:
  virtual ~HostExtensionSession() {}

  
  
  
  
  
  
  virtual void OnCreateVideoCapturer(
      scoped_ptr<webrtc::DesktopCapturer>* capturer);
  virtual void OnCreateVideoEncoder(scoped_ptr<VideoEncoder>* encoder);

  
  
  virtual bool ModifiesVideoPipeline() const;

  
  
  
  virtual bool OnExtensionMessage(
      ClientSessionControl* client_session_control,
      protocol::ClientStub* client_stub,
      const protocol::ExtensionMessage& message) = 0;
};

}  

#endif  
