// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_TEST_IN_PROCESS_RECEIVER_H_
#define MEDIA_CAST_TEST_IN_PROCESS_RECEIVER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "media/base/audio_bus.h"
#include "media/cast/cast_config.h"
#include "media/cast/net/cast_transport_config.h"
#include "net/base/ip_endpoint.h"

namespace base {
class TimeTicks;
class WaitableEvent;
}  

namespace net {
class IPEndPoint;
}  

namespace media {

class VideoFrame;

namespace cast {

class CastEnvironment;
class CastReceiver;
class UdpTransport;

class InProcessReceiver {
 public:
  
  
  
  InProcessReceiver(const scoped_refptr<CastEnvironment>& cast_environment,
                    const net::IPEndPoint& local_end_point,
                    const net::IPEndPoint& remote_end_point,
                    const FrameReceiverConfig& audio_config,
                    const FrameReceiverConfig& video_config);

  virtual ~InProcessReceiver();

  
  scoped_refptr<CastEnvironment> cast_env() const { return cast_environment_; }
  const FrameReceiverConfig& audio_config() const { return audio_config_; }
  const FrameReceiverConfig& video_config() const { return video_config_; }

  
  
  virtual void Start();

  
  
  virtual void Stop();

 protected:
  
  
  virtual void OnAudioFrame(scoped_ptr<AudioBus> audio_frame,
                            const base::TimeTicks& playout_time,
                            bool is_continuous) = 0;
  virtual void OnVideoFrame(const scoped_refptr<VideoFrame>& video_frame,
                            const base::TimeTicks& playout_time,
                            bool is_continuous) = 0;

  
  
  
  virtual void StartOnMainThread();

  
  
  virtual void StopOnMainThread(base::WaitableEvent* event);

  
  
  virtual void UpdateCastTransportStatus(CastTransportStatus status);

 private:
  friend class base::RefCountedThreadSafe<InProcessReceiver>;

  
  
  
  void GotAudioFrame(scoped_ptr<AudioBus> audio_frame,
                     const base::TimeTicks& playout_time,
                     bool is_continuous);
  void GotVideoFrame(const scoped_refptr<VideoFrame>& video_frame,
                     const base::TimeTicks& playout_time,
                     bool is_continuous);
  void PullNextAudioFrame();
  void PullNextVideoFrame();

  const scoped_refptr<CastEnvironment> cast_environment_;
  const net::IPEndPoint local_end_point_;
  const net::IPEndPoint remote_end_point_;
  const FrameReceiverConfig audio_config_;
  const FrameReceiverConfig video_config_;

  scoped_ptr<UdpTransport> transport_;
  scoped_ptr<CastReceiver> cast_receiver_;

  
  base::WeakPtrFactory<InProcessReceiver> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(InProcessReceiver);
};

}  
}  

#endif  
