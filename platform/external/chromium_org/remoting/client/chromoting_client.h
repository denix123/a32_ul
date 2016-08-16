// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef REMOTING_CLIENT_CHROMOTING_CLIENT_H_
#define REMOTING_CLIENT_CHROMOTING_CLIENT_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "remoting/client/chromoting_stats.h"
#include "remoting/protocol/client_stub.h"
#include "remoting/protocol/clipboard_stub.h"
#include "remoting/protocol/connection_to_host.h"
#include "remoting/protocol/input_stub.h"
#include "remoting/protocol/video_stub.h"

namespace base {
class SingleThreadTaskRunner;
}  

namespace remoting {

namespace protocol {
class CandidateSessionConfig;
class TransportFactory;
}  

class AudioDecodeScheduler;
class AudioPlayer;
class ClientContext;
class ClientUserInterface;
class FrameConsumerProxy;
class FrameProducer;
class VideoRenderer;
class SignalStrategy;

class ChromotingClient : public protocol::ConnectionToHost::HostEventCallback,
                         public protocol::ClientStub {
 public:
  
  ChromotingClient(ClientContext* client_context,
                   ClientUserInterface* user_interface,
                   VideoRenderer* video_renderer,
                   scoped_ptr<AudioPlayer> audio_player);

  virtual ~ChromotingClient();

  void SetProtocolConfigForTests(
      scoped_ptr<protocol::CandidateSessionConfig> config);

  
  
  void Start(SignalStrategy* signal_strategy,
             scoped_ptr<protocol::Authenticator> authenticator,
             scoped_ptr<protocol::TransportFactory> transport_factory,
             const std::string& host_jid,
             const std::string& capabilities);

  protocol::ConnectionToHost::State connection_state() const {
    return connection_.state();
  }

  protocol::ClipboardStub* clipboard_forwarder() {
    return connection_.clipboard_forwarder();
  }
  protocol::HostStub* host_stub() { return connection_.host_stub(); }
  protocol::InputStub* input_stub() { return connection_.input_stub(); }

  
  virtual void SetCapabilities(
      const protocol::Capabilities& capabilities) OVERRIDE;
  virtual void SetPairingResponse(
      const protocol::PairingResponse& pairing_response) OVERRIDE;
  virtual void DeliverHostMessage(
      const protocol::ExtensionMessage& message) OVERRIDE;

  
  virtual void InjectClipboardEvent(
      const protocol::ClipboardEvent& event) OVERRIDE;

  
  virtual void SetCursorShape(
      const protocol::CursorShapeInfo& cursor_shape) OVERRIDE;

  
  virtual void OnConnectionState(
      protocol::ConnectionToHost::State state,
      protocol::ErrorCode error) OVERRIDE;
  virtual void OnConnectionReady(bool ready) OVERRIDE;
  virtual void OnRouteChanged(const std::string& channel_name,
                              const protocol::TransportRoute& route) OVERRIDE;

 private:
  
  void OnAuthenticated();

  
  void OnChannelsConnected();

  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  ClientUserInterface* user_interface_;
  VideoRenderer* video_renderer_;

  protocol::ConnectionToHost connection_;

  scoped_ptr<AudioDecodeScheduler> audio_decode_scheduler_;

  std::string local_capabilities_;

  
  std::string host_capabilities_;

  
  bool host_capabilities_received_;

  
  ChromotingStats stats_;

  DISALLOW_COPY_AND_ASSIGN(ChromotingClient);
};

}  

#endif  
