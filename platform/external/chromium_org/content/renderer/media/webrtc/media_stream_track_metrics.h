// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_MEDIA_STREAM_TRACK_METRICS_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_MEDIA_STREAM_TRACK_METRICS_H_

#include "base/basictypes.h"
#include "base/memory/scoped_vector.h"
#include "base/threading/non_thread_safe.h"
#include "content/common/content_export.h"
#include "third_party/libjingle/source/talk/app/webrtc/peerconnectioninterface.h"

namespace webrtc {
class MediaStreamInterface;
class MediaStreamTrackInterface;
}

namespace content {

class MediaStreamTrackMetricsObserver;
class RTCPeerConnectionHandler;

class CONTENT_EXPORT MediaStreamTrackMetrics : public base::NonThreadSafe {
 public:
  explicit MediaStreamTrackMetrics();
  ~MediaStreamTrackMetrics();

  enum StreamType { SENT_STREAM, RECEIVED_STREAM };

  enum TrackType { AUDIO_TRACK, VIDEO_TRACK };

  enum LifetimeEvent { CONNECTED, DISCONNECTED };

  
  
  
  void AddStream(StreamType type, webrtc::MediaStreamInterface* stream);

  
  void RemoveStream(StreamType type, webrtc::MediaStreamInterface* stream);

  
  
  
  void IceConnectionChange(
      webrtc::PeerConnectionInterface::IceConnectionState new_state);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void SendLifetimeMessage(const std::string& track_id,
                                   TrackType track_type,
                                   LifetimeEvent lifetime_event,
                                   StreamType stream_type);

 protected:
  
  void SendLifeTimeMessageDependingOnIceState(
      MediaStreamTrackMetricsObserver* observer);

  
  
  
  
  uint64 MakeUniqueIdImpl(uint64 pc_id,
                          const std::string& track,
                          StreamType stream_type);

 private:
  
  
  uint64 MakeUniqueId(const std::string& track, StreamType stream_type);

  typedef ScopedVector<MediaStreamTrackMetricsObserver> ObserverVector;
  ObserverVector observers_;

  webrtc::PeerConnectionInterface::IceConnectionState ice_state_;
};

}  

#endif  
