// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_VIDEO_DECODER_RESOURCE_H_
#define PPAPI_PROXY_VIDEO_DECODER_RESOURCE_H_

#include <queue>

#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "ppapi/proxy/connection.h"
#include "ppapi/proxy/plugin_resource.h"
#include "ppapi/proxy/ppapi_proxy_export.h"
#include "ppapi/shared_impl/resource.h"
#include "ppapi/shared_impl/scoped_pp_resource.h"
#include "ppapi/thunk/ppb_video_decoder_api.h"

namespace gpu {
struct Mailbox;
namespace gles2 {
class GLES2Implementation;
}
}

namespace ppapi {

class PPB_Graphics3D_Shared;
class TrackedCallback;

namespace proxy {

class PPAPI_PROXY_EXPORT VideoDecoderResource
    : public PluginResource,
      public thunk::PPB_VideoDecoder_API {
 public:
  VideoDecoderResource(Connection connection, PP_Instance instance);
  virtual ~VideoDecoderResource();

  
  virtual thunk::PPB_VideoDecoder_API* AsPPB_VideoDecoder_API() OVERRIDE;

  
  virtual int32_t Initialize0_1(
      PP_Resource graphics_context,
      PP_VideoProfile profile,
      PP_Bool allow_software_fallback,
      scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual int32_t Initialize(PP_Resource graphics_context,
                             PP_VideoProfile profile,
                             PP_HardwareAcceleration acceleration,
                             scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual int32_t Decode(uint32_t decode_id,
                         uint32_t size,
                         const void* buffer,
                         scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual int32_t GetPicture(PP_VideoPicture* picture,
                             scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual void RecyclePicture(const PP_VideoPicture* picture) OVERRIDE;
  virtual int32_t Flush(scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual int32_t Reset(scoped_refptr<TrackedCallback> callback) OVERRIDE;

  
  virtual void OnReplyReceived(const ResourceMessageReplyParams& params,
                               const IPC::Message& msg) OVERRIDE;

  
  
  void SetForTest();

 private:
  
  struct ShmBuffer {
    ShmBuffer(scoped_ptr<base::SharedMemory> shm,
              uint32_t size,
              uint32_t shm_id);
    ~ShmBuffer();

    const scoped_ptr<base::SharedMemory> shm;
    void* addr;
    
    
    const uint32_t shm_id;
  };

  
  struct Texture {
    Texture(uint32_t texture_target, const PP_Size& size);
    ~Texture();

    const uint32_t texture_target;
    const PP_Size size;
  };

  
  struct Picture {
    Picture(int32_t decode_id, uint32_t texture_id);
    ~Picture();

    int32_t decode_id;
    uint32_t texture_id;
  };

  int32_t InitializeInternal(PP_Resource graphics_context,
                             PP_VideoProfile profile,
                             PP_Bool allow_software_fallback,
                             scoped_refptr<TrackedCallback> callback,
                             bool testing);

  
  void OnPluginMsgRequestTextures(const ResourceMessageReplyParams& params,
                                  uint32_t num_textures,
                                  const PP_Size& size,
                                  uint32_t texture_target,
                                  const std::vector<gpu::Mailbox>& mailboxes);
  void OnPluginMsgPictureReady(const ResourceMessageReplyParams& params,
                               int32_t decode_id,
                               uint32_t texture_id);
  void OnPluginMsgDismissPicture(const ResourceMessageReplyParams& params,
                                 uint32_t texture_id);
  void OnPluginMsgNotifyError(const ResourceMessageReplyParams& params,
                              int32_t error);

  
  void OnPluginMsgInitializeComplete(const ResourceMessageReplyParams& params);
  void OnPluginMsgDecodeComplete(const ResourceMessageReplyParams& params,
                                 uint32_t shm_id);
  void OnPluginMsgFlushComplete(const ResourceMessageReplyParams& params);
  void OnPluginMsgResetComplete(const ResourceMessageReplyParams& params);

  void RunCallbackWithError(scoped_refptr<TrackedCallback>* callback);
  void DeleteGLTexture(uint32_t texture_id);
  void WriteNextPicture(PP_VideoPicture* picture);

  
  ScopedVector<ShmBuffer> shm_buffers_;

  
  typedef std::vector<ShmBuffer*> ShmBufferList;
  ShmBufferList available_shm_buffers_;

  
  typedef base::hash_map<uint32_t, Texture> TextureMap;
  TextureMap textures_;

  
  typedef std::queue<Picture> PictureQueue;
  PictureQueue received_pictures_;

  
  scoped_refptr<TrackedCallback> initialize_callback_;
  scoped_refptr<TrackedCallback> decode_callback_;
  scoped_refptr<TrackedCallback> get_picture_callback_;
  scoped_refptr<TrackedCallback> flush_callback_;
  scoped_refptr<TrackedCallback> reset_callback_;

  
  int32_t num_decodes_;
  
  
  
  
  
  
  static const int kMaximumPictureDelay = 128;
  uint32_t decode_ids_[kMaximumPictureDelay];

  
  PP_VideoPicture* get_picture_;

  ScopedPPResource graphics3d_;
  gpu::gles2::GLES2Implementation* gles2_impl_;

  bool initialized_;
  bool testing_;
  int32_t decoder_last_error_;

  DISALLOW_COPY_AND_ASSIGN(VideoDecoderResource);
};

}  
}  

#endif  
