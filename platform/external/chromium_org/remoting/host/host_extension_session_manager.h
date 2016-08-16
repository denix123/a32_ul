// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_HOST_EXTENSION_SESSION_MANAGER_H_
#define REMOTING_HOST_HOST_EXTENSION_SESSION_MANAGER_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"

namespace webrtc {
class DesktopCapturer;
}

namespace remoting {

class ClientSessionControl;
class HostExtension;
class HostExtensionSession;
class VideoEncoder;

namespace protocol {
class ClientStub;
class ExtensionMessage;
}

class HostExtensionSessionManager {
 public:
  typedef std::vector<HostExtension*> HostExtensions;

  
  HostExtensionSessionManager(const HostExtensions& extensions,
                              ClientSessionControl* client_session_control);
  virtual ~HostExtensionSessionManager();

  
  std::string GetCapabilities() const;

  
  
  
  
  void OnCreateVideoCapturer(scoped_ptr<webrtc::DesktopCapturer>* capturer);
  void OnCreateVideoEncoder(scoped_ptr<VideoEncoder>* encoder);

  
  
  void OnNegotiatedCapabilities(protocol::ClientStub* client_stub,
                                const std::string& capabilities);

  
  
  
  bool OnExtensionMessage(const protocol::ExtensionMessage& message);

 private:
  typedef ScopedVector<HostExtensionSession> HostExtensionSessions;

  
  
  ClientSessionControl* client_session_control_;
  protocol::ClientStub* client_stub_;

  
  
  HostExtensions extensions_;

  
  HostExtensionSessions extension_sessions_;

  DISALLOW_COPY_AND_ASSIGN(HostExtensionSessionManager);
};

}  

#endif  
