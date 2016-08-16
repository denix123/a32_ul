// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_CONNECTION_TO_HOST_H_
#define REMOTING_PROTOCOL_CONNECTION_TO_HOST_H_

#include <set>
#include <string>

#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/timer/timer.h"
#include "remoting/proto/internal.pb.h"
#include "remoting/protocol/clipboard_filter.h"
#include "remoting/protocol/errors.h"
#include "remoting/protocol/input_filter.h"
#include "remoting/protocol/message_reader.h"
#include "remoting/protocol/monitored_video_stub.h"
#include "remoting/protocol/session.h"
#include "remoting/protocol/session_config.h"
#include "remoting/protocol/session_manager.h"
#include "remoting/signaling/signal_strategy.h"

namespace remoting {

class XmppProxy;
class VideoPacket;

namespace protocol {

class AudioReader;
class AudioStub;
class Authenticator;
class ClientControlDispatcher;
class ClientEventDispatcher;
class ClientStub;
class ClipboardStub;
class HostStub;
class InputStub;
class SessionConfig;
class TransportFactory;
class ClientVideoDispatcher;
class VideoStub;

class ConnectionToHost : public SignalStrategy::Listener,
                         public SessionManager::Listener,
                         public Session::EventHandler,
                         public base::NonThreadSafe {
 public:
  
  
  
  
  enum State {
    INITIALIZING,
    CONNECTING,
    AUTHENTICATED,
    CONNECTED,
    FAILED,
    CLOSED,
  };

  class HostEventCallback {
   public:
    virtual ~HostEventCallback() {}

    
    virtual void OnConnectionState(State state, ErrorCode error) = 0;

    
    
    
    
    virtual void OnConnectionReady(bool ready) = 0;

    
    virtual void OnRouteChanged(const std::string& channel_name,
                                const protocol::TransportRoute& route) = 0;
  };

  ConnectionToHost();
  virtual ~ConnectionToHost();

  
  
  void set_candidate_config(scoped_ptr<CandidateSessionConfig> config);

  
  
  
  
  void set_client_stub(ClientStub* client_stub);
  void set_clipboard_stub(ClipboardStub* clipboard_stub);
  void set_video_stub(VideoStub* video_stub);
  
  void set_audio_stub(AudioStub* audio_stub);

  
  
  
  
  
  
  
  virtual void Connect(SignalStrategy* signal_strategy,
                       scoped_ptr<TransportFactory> transport_factory,
                       scoped_ptr<Authenticator> authenticator,
                       const std::string& host_jid,
                       HostEventCallback* event_callback);

  
  virtual const SessionConfig& config();

  
  virtual ClipboardStub* clipboard_forwarder();
  virtual HostStub* host_stub();
  virtual InputStub* input_stub();

  
  virtual void OnSignalStrategyStateChange(
      SignalStrategy::State state) OVERRIDE;
  virtual bool OnSignalStrategyIncomingStanza(
      const buzz::XmlElement* stanza) OVERRIDE;

  
  virtual void OnSessionManagerReady() OVERRIDE;
  virtual void OnIncomingSession(
      Session* session,
      SessionManager::IncomingSessionResponse* response) OVERRIDE;

  
  virtual void OnSessionStateChange(Session::State state) OVERRIDE;
  virtual void OnSessionRouteChange(const std::string& channel_name,
                                    const TransportRoute& route) OVERRIDE;

  
  virtual void OnVideoChannelStatus(bool active);

  
  State state() const;

 private:
  
  void OnChannelInitialized(bool successful);

  void NotifyIfChannelsReady();

  void CloseOnError(ErrorCode error);

  
  void CloseChannels();

  void SetState(State state, ErrorCode error);

  std::string host_jid_;
  std::string host_public_key_;
  scoped_ptr<Authenticator> authenticator_;

  HostEventCallback* event_callback_;

  scoped_ptr<CandidateSessionConfig> candidate_config_;

  
  ClientStub* client_stub_;
  ClipboardStub* clipboard_stub_;
  AudioStub* audio_stub_;

  SignalStrategy* signal_strategy_;
  scoped_ptr<SessionManager> session_manager_;
  scoped_ptr<Session> session_;
  scoped_ptr<MonitoredVideoStub> monitored_video_stub_;

  scoped_ptr<ClientVideoDispatcher> video_dispatcher_;
  scoped_ptr<AudioReader> audio_reader_;
  scoped_ptr<ClientControlDispatcher> control_dispatcher_;
  scoped_ptr<ClientEventDispatcher> event_dispatcher_;
  ClipboardFilter clipboard_forwarder_;
  InputFilter event_forwarder_;

  
  State state_;
  ErrorCode error_;

 private:
  DISALLOW_COPY_AND_ASSIGN(ConnectionToHost);
};

}  
}  

#endif  
