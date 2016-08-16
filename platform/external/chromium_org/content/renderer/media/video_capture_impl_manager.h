// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#ifndef CONTENT_RENDERER_MEDIA_VIDEO_CAPTURE_IMPL_MANAGER_H_
#define CONTENT_RENDERER_MEDIA_VIDEO_CAPTURE_IMPL_MANAGER_H_

#include <map>

#include "base/callback.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "content/common/media/video_capture.h"
#include "content/public/renderer/media_stream_video_sink.h"
#include "media/video/capture/video_capture_types.h"

namespace content {

class VideoCaptureImpl;
class VideoCaptureMessageFilter;

class CONTENT_EXPORT VideoCaptureImplManager {
 public:
  VideoCaptureImplManager();
  virtual ~VideoCaptureImplManager();

  
  
  
  
  
  base::Closure UseDevice(media::VideoCaptureSessionId id);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  base::Closure StartCapture(
      media::VideoCaptureSessionId id,
      const media::VideoCaptureParams& params,
      const VideoCaptureStateUpdateCB& state_update_cb,
      const VideoCaptureDeliverFrameCB& deliver_frame_cb);

  
  
  void GetDeviceSupportedFormats(
      media::VideoCaptureSessionId id,
      const VideoCaptureDeviceFormatsCB& callback);

  
  
  void GetDeviceFormatsInUse(
      media::VideoCaptureSessionId id,
      const VideoCaptureDeviceFormatsCB& callback);

  
  
  void SuspendDevices(bool suspend);

  VideoCaptureMessageFilter* video_capture_message_filter() const {
    return filter_.get();
  }

 protected:
  virtual VideoCaptureImpl* CreateVideoCaptureImplForTesting(
      media::VideoCaptureSessionId id,
      VideoCaptureMessageFilter* filter) const;

 private:
  void StopCapture(int client_id, media::VideoCaptureSessionId id);
  void UnrefDevice(media::VideoCaptureSessionId id);

  
  
  
  
  typedef std::map<media::VideoCaptureSessionId,
                   std::pair<int, VideoCaptureImpl*> >
      VideoCaptureDeviceMap;
  VideoCaptureDeviceMap devices_;

  
  
  int next_client_id_;

  scoped_refptr<VideoCaptureMessageFilter> filter_;

  
  base::ThreadChecker thread_checker_;

  
  
  base::WeakPtrFactory<VideoCaptureImplManager> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoCaptureImplManager);
};

}  

#endif  
