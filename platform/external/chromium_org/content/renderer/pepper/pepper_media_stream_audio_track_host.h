// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_PEPPER_MEDIA_STREAM_AUDIO_TRACK_HOST_H_
#define CONTENT_RENDERER_PEPPER_PEPPER_MEDIA_STREAM_AUDIO_TRACK_HOST_H_

#include <deque>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "content/public/renderer/media_stream_audio_sink.h"
#include "content/renderer/pepper/pepper_media_stream_track_host_base.h"
#include "media/audio/audio_parameters.h"
#include "ppapi/host/host_message_context.h"
#include "ppapi/shared_impl/media_stream_audio_track_shared.h"
#include "third_party/WebKit/public/platform/WebMediaStreamTrack.h"

namespace base {
class MessageLoopProxy;
}  

namespace content {

class PepperMediaStreamAudioTrackHost : public PepperMediaStreamTrackHostBase {
 public:
  PepperMediaStreamAudioTrackHost(RendererPpapiHost* host,
                                  PP_Instance instance,
                                  PP_Resource resource,
                                  const blink::WebMediaStreamTrack& track);

 private:
  
  
  class AudioSink : public MediaStreamAudioSink {
   public:
    explicit AudioSink(PepperMediaStreamAudioTrackHost* host);
    virtual ~AudioSink();

    
    
    
    void EnqueueBuffer(int32_t index);

    
    int32_t Configure(int32_t number_of_buffers, int32_t duration,
                      const ppapi::host::ReplyMessageContext& context);

    
    void SendConfigureReply(int32_t result);

   private:
    
    void SetFormatOnMainThread(int bytes_per_second, int bytes_per_frame);

    void InitBuffers();

    
    void SendEnqueueBufferMessageOnMainThread(int32_t index,
                                              int32_t buffers_generation);

    
    
    virtual void OnData(const int16* audio_data,
                        int sample_rate,
                        int number_of_channels,
                        int number_of_frames) OVERRIDE;
    virtual void OnSetFormat(const media::AudioParameters& params) OVERRIDE;

    
    
    
    
    
    PepperMediaStreamAudioTrackHost* host_;

    
    
    base::TimeDelta timestamp_;

    
    
    base::TimeDelta buffer_duration_;

    
    
    media::AudioParameters audio_params_;

    
    
    
    media::AudioParameters original_audio_params_;

    
    
    uint32_t buffer_data_size_;

    
    
    int active_buffer_index_;

    
    
    
    int32_t active_buffers_generation_;

    
    
    uint32_t active_buffer_offset_;

    
    
    base::Lock lock_;

    
    std::deque<int32_t> buffers_;

    
    int32_t buffers_generation_;

    
    int32_t output_buffer_size_;

    scoped_refptr<base::MessageLoopProxy> main_message_loop_proxy_;

    base::ThreadChecker audio_thread_checker_;

    
    int32_t number_of_buffers_;

    
    int bytes_per_second_;

    
    int bytes_per_frame_;

    
    int32_t user_buffer_duration_;

    
    ppapi::host::ReplyMessageContext pending_configure_reply_;

    base::WeakPtrFactory<AudioSink> weak_factory_;

    DISALLOW_COPY_AND_ASSIGN(AudioSink);
  };

  virtual ~PepperMediaStreamAudioTrackHost();

  
  virtual int32_t OnResourceMessageReceived(
      const IPC::Message& msg,
      ppapi::host::HostMessageContext* context) OVERRIDE;

  
  int32_t OnHostMsgConfigure(
      ppapi::host::HostMessageContext* context,
      const ppapi::MediaStreamAudioTrackShared::Attributes& attributes);

  
  virtual void OnClose() OVERRIDE;

  
  virtual void OnNewBufferEnqueued() OVERRIDE;

  
  virtual void DidConnectPendingHostToResource() OVERRIDE;

  blink::WebMediaStreamTrack track_;

  
  
  bool connected_;

  AudioSink audio_sink_;

  DISALLOW_COPY_AND_ASSIGN(PepperMediaStreamAudioTrackHost);
};

}  

#endif  
