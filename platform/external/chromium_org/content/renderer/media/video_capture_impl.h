// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#ifndef CONTENT_RENDERER_MEDIA_VIDEO_CAPTURE_IMPL_H_
#define CONTENT_RENDERER_MEDIA_VIDEO_CAPTURE_IMPL_H_

#include <list>
#include <map>

#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "content/common/content_export.h"
#include "content/common/media/video_capture.h"
#include "content/public/renderer/media_stream_video_sink.h"
#include "content/renderer/media/video_capture_message_filter.h"
#include "media/video/capture/video_capture_types.h"

namespace base {
class MessageLoopProxy;
}  

namespace gpu {
struct MailboxHolder;
}  

namespace media {
class VideoFrame;
}  

namespace content {

class CONTENT_EXPORT VideoCaptureImpl
    : public VideoCaptureMessageFilter::Delegate {
 public:
  virtual ~VideoCaptureImpl();

  VideoCaptureImpl(media::VideoCaptureSessionId session_id,
                   VideoCaptureMessageFilter* filter);

  
  void Init();

  
  void DeInit();

  
  void SuspendCapture(bool suspend);

  
  
  
  
  
  void StartCapture(
      int client_id,
      const media::VideoCaptureParams& params,
      const VideoCaptureStateUpdateCB& state_update_cb,
      const VideoCaptureDeliverFrameCB& deliver_frame_cb);

  
  void StopCapture(int client_id);

  
  
  void GetDeviceSupportedFormats(
      const VideoCaptureDeviceFormatsCB& callback);

  
  
  void GetDeviceFormatsInUse(
      const VideoCaptureDeviceFormatsCB& callback);

  media::VideoCaptureSessionId session_id() const { return session_id_; }

 private:
  friend class VideoCaptureImplTest;
  friend class MockVideoCaptureImpl;

  
  
  class ClientBuffer;

  
  
  struct ClientInfo {
    ClientInfo();
    ~ClientInfo();
    media::VideoCaptureParams params;
    VideoCaptureStateUpdateCB state_update_cb;
    VideoCaptureDeliverFrameCB deliver_frame_cb;
  };
  typedef std::map<int, ClientInfo> ClientInfoMap;

  
  virtual void OnBufferCreated(base::SharedMemoryHandle handle,
                               int length,
                               int buffer_id) OVERRIDE;
  virtual void OnBufferDestroyed(int buffer_id) OVERRIDE;
  virtual void OnBufferReceived(int buffer_id,
                                const media::VideoCaptureFormat& format,
                                const gfx::Rect& visible_rect,
                                base::TimeTicks) OVERRIDE;
  virtual void OnMailboxBufferReceived(int buffer_id,
                                       const gpu::MailboxHolder& mailbox_holder,
                                       const media::VideoCaptureFormat& format,
                                       base::TimeTicks timestamp) OVERRIDE;
  virtual void OnStateChanged(VideoCaptureState state) OVERRIDE;
  virtual void OnDeviceSupportedFormatsEnumerated(
      const media::VideoCaptureFormats& supported_formats) OVERRIDE;
  virtual void OnDeviceFormatsInUseReceived(
      const media::VideoCaptureFormats& formats_in_use) OVERRIDE;
  virtual void OnDelegateAdded(int32 device_id) OVERRIDE;

  
  
  void OnClientBufferFinished(int buffer_id,
                              const scoped_refptr<ClientBuffer>& buffer,
                              uint32 release_sync_point);

  void StopDevice();
  void RestartCapture();
  void StartCaptureInternal();

  virtual void Send(IPC::Message* message);

  
  bool RemoveClient(int client_id, ClientInfoMap* clients);

  const scoped_refptr<VideoCaptureMessageFilter> message_filter_;
  int device_id_;
  const int session_id_;

  
  
  std::vector<VideoCaptureDeviceFormatsCB> device_formats_cb_queue_;
  
  
  std::vector<VideoCaptureDeviceFormatsCB> device_formats_in_use_cb_queue_;

  
  typedef std::map<int32, scoped_refptr<ClientBuffer> > ClientBufferMap;
  ClientBufferMap client_buffers_;

  ClientInfoMap clients_;
  ClientInfoMap clients_pending_on_filter_;
  ClientInfoMap clients_pending_on_restart_;

  
  
  media::VideoCaptureParams params_;

  
  media::VideoCaptureFormat last_frame_format_;

  
  base::TimeTicks first_frame_timestamp_;

  bool suspended_;
  VideoCaptureState state_;

  
  base::ThreadChecker thread_checker_;

  
  
  
  
  base::WeakPtrFactory<VideoCaptureImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoCaptureImpl);
};

}  

#endif  
