// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_CAST_EXTENSION_SESSION_H_
#define REMOTING_HOST_CAST_EXTENSION_SESSION_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread.h"
#include "base/timer/timer.h"
#include "base/values.h"
#include "jingle/glue/thread_wrapper.h"
#include "remoting/host/host_extension_session.h"
#include "third_party/libjingle/source/talk/app/webrtc/peerconnectioninterface.h"
#include "third_party/webrtc/base/scoped_ref_ptr.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_capturer.h"

namespace base {
class SingleThreadTaskRunner;
class WaitableEvent;
}  

namespace net {
class URLRequestContextGetter;
}  

namespace webrtc {
class MediaStreamInterface;
}  

namespace remoting {

class CastCreateSessionDescriptionObserver;

namespace protocol {
struct NetworkSettings;
}  

class CastExtensionSession : public HostExtensionSession,
                             public webrtc::PeerConnectionObserver {
 public:
  virtual ~CastExtensionSession();

  
  
  
  static scoped_ptr<CastExtensionSession> Create(
      scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner,
      scoped_refptr<net::URLRequestContextGetter> url_request_context_getter,
      const protocol::NetworkSettings& network_settings,
      ClientSessionControl* client_session_control,
      protocol::ClientStub* client_stub);

  
  void OnCreateSessionDescription(webrtc::SessionDescriptionInterface* desc);
  void OnCreateSessionDescriptionFailure(const std::string& error);

  
  virtual void OnCreateVideoCapturer(
      scoped_ptr<webrtc::DesktopCapturer>* capturer) OVERRIDE;
  virtual bool ModifiesVideoPipeline() const OVERRIDE;
  virtual bool OnExtensionMessage(
      ClientSessionControl* client_session_control,
      protocol::ClientStub* client_stub,
      const protocol::ExtensionMessage& message) OVERRIDE;

  
  virtual void OnError() OVERRIDE;
  virtual void OnSignalingChange(
      webrtc::PeerConnectionInterface::SignalingState new_state) OVERRIDE;
  virtual void OnStateChange(
      webrtc::PeerConnectionObserver::StateType state_changed) OVERRIDE;
  virtual void OnAddStream(webrtc::MediaStreamInterface* stream) OVERRIDE;
  virtual void OnRemoveStream(webrtc::MediaStreamInterface* stream) OVERRIDE;
  virtual void OnDataChannel(
      webrtc::DataChannelInterface* data_channel) OVERRIDE;
  virtual void OnRenegotiationNeeded() OVERRIDE;
  virtual void OnIceConnectionChange(
      webrtc::PeerConnectionInterface::IceConnectionState new_state) OVERRIDE;
  virtual void OnIceGatheringChange(
      webrtc::PeerConnectionInterface::IceGatheringState new_state) OVERRIDE;
  virtual void OnIceCandidate(
      const webrtc::IceCandidateInterface* candidate) OVERRIDE;
  virtual void OnIceComplete() OVERRIDE;

 private:
  CastExtensionSession(
      scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner,
      scoped_refptr<net::URLRequestContextGetter> url_request_context_getter,
      const protocol::NetworkSettings& network_settings,
      ClientSessionControl* client_session_control,
      protocol::ClientStub* client_stub);

  
  
  bool ParseAndSetRemoteDescription(base::DictionaryValue* message);

  
  
  bool ParseAndAddICECandidate(base::DictionaryValue* message);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool SendMessageToClient(const std::string& subject, const std::string& data);

  
  
  
  void EnsureTaskAndSetSend(rtc::Thread** ptr,
                            base::WaitableEvent* event = NULL);

  
  
  
  bool WrapTasksAndSave();

  
  
  bool InitializePeerConnection();

  
  
  
  
  bool SetupVideoStream(scoped_ptr<webrtc::DesktopCapturer> desktop_capturer);

  
  
  
  void PollPeerConnectionStats();

  
  
  void CleanupPeerConnection();

  
  bool connection_active() const;

  
  
  scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> worker_task_runner_;

  
  rtc::scoped_refptr<webrtc::PeerConnectionInterface> peer_connection_;
  rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> peer_conn_factory_;
  rtc::scoped_refptr<webrtc::MediaStreamInterface> stream_;
  rtc::scoped_refptr<CastCreateSessionDescriptionObserver>
      create_session_desc_observer_;

  
  scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;
  const protocol::NetworkSettings& network_settings_;

  
  ClientSessionControl* client_session_control_;

  
  protocol::ClientStub* client_stub_;

  
  rtc::scoped_refptr<webrtc::StatsObserver> stats_observer_;

  
  base::RepeatingTimer<CastExtensionSession> stats_polling_timer_;

  
  
  
  bool received_offer_;

  
  
  bool has_grabbed_capturer_;

  
  
  
  
  rtc::Thread* signaling_thread_wrapper_;
  rtc::Thread* worker_thread_wrapper_;

  
  base::Thread worker_thread_;

  DISALLOW_COPY_AND_ASSIGN(CastExtensionSession);
};

}  

#endif  
