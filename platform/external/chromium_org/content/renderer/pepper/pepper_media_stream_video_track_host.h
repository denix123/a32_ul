// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_PEPPER_MEDIA_STREAM_VIDEO_TRACK_HOST_H_
#define CONTENT_RENDERER_PEPPER_PEPPER_MEDIA_STREAM_VIDEO_TRACK_HOST_H_

#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "content/public/renderer/media_stream_video_sink.h"
#include "content/renderer/media/media_stream_video_source.h"
#include "content/renderer/pepper/pepper_media_stream_track_host_base.h"
#include "media/base/video_frame.h"
#include "ppapi/c/ppb_video_frame.h"
#include "ppapi/shared_impl/media_stream_video_track_shared.h"
#include "third_party/WebKit/public/platform/WebMediaStreamTrack.h"
#include "ui/gfx/size.h"

namespace content {

class PepperMediaStreamVideoTrackHost : public PepperMediaStreamTrackHostBase,
                                        public MediaStreamVideoSink,
                                        public MediaStreamVideoSource {
 public:
  
  
  
  PepperMediaStreamVideoTrackHost(RendererPpapiHost* host,
                                  PP_Instance instance,
                                  PP_Resource resource,
                                  const blink::WebMediaStreamTrack& track);

  
  
  
  PepperMediaStreamVideoTrackHost(RendererPpapiHost* host,
                                  PP_Instance instance,
                                  PP_Resource resource);

  virtual bool IsMediaStreamVideoTrackHost() OVERRIDE;

  blink::WebMediaStreamTrack track() { return track_; }

 private:

  virtual ~PepperMediaStreamVideoTrackHost();

  void InitBuffers();

  
  virtual void OnClose() OVERRIDE;
  virtual int32_t OnHostMsgEnqueueBuffer(
      ppapi::host::HostMessageContext* context, int32_t index) OVERRIDE;

  
  int32_t SendFrameToTrack(int32_t index);

  void OnVideoFrame(const scoped_refptr<media::VideoFrame>& frame,
                    const media::VideoCaptureFormat& format,
                    const base::TimeTicks& estimated_capture_time);

  
  virtual void GetCurrentSupportedFormats(
      int max_requested_width,
      int max_requested_height,
      double max_requested_frame_rate,
      const VideoCaptureDeviceFormatsCB& callback) OVERRIDE;

  virtual void StartSourceImpl(
      const media::VideoCaptureFormat& format,
      const VideoCaptureDeliverFrameCB& frame_callback) OVERRIDE;

  virtual void StopSourceImpl() OVERRIDE;

  
  virtual void DidConnectPendingHostToResource() OVERRIDE;

  
  virtual int32_t OnResourceMessageReceived(
      const IPC::Message& msg,
      ppapi::host::HostMessageContext* context) OVERRIDE;

  
  int32_t OnHostMsgConfigure(
      ppapi::host::HostMessageContext* context,
      const ppapi::MediaStreamVideoTrackShared::Attributes& attributes);

  void InitBlinkTrack();
  void OnTrackStarted(MediaStreamSource* source,
                      MediaStreamRequestResult result,
                      const blink::WebString& result_name);

  blink::WebMediaStreamTrack track_;

  
  bool connected_;

  
  int32_t number_of_buffers_;

  
  gfx::Size source_frame_size_;

  
  gfx::Size plugin_frame_size_;

  
  PP_VideoFrame_Format source_frame_format_;

  
  PP_VideoFrame_Format plugin_frame_format_;

  
  uint32_t frame_data_size_;

  
  
  TrackType type_;
  bool output_started_;

  
  
  class FrameDeliverer;
  scoped_refptr<FrameDeliverer> frame_deliverer_;

  base::WeakPtrFactory<PepperMediaStreamVideoTrackHost> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PepperMediaStreamVideoTrackHost);
};

}  

#endif  
