// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_TESTS_GL_MANAGER_H_
#define GPU_COMMAND_BUFFER_TESTS_GL_MANAGER_H_

#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "gpu/command_buffer/client/gpu_control.h"
#include "gpu/command_buffer/service/feature_info.h"
#include "ui/gfx/size.h"

namespace gfx {

class GLContext;
class GLShareGroup;
class GLSurface;

}

namespace gpu {

class CommandBufferService;
class GpuScheduler;
class TransferBuffer;

namespace gles2 {

class ContextGroup;
class MailboxManager;
class GLES2Decoder;
class GLES2CmdHelper;
class GLES2Implementation;
class ImageManager;
class ShareGroup;

};

class GLManager : private GpuControl {
 public:
  struct Options {
    Options();
    
    gfx::Size size;
    
    GLManager* share_group_manager;
    
    GLManager* share_mailbox_manager;
    
    GLManager* virtual_manager;
    
    bool bind_generates_resource;
    
    bool lose_context_when_out_of_memory;
    
    bool context_lost_allowed;
  };
  GLManager();
  virtual ~GLManager();

  void Initialize(const Options& options);
  void Destroy();

  void MakeCurrent();

  void SetSurface(gfx::GLSurface* surface);

  gles2::GLES2Decoder* decoder() const {
    return decoder_.get();
  }

  gles2::MailboxManager* mailbox_manager() const {
    return mailbox_manager_.get();
  }

  gfx::GLShareGroup* share_group() const {
    return share_group_.get();
  }

  gles2::GLES2Implementation* gles2_implementation() const {
    return gles2_implementation_.get();
  }

  gfx::GLContext* context() {
    return context_.get();
  }

  const gpu::gles2::FeatureInfo::Workarounds& workarounds() const;

  
  virtual Capabilities GetCapabilities() OVERRIDE;
  virtual gfx::GpuMemoryBuffer* CreateGpuMemoryBuffer(size_t width,
                                                      size_t height,
                                                      unsigned internalformat,
                                                      unsigned usage,
                                                      int32* id) OVERRIDE;
  virtual void DestroyGpuMemoryBuffer(int32 id) OVERRIDE;
  virtual uint32 InsertSyncPoint() OVERRIDE;
  virtual uint32 InsertFutureSyncPoint() OVERRIDE;
  virtual void RetireSyncPoint(uint32 sync_point) OVERRIDE;
  virtual void SignalSyncPoint(uint32 sync_point,
                               const base::Closure& callback) OVERRIDE;
  virtual void SignalQuery(uint32 query,
                           const base::Closure& callback) OVERRIDE;
  virtual void SetSurfaceVisible(bool visible) OVERRIDE;
  virtual void Echo(const base::Closure& callback) OVERRIDE;
  virtual uint32 CreateStreamTexture(uint32 texture_id) OVERRIDE;

 private:
  void PumpCommands();
  bool GetBufferChanged(int32 transfer_buffer_id);
  void SetupBaseContext();

  scoped_refptr<gles2::MailboxManager> mailbox_manager_;
  scoped_refptr<gfx::GLShareGroup> share_group_;
  scoped_ptr<CommandBufferService> command_buffer_;
  scoped_ptr<gles2::GLES2Decoder> decoder_;
  scoped_ptr<GpuScheduler> gpu_scheduler_;
  scoped_refptr<gfx::GLSurface> surface_;
  scoped_refptr<gfx::GLContext> context_;
  scoped_ptr<gles2::GLES2CmdHelper> gles2_helper_;
  scoped_ptr<TransferBuffer> transfer_buffer_;
  scoped_ptr<gles2::GLES2Implementation> gles2_implementation_;
  bool context_lost_allowed_;

  
  base::ScopedPtrHashMap<int32, gfx::GpuMemoryBuffer> gpu_memory_buffers_;

  
  static int use_count_;
  static scoped_refptr<gfx::GLShareGroup>* base_share_group_;
  static scoped_refptr<gfx::GLSurface>* base_surface_;
  static scoped_refptr<gfx::GLContext>* base_context_;
};

}  

#endif  
