// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_CLIENT_WEBGRAPHICSCONTEXT3D_COMMAND_BUFFER_IMPL_H_
#define CONTENT_COMMON_GPU_CLIENT_WEBGRAPHICSCONTEXT3D_COMMAND_BUFFER_IMPL_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "content/common/content_export.h"
#include "content/common/gpu/client/command_buffer_proxy_impl.h"
#include "third_party/WebKit/public/platform/WebGraphicsContext3D.h"
#include "third_party/WebKit/public/platform/WebString.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gl/gpu_preference.h"
#include "url/gurl.h"
#include "webkit/common/gpu/webgraphicscontext3d_impl.h"

namespace gpu {

class ContextSupport;
class TransferBuffer;

namespace gles2 {
class GLES2CmdHelper;
class GLES2Implementation;
class GLES2Interface;
}
}

namespace content {
class GpuChannelHost;

const size_t kDefaultCommandBufferSize = 1024 * 1024;
const size_t kDefaultStartTransferBufferSize = 1 * 1024 * 1024;
const size_t kDefaultMinTransferBufferSize = 1 * 256 * 1024;
const size_t kDefaultMaxTransferBufferSize = 16 * 1024 * 1024;

class WebGraphicsContext3DCommandBufferImpl
    : public webkit::gpu::WebGraphicsContext3DImpl {
 public:
  enum MappedMemoryReclaimLimit {
    kNoLimit = 0,
  };

  struct CONTENT_EXPORT SharedMemoryLimits {
    SharedMemoryLimits();

    size_t command_buffer_size;
    size_t start_transfer_buffer_size;
    size_t min_transfer_buffer_size;
    size_t max_transfer_buffer_size;
    size_t mapped_memory_reclaim_limit;
  };

  class ShareGroup : public base::RefCountedThreadSafe<ShareGroup> {
   public:
    ShareGroup();

    WebGraphicsContext3DCommandBufferImpl* GetAnyContextLocked() {
      
      
      
      lock_.AssertAcquired();
      if (contexts_.empty())
        return NULL;
      return contexts_.front();
    }

    void AddContextLocked(WebGraphicsContext3DCommandBufferImpl* context) {
      lock_.AssertAcquired();
      contexts_.push_back(context);
    }

    void RemoveContext(WebGraphicsContext3DCommandBufferImpl* context) {
      base::AutoLock auto_lock(lock_);
      contexts_.erase(std::remove(contexts_.begin(), contexts_.end(), context),
          contexts_.end());
    }

    void RemoveAllContexts() {
      base::AutoLock auto_lock(lock_);
      contexts_.clear();
    }

    base::Lock& lock() {
      return lock_;
    }

   private:
    friend class base::RefCountedThreadSafe<ShareGroup>;
    virtual ~ShareGroup();

    std::vector<WebGraphicsContext3DCommandBufferImpl*> contexts_;
    base::Lock lock_;

    DISALLOW_COPY_AND_ASSIGN(ShareGroup);
  };

  WebGraphicsContext3DCommandBufferImpl(
      int surface_id,
      const GURL& active_url,
      GpuChannelHost* host,
      const Attributes& attributes,
      bool lose_context_when_out_of_memory,
      const SharedMemoryLimits& limits,
      WebGraphicsContext3DCommandBufferImpl* share_context);

  virtual ~WebGraphicsContext3DCommandBufferImpl();

  CommandBufferProxyImpl* GetCommandBufferProxy() {
    return command_buffer_.get();
  }

  CONTENT_EXPORT gpu::ContextSupport* GetContextSupport();

  gpu::gles2::GLES2Implementation* GetImplementation() {
    return real_gl_.get();
  }

  
  
  bool IsCommandBufferContextLost();

  
  
  static CONTENT_EXPORT WebGraphicsContext3DCommandBufferImpl*
      CreateOffscreenContext(
          GpuChannelHost* host,
          const WebGraphicsContext3D::Attributes& attributes,
          bool lose_context_when_out_of_memory,
          const GURL& active_url,
          const SharedMemoryLimits& limits,
          WebGraphicsContext3DCommandBufferImpl* share_context);

  size_t GetMappedMemoryLimit() {
    return mem_limits_.mapped_memory_reclaim_limit;
  }

  
  virtual bool InitializeOnCurrentThread() OVERRIDE;

  
  
  virtual bool isContextLost();

  virtual WGC3Denum getGraphicsResetStatusARB();

 private:
  
  enum Error {
    SUCCESS               = 0x3000,
    BAD_ATTRIBUTE         = 0x3004,
    CONTEXT_LOST          = 0x300E
  };

  
  
  
  
  bool MaybeInitializeGL();

  bool InitializeCommandBuffer(bool onscreen,
      WebGraphicsContext3DCommandBufferImpl* share_context);

  void Destroy();

  
  
  
  
  
  
  
  
  
  
  
  
  
  bool CreateContext(bool onscreen);

  virtual void OnGpuChannelLost();

  bool lose_context_when_out_of_memory_;
  blink::WebGraphicsContext3D::Attributes attributes_;

  bool visible_;

  
  scoped_refptr<GpuChannelHost> host_;
  int32 surface_id_;
  GURL active_url_;

  gfx::GpuPreference gpu_preference_;

  scoped_ptr<CommandBufferProxyImpl> command_buffer_;
  scoped_ptr<gpu::gles2::GLES2CmdHelper> gles2_helper_;
  scoped_ptr<gpu::TransferBuffer> transfer_buffer_;
  scoped_ptr<gpu::gles2::GLES2Implementation> real_gl_;
  scoped_ptr<gpu::gles2::GLES2Interface> trace_gl_;
  Error last_error_;
  SharedMemoryLimits mem_limits_;
  scoped_refptr<ShareGroup> share_group_;

  
  
  
  base::WeakPtrFactory<WebGraphicsContext3DCommandBufferImpl> weak_ptr_factory_;
};

}  

#endif  
