// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_PEPPER_PEPPER_MEDIA_STREAM_TRACK_HOST_BASE_H_
#define CONTENT_RENDERER_PEPPER_PEPPER_MEDIA_STREAM_TRACK_HOST_BASE_H_

#include "base/compiler_specific.h"
#include "content/common/content_export.h"
#include "ppapi/host/resource_host.h"
#include "ppapi/shared_impl/media_stream_buffer_manager.h"

namespace content {

class RendererPpapiHost;

class PepperMediaStreamTrackHostBase
    : public ppapi::host::ResourceHost,
      public ppapi::MediaStreamBufferManager::Delegate {
 protected:
  PepperMediaStreamTrackHostBase(RendererPpapiHost* host,
                                 PP_Instance instance,
                                 PP_Resource resource);
  virtual ~PepperMediaStreamTrackHostBase();

  enum TrackType {
    kRead,
    kWrite
  };
  bool InitBuffers(int32_t number_of_buffers,
                   int32_t buffer_size,
                   TrackType track_type);

  ppapi::MediaStreamBufferManager* buffer_manager() { return &buffer_manager_; }

  
  
  
  
  void SendEnqueueBufferMessageToPlugin(int32_t index);

  
  
  
  
  void SendEnqueueBuffersMessageToPlugin(const std::vector<int32_t>& indices);

  
  virtual int32_t OnResourceMessageReceived(
      const IPC::Message& msg,
      ppapi::host::HostMessageContext* context) OVERRIDE;

  
  virtual int32_t OnHostMsgEnqueueBuffer(
      ppapi::host::HostMessageContext* context, int32_t index);

 private:
  
  virtual void OnClose() = 0;

  
  int32_t OnHostMsgClose(ppapi::host::HostMessageContext* context);

  RendererPpapiHost* host_;

  ppapi::MediaStreamBufferManager buffer_manager_;

  DISALLOW_COPY_AND_ASSIGN(PepperMediaStreamTrackHostBase);
};

}  

#endif  
