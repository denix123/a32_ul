// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_MEDIA_STREAM_TRACK_RESOURCE_BASE_H_
#define PPAPI_PROXY_MEDIA_STREAM_TRACK_RESOURCE_BASE_H_

#include "ppapi/proxy/plugin_resource.h"
#include "ppapi/proxy/ppapi_proxy_export.h"
#include "ppapi/shared_impl/media_stream_buffer_manager.h"

namespace ppapi {
namespace proxy {

class PPAPI_PROXY_EXPORT MediaStreamTrackResourceBase
  : public PluginResource,
    public MediaStreamBufferManager::Delegate {
 protected:
  MediaStreamTrackResourceBase(Connection connection,
                               PP_Instance instance,
                               int pending_renderer_id,
                               const std::string& id);

  MediaStreamTrackResourceBase(Connection connection, PP_Instance instance);

  virtual ~MediaStreamTrackResourceBase();

  std::string id() const { return id_; }

  void set_id(const std::string& id) { id_ = id; }

  bool has_ended() const { return has_ended_; }

  MediaStreamBufferManager* buffer_manager() { return &buffer_manager_; }

  void CloseInternal();

  
  
  
  
  void SendEnqueueBufferMessageToHost(int32_t index);

  
  virtual void OnReplyReceived(const ResourceMessageReplyParams& params,
                               const IPC::Message& msg) OVERRIDE;

 private:
  
  void OnPluginMsgInitBuffers(const ResourceMessageReplyParams& params,
                              int32_t number_of_buffers,
                              int32_t buffer_size,
                              bool readonly);
  void OnPluginMsgEnqueueBuffer(const ResourceMessageReplyParams& params,
                                int32_t index);
  void OnPluginMsgEnqueueBuffers(const ResourceMessageReplyParams& params,
                                 const std::vector<int32_t>& indices);

  MediaStreamBufferManager buffer_manager_;

  std::string id_;

  bool has_ended_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamTrackResourceBase);
};

}  
}  

#endif  
