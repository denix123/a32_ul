// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CLIENT_CHROMOTING_JNI_INSTANCE_H_
#define REMOTING_CLIENT_CHROMOTING_JNI_INSTANCE_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop.h"
#include "remoting/client/chromoting_client.h"
#include "remoting/client/client_context.h"
#include "remoting/client/client_user_interface.h"
#include "remoting/client/frame_consumer_proxy.h"
#include "remoting/client/jni/jni_frame_consumer.h"
#include "remoting/protocol/clipboard_stub.h"
#include "remoting/protocol/cursor_shape_stub.h"
#include "remoting/signaling/xmpp_signal_strategy.h"

namespace remoting {

namespace protocol {
class ClipboardEvent;
class CursorShapeInfo;
}  

class ClientStatusLogger;
class VideoRenderer;
class TokenFetcherProxy;

class ChromotingJniInstance
  : public ClientUserInterface,
    public protocol::ClipboardStub,
    public protocol::CursorShapeStub,
    public base::RefCountedThreadSafe<ChromotingJniInstance> {
 public:
  
  
  
  ChromotingJniInstance(ChromotingJniRuntime* jni_runtime,
                        const char* username,
                        const char* auth_token,
                        const char* host_jid,
                        const char* host_id,
                        const char* host_pubkey,
                        const char* pairing_id,
                        const char* pairing_secret,
                        const char* capabilities);

  
  
  void Disconnect();

  
  void FetchThirdPartyToken(
      const GURL& token_url,
      const std::string& client_id,
      const std::string& scope,
      const base::WeakPtr<TokenFetcherProxy> token_fetcher_proxy);

  
  void HandleOnThirdPartyTokenFetched(const std::string& token,
                                      const std::string& shared_secret);

  
  
  
  void ProvideSecret(const std::string& pin, bool create_pair,
                     const std::string& device_name);

  
  void RedrawDesktop();

  
  
  void SendMouseEvent(int x, int y,
                      protocol::MouseEvent_MouseButton button,
                      bool button_down);
  void SendMouseWheelEvent(int delta_x, int delta_y);

  
  bool SendKeyEvent(int key_code, bool key_down);

  void SendTextEvent(const std::string& text);

  void SendClientMessage(const std::string& type, const std::string& data);

  
  
  void RecordPaintTime(int64 paint_time_ms);

  
  virtual void OnConnectionState(
      protocol::ConnectionToHost::State state,
      protocol::ErrorCode error) OVERRIDE;
  virtual void OnConnectionReady(bool ready) OVERRIDE;
  virtual void OnRouteChanged(const std::string& channel_name,
                              const protocol::TransportRoute& route) OVERRIDE;
  virtual void SetCapabilities(const std::string& capabilities) OVERRIDE;
  virtual void SetPairingResponse(
      const protocol::PairingResponse& response) OVERRIDE;
  virtual void DeliverHostMessage(
      const protocol::ExtensionMessage& message) OVERRIDE;
  virtual protocol::ClipboardStub* GetClipboardStub() OVERRIDE;
  virtual protocol::CursorShapeStub* GetCursorShapeStub() OVERRIDE;

  
  virtual void InjectClipboardEvent(
      const protocol::ClipboardEvent& event) OVERRIDE;

  
  virtual void SetCursorShape(const protocol::CursorShapeInfo& shape) OVERRIDE;

 private:
  
  virtual ~ChromotingJniInstance();

  void ConnectToHostOnDisplayThread();
  void ConnectToHostOnNetworkThread();
  void DisconnectFromHostOnNetworkThread();

  
  
  
  void FetchSecret(bool pairable,
                   const protocol::SecretFetchedCallback& callback);

  
  void SetDeviceName(const std::string& device_name);

  void SendKeyEventInternal(int usb_key_code, bool key_down);

  
  
  void EnableStatsLogging(bool enabled);

  
  
  
  void LogPerfStats();

  
  ChromotingJniRuntime* jni_runtime_;

  
  std::string host_id_;
  std::string host_jid_;

  
  scoped_refptr<FrameConsumerProxy> frame_consumer_;
  scoped_ptr<JniFrameConsumer> view_;
  scoped_ptr<base::WeakPtrFactory<JniFrameConsumer> > view_weak_factory_;

  
  scoped_ptr<ClientContext> client_context_;
  scoped_ptr<VideoRenderer> video_renderer_;
  scoped_ptr<protocol::Authenticator> authenticator_;
  scoped_ptr<ChromotingClient> client_;
  XmppSignalStrategy::XmppServerConfig xmpp_config_;
  scoped_ptr<XmppSignalStrategy> signaling_;  
  scoped_ptr<ClientStatusLogger> client_status_logger_;
  base::WeakPtr<TokenFetcherProxy> token_fetcher_proxy_;

  
  
  protocol::SecretFetchedCallback pin_callback_;

  
  
  
  
  bool create_pairing_;

  
  
  std::string device_name_;

  // If this is true, performance statistics will be periodically written to
  
  bool stats_logging_enabled_;

  
  
  
  std::string capabilities_;

  friend class base::RefCountedThreadSafe<ChromotingJniInstance>;

  base::WeakPtrFactory<ChromotingJniInstance> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromotingJniInstance);
};

}  

#endif
