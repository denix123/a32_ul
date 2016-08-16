// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_ANDROID_STREAM_TEXTURE_FACTORY_H_
#define CONTENT_RENDERER_MEDIA_ANDROID_STREAM_TEXTURE_FACTORY_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop_proxy.h"
#include "cc/layers/video_frame_provider.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "ui/gfx/size.h"

namespace gpu {
namespace gles2 {
class GLES2Interface;
}  
}  

namespace content {

class StreamTextureProxy {
 public:
  virtual ~StreamTextureProxy() {}

  
  
  
  virtual void BindToLoop(int32 stream_id,
                          cc::VideoFrameProvider::Client* client,
                          scoped_refptr<base::MessageLoopProxy> loop) = 0;

  
  virtual void Release() = 0;

  struct Deleter {
    inline void operator()(StreamTextureProxy* ptr) const { ptr->Release(); }
  };
};

typedef scoped_ptr<StreamTextureProxy, StreamTextureProxy::Deleter>
    ScopedStreamTextureProxy;

class StreamTextureFactoryContextObserver {
 public:
  virtual ~StreamTextureFactoryContextObserver() {}
  virtual void ResetStreamTextureProxy() = 0;
};

class StreamTextureFactory : public base::RefCounted<StreamTextureFactory> {
 public:
  
  virtual StreamTextureProxy* CreateProxy() = 0;

  
  
  
  
  virtual void EstablishPeer(int32 stream_id, int player_id) = 0;

  
  
  
  virtual unsigned CreateStreamTexture(unsigned texture_target,
                                       unsigned* texture_id,
                                       gpu::Mailbox* texture_mailbox) = 0;

  
  virtual void SetStreamTextureSize(int32 texture_id,
                                    const gfx::Size& size) = 0;

  virtual gpu::gles2::GLES2Interface* ContextGL() = 0;

  virtual void AddObserver(StreamTextureFactoryContextObserver* obs) = 0;
  virtual void RemoveObserver(StreamTextureFactoryContextObserver* obs) = 0;

 protected:
  friend class base::RefCounted<StreamTextureFactory>;
  virtual ~StreamTextureFactory() {}
};

}  

#endif  
