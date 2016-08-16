// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_PEER_CONNECTION_DEPENDENCY_FACTORY_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_PEER_CONNECTION_DEPENDENCY_FACTORY_H_

#include <string>

#include "base/basictypes.h"
#include "base/files/file.h"
#include "base/threading/thread.h"
#include "content/common/content_export.h"
#include "content/public/renderer/render_process_observer.h"
#include "content/renderer/media/aec_dump_message_filter.h"
#include "content/renderer/p2p/socket_dispatcher.h"
#include "ipc/ipc_platform_file.h"
#include "third_party/libjingle/source/talk/app/webrtc/peerconnectioninterface.h"
#include "third_party/libjingle/source/talk/app/webrtc/videosourceinterface.h"

namespace base {
class WaitableEvent;
}

namespace rtc {
class NetworkManager;
class PacketSocketFactory;
class Thread;
}

namespace blink {
class WebFrame;
class WebMediaConstraints;
class WebMediaStream;
class WebMediaStreamSource;
class WebMediaStreamTrack;
class WebRTCPeerConnectionHandler;
class WebRTCPeerConnectionHandlerClient;
}

namespace content {

class IpcNetworkManager;
class IpcPacketSocketFactory;
class MediaStreamAudioSource;
class RTCMediaConstraints;
class WebAudioCapturerSource;
class WebRtcAudioCapturer;
class WebRtcAudioDeviceImpl;
class WebRtcLocalAudioTrack;
class WebRtcLoggingHandlerImpl;
class WebRtcLoggingMessageFilter;
class WebRtcVideoCapturerAdapter;
struct StreamDeviceInfo;

class CONTENT_EXPORT PeerConnectionDependencyFactory
    : NON_EXPORTED_BASE(public base::NonThreadSafe),
      NON_EXPORTED_BASE(public AecDumpMessageFilter::AecDumpDelegate) {
 public:
  PeerConnectionDependencyFactory(
      P2PSocketDispatcher* p2p_socket_dispatcher);
  virtual ~PeerConnectionDependencyFactory();

  
  
  blink::WebRTCPeerConnectionHandler* CreateRTCPeerConnectionHandler(
      blink::WebRTCPeerConnectionHandlerClient* client);

  
  virtual scoped_refptr<webrtc::MediaStreamInterface>
      CreateLocalMediaStream(const std::string& label);

  
  
  bool InitializeMediaStreamAudioSource(
      int render_view_id,
      const blink::WebMediaConstraints& audio_constraints,
      MediaStreamAudioSource* source_data);

  
  
  virtual WebRtcVideoCapturerAdapter* CreateVideoCapturer(
      bool is_screen_capture);

  
  
  void CreateLocalAudioTrack(const blink::WebMediaStreamTrack& track);

  
  virtual scoped_refptr<webrtc::VideoTrackInterface>
      CreateLocalVideoTrack(const std::string& id,
                            webrtc::VideoSourceInterface* source);

  
  
  virtual scoped_refptr<webrtc::VideoSourceInterface>
      CreateVideoSource(cricket::VideoCapturer* capturer,
                        const blink::WebMediaConstraints& constraints);

  
  
  
  virtual scoped_refptr<webrtc::PeerConnectionInterface>
      CreatePeerConnection(
          const webrtc::PeerConnectionInterface::RTCConfiguration& config,
          const webrtc::MediaConstraintsInterface* constraints,
          blink::WebFrame* web_frame,
          webrtc::PeerConnectionObserver* observer);

  
  
  virtual webrtc::SessionDescriptionInterface* CreateSessionDescription(
      const std::string& type,
      const std::string& sdp,
      webrtc::SdpParseError* error);

  
  virtual webrtc::IceCandidateInterface* CreateIceCandidate(
      const std::string& sdp_mid,
      int sdp_mline_index,
      const std::string& sdp);

  WebRtcAudioDeviceImpl* GetWebRtcAudioDevice();

  static void AddNativeAudioTrackToBlinkTrack(
      webrtc::MediaStreamTrackInterface* native_track,
      const blink::WebMediaStreamTrack& webkit_track,
      bool is_local_track);

  scoped_refptr<base::MessageLoopProxy> GetWebRtcWorkerThread() const;

  
  
  
  virtual void OnAecDumpFile(
      const IPC::PlatformFileForTransit& file_handle) OVERRIDE;
  virtual void OnDisableAecDump() OVERRIDE;
  virtual void OnIpcClosing() OVERRIDE;

 protected:
  
  virtual scoped_refptr<webrtc::AudioSourceInterface>
      CreateLocalAudioSource(
          const webrtc::MediaConstraintsInterface* constraints);

  
  
  
  
  virtual scoped_refptr<WebAudioCapturerSource> CreateWebAudioSource(
      blink::WebMediaStreamSource* source);

  
  
  virtual scoped_refptr<webrtc::VideoTrackInterface>
      CreateLocalVideoTrack(const std::string& id,
                            cricket::VideoCapturer* capturer);

  virtual const scoped_refptr<webrtc::PeerConnectionFactoryInterface>&
      GetPcFactory();
  virtual bool PeerConnectionFactoryCreated();

  
  
  
  virtual scoped_refptr<WebRtcAudioCapturer> CreateAudioCapturer(
      int render_view_id, const StreamDeviceInfo& device_info,
      const blink::WebMediaConstraints& constraints,
      MediaStreamAudioSource* audio_source);

  
  
  
  virtual void StartLocalAudioTrack(WebRtcLocalAudioTrack* audio_track);

 private:
  
  
  void CreatePeerConnectionFactory();

  void InitializeWorkerThread(rtc::Thread** thread,
                              base::WaitableEvent* event);

  void CreateIpcNetworkManagerOnWorkerThread(base::WaitableEvent* event);
  void DeleteIpcNetworkManager();
  void CleanupPeerConnectionFactory();

  
  void EnsureWebRtcAudioDeviceImpl();

  
  
  IpcNetworkManager* network_manager_;
  scoped_ptr<IpcPacketSocketFactory> socket_factory_;

  scoped_refptr<webrtc::PeerConnectionFactoryInterface> pc_factory_;

  scoped_refptr<P2PSocketDispatcher> p2p_socket_dispatcher_;
  scoped_refptr<WebRtcAudioDeviceImpl> audio_device_;

  
  
  
  scoped_refptr<AecDumpMessageFilter> aec_dump_message_filter_;

  
  
  rtc::Thread* signaling_thread_;
  rtc::Thread* worker_thread_;
  base::Thread chrome_worker_thread_;

  DISALLOW_COPY_AND_ASSIGN(PeerConnectionDependencyFactory);
};

}  

#endif  
