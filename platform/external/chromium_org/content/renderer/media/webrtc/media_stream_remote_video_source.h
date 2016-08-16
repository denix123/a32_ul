// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_WEBRTC_MEDIA_STREAM_REMOTE_VIDEO_SOURCE_H_
#define CONTENT_RENDERER_MEDIA_WEBRTC_MEDIA_STREAM_REMOTE_VIDEO_SOURCE_H_

#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "content/renderer/media/media_stream_video_source.h"
#include "third_party/WebKit/public/platform/WebMediaStreamSource.h"
#include "third_party/libjingle/source/talk/app/webrtc/mediastreaminterface.h"

namespace content {

class CONTENT_EXPORT MediaStreamRemoteVideoSource
     : public MediaStreamVideoSource,
       NON_EXPORTED_BASE(public webrtc::ObserverInterface) {
 public:
  explicit MediaStreamRemoteVideoSource(
      webrtc::VideoTrackInterface* remote_track);
  virtual ~MediaStreamRemoteVideoSource();

 protected:
  
  virtual void GetCurrentSupportedFormats(
      int max_requested_width,
      int max_requested_height,
      double max_requested_frame_rate,
      const VideoCaptureDeviceFormatsCB& callback) OVERRIDE;

  virtual void StartSourceImpl(
      const media::VideoCaptureFormat& format,
      const VideoCaptureDeliverFrameCB& frame_callback) OVERRIDE;

  virtual void StopSourceImpl() OVERRIDE;

  
  
  webrtc::VideoRendererInterface* RenderInterfaceForTest();

 private:
  
  virtual void OnChanged() OVERRIDE;

  scoped_refptr<webrtc::VideoTrackInterface> remote_track_;
  webrtc::MediaStreamTrackInterface::TrackState last_state_;

  
  
  class RemoteVideoSourceDelegate;
  scoped_refptr<RemoteVideoSourceDelegate> delegate_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamRemoteVideoSource);
};

}  

#endif  
