// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_CLIENT_GL_HELPER_H_
#define CONTENT_COMMON_GPU_CLIENT_GL_HELPER_H_

#include "base/atomicops.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/content_export.h"
#include "gpu/command_buffer/client/gles2_interface.h"
#include "gpu/command_buffer/common/mailbox_holder.h"
#include "third_party/skia/include/core/SkBitmap.h"

namespace gfx {
class Rect;
class Size;
}

namespace gpu {
class ContextSupport;
struct Mailbox;
}

namespace media {
class VideoFrame;
};

class SkRegion;

namespace content {

class GLHelperScaling;

class ScopedGLuint {
 public:
  typedef void (gpu::gles2::GLES2Interface::*GenFunc)(GLsizei n, GLuint* ids);
  typedef void (gpu::gles2::GLES2Interface::*DeleteFunc)(GLsizei n,
                                                         const GLuint* ids);
  ScopedGLuint(gpu::gles2::GLES2Interface* gl,
               GenFunc gen_func,
               DeleteFunc delete_func)
      : gl_(gl), id_(0u), delete_func_(delete_func) {
    (gl_->*gen_func)(1, &id_);
  }

  operator GLuint() const { return id_; }

  GLuint id() const { return id_; }

  ~ScopedGLuint() {
    if (id_ != 0) {
      (gl_->*delete_func_)(1, &id_);
    }
  }

 private:
  gpu::gles2::GLES2Interface* gl_;
  GLuint id_;
  DeleteFunc delete_func_;

  DISALLOW_COPY_AND_ASSIGN(ScopedGLuint);
};

class ScopedBuffer : public ScopedGLuint {
 public:
  explicit ScopedBuffer(gpu::gles2::GLES2Interface* gl)
      : ScopedGLuint(gl,
                     &gpu::gles2::GLES2Interface::GenBuffers,
                     &gpu::gles2::GLES2Interface::DeleteBuffers) {}
};

class ScopedFramebuffer : public ScopedGLuint {
 public:
  explicit ScopedFramebuffer(gpu::gles2::GLES2Interface* gl)
      : ScopedGLuint(gl,
                     &gpu::gles2::GLES2Interface::GenFramebuffers,
                     &gpu::gles2::GLES2Interface::DeleteFramebuffers) {}
};

class ScopedTexture : public ScopedGLuint {
 public:
  explicit ScopedTexture(gpu::gles2::GLES2Interface* gl)
      : ScopedGLuint(gl,
                     &gpu::gles2::GLES2Interface::GenTextures,
                     &gpu::gles2::GLES2Interface::DeleteTextures) {}
};

template <GLenum Target>
class ScopedBinder {
 public:
  typedef void (gpu::gles2::GLES2Interface::*BindFunc)(GLenum target,
                                                       GLuint id);
  ScopedBinder(gpu::gles2::GLES2Interface* gl, GLuint id, BindFunc bind_func)
      : gl_(gl), bind_func_(bind_func) {
    (gl_->*bind_func_)(Target, id);
  }

  virtual ~ScopedBinder() { (gl_->*bind_func_)(Target, 0); }

 private:
  gpu::gles2::GLES2Interface* gl_;
  BindFunc bind_func_;

  DISALLOW_COPY_AND_ASSIGN(ScopedBinder);
};

template <GLenum Target>
class ScopedBufferBinder : ScopedBinder<Target> {
 public:
  ScopedBufferBinder(gpu::gles2::GLES2Interface* gl, GLuint id)
      : ScopedBinder<Target>(gl, id, &gpu::gles2::GLES2Interface::BindBuffer) {}
};

template <GLenum Target>
class ScopedFramebufferBinder : ScopedBinder<Target> {
 public:
  ScopedFramebufferBinder(gpu::gles2::GLES2Interface* gl, GLuint id)
      : ScopedBinder<Target>(gl,
                             id,
                             &gpu::gles2::GLES2Interface::BindFramebuffer) {}
};

template <GLenum Target>
class ScopedTextureBinder : ScopedBinder<Target> {
 public:
  ScopedTextureBinder(gpu::gles2::GLES2Interface* gl, GLuint id)
      : ScopedBinder<Target>(gl, id, &gpu::gles2::GLES2Interface::BindTexture) {
  }
};

class ReadbackYUVInterface;
class GLHelperReadbackSupport;

class CONTENT_EXPORT GLHelper {
 public:
  GLHelper(gpu::gles2::GLES2Interface* gl,
           gpu::ContextSupport* context_support);
  ~GLHelper();

  enum ScalerQuality {
    
    SCALER_QUALITY_FAST = 1,

    
    
    
    SCALER_QUALITY_GOOD = 2,

    
    
    
    
    SCALER_QUALITY_BEST = 3,
  };

  
  
  
  
  
  
  
  
  void CropScaleReadbackAndCleanTexture(
      GLuint src_texture,
      const gfx::Size& src_size,
      const gfx::Rect& src_subrect,
      const gfx::Size& dst_size,
      unsigned char* out,
      const SkColorType out_color_type,
      const base::Callback<void(bool)>& callback,
      GLHelper::ScalerQuality quality);

  
  
  
  
  
  
  
  
  
  void CropScaleReadbackAndCleanMailbox(
      const gpu::Mailbox& src_mailbox,
      uint32 sync_point,
      const gfx::Size& src_size,
      const gfx::Rect& src_subrect,
      const gfx::Size& dst_size,
      unsigned char* out,
      const SkColorType out_color_type,
      const base::Callback<void(bool)>& callback,
      GLHelper::ScalerQuality quality);

  
  
  
  
  
  void ReadbackTextureSync(GLuint texture,
                           const gfx::Rect& src_rect,
                           unsigned char* out,
                           SkColorType format);

  void ReadbackTextureAsync(GLuint texture,
                            const gfx::Size& dst_size,
                            unsigned char* out,
                            SkColorType color_type,
                            const base::Callback<void(bool)>& callback);

  
  
  
  GLuint CopyTexture(GLuint texture, const gfx::Size& size);

  
  
  
  
  GLuint CopyAndScaleTexture(GLuint texture,
                             const gfx::Size& src_size,
                             const gfx::Size& dst_size,
                             bool vertically_flip_texture,
                             ScalerQuality quality);

  
  GLuint CompileShaderFromSource(const GLchar* source, GLenum type);

  
  
  void CopySubBufferDamage(GLuint texture,
                           GLuint previous_texture,
                           const SkRegion& new_damage,
                           const SkRegion& old_damage);

  
  GLuint CreateTexture();
  
  void DeleteTexture(GLuint texture_id);

  
  uint32 InsertSyncPoint();
  
  void WaitSyncPoint(uint32 sync_point);

  
  
  
  
  gpu::MailboxHolder ProduceMailboxHolderFromTexture(GLuint texture_id);

  
  
  GLuint ConsumeMailboxToTexture(const gpu::Mailbox& mailbox,
                                 uint32 sync_point);

  
  void ResizeTexture(GLuint texture, const gfx::Size& size);

  
  void CopyTextureSubImage(GLuint texture, const gfx::Rect& rect);

  
  
  void CopyTextureFullImage(GLuint texture, const gfx::Size& size);

  
  void Flush();


  
  
  
  
  class CONTENT_EXPORT ScalerInterface {
   public:
    ScalerInterface() {}
    virtual ~ScalerInterface() {}

    
    
    virtual void Scale(GLuint source_texture, GLuint dest_texture) = 0;
    virtual const gfx::Size& SrcSize() = 0;
    virtual const gfx::Rect& SrcSubrect() = 0;
    virtual const gfx::Size& DstSize() = 0;
  };

  
  
  
  
  ScalerInterface* CreateScaler(ScalerQuality quality,
                                const gfx::Size& src_size,
                                const gfx::Rect& src_subrect,
                                const gfx::Size& dst_size,
                                bool vertically_flip_texture,
                                bool swizzle);

  
  
  
  
  
  
  
  
  ReadbackYUVInterface* CreateReadbackPipelineYUV(ScalerQuality quality,
                                                  const gfx::Size& src_size,
                                                  const gfx::Rect& src_subrect,
                                                  const gfx::Size& dst_size,
                                                  const gfx::Rect& dst_subrect,
                                                  bool flip_vertically,
                                                  bool use_mrt);

  
  
  GLint MaxDrawBuffers();

  
  
  bool IsReadbackConfigSupported(SkColorType texture_format);

 protected:
  class CopyTextureToImpl;

  
  void InitCopyTextToImpl();
  
  void InitScalerImpl();

  enum ReadbackSwizzle {
    kSwizzleNone = 0,
    kSwizzleBGRA
  };

  gpu::gles2::GLES2Interface* gl_;
  gpu::ContextSupport* context_support_;
  scoped_ptr<CopyTextureToImpl> copy_texture_to_impl_;
  scoped_ptr<GLHelperScaling> scaler_impl_;
  scoped_ptr<GLHelperReadbackSupport> readback_support_;

  DISALLOW_COPY_AND_ASSIGN(GLHelper);
};

class CONTENT_EXPORT ReadbackYUVInterface {
 public:
  ReadbackYUVInterface() {}
  virtual ~ReadbackYUVInterface() {}

  
  virtual void ReadbackYUV(const gpu::Mailbox& mailbox,
                           uint32 sync_point,
                           const scoped_refptr<media::VideoFrame>& target,
                           const base::Callback<void(bool)>& callback) = 0;
  virtual GLHelper::ScalerInterface* scaler() = 0;
};

}  

#endif  
