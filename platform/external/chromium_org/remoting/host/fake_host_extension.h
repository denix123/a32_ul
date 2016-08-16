// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_FAKE_HOST_EXTENSION_H_
#define REMOTING_HOST_FAKE_HOST_EXTENSION_H_

#include <string>

#include "remoting/host/host_extension.h"

namespace remoting {

class ClientSessionControl;
class HostExtensionSession;

namespace protocol {
class ClientStub;
}

class FakeExtension : public HostExtension {
 public:
  FakeExtension(const std::string& message_type,
                const std::string& capability);
  virtual ~FakeExtension();

  
  virtual std::string capability() const OVERRIDE;
  virtual scoped_ptr<HostExtensionSession> CreateExtensionSession(
      ClientSessionControl* client_session_control,
      protocol::ClientStub* client_stub) OVERRIDE;

  
  void set_steal_video_capturer(bool steal_video_capturer) {
    steal_video_capturer_ = steal_video_capturer;
  }

  
  bool has_handled_message() const { return has_handled_message_; }
  bool has_wrapped_video_encoder() const { return has_wrapped_video_encoder_; }
  bool has_wrapped_video_capturer() const {
    return has_wrapped_video_capturer_;
  }
  bool was_instantiated() const { return was_instantiated_; }

 private:
  class Session;
  friend class Session;

  
  std::string message_type_;

  
  std::string capability_;

  
  
  bool steal_video_capturer_;

  
  bool has_handled_message_;

  
  bool has_wrapped_video_encoder_;
  bool has_wrapped_video_capturer_;

  
  bool was_instantiated_;

  DISALLOW_COPY_AND_ASSIGN(FakeExtension);
};

} 

#endif  
