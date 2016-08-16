// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_RESOURCE_PROVIDER_H_
#define CC_RESOURCES_RESOURCE_PROVIDER_H_

#include <deque>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "cc/base/cc_export.h"
#include "cc/output/context_provider.h"
#include "cc/output/output_surface.h"
#include "cc/resources/release_callback_impl.h"
#include "cc/resources/resource_format.h"
#include "cc/resources/return_callback.h"
#include "cc/resources/shared_bitmap.h"
#include "cc/resources/single_release_callback_impl.h"
#include "cc/resources/texture_mailbox.h"
#include "cc/resources/transferable_resource.h"
#include "third_party/khronos/GLES2/gl2.h"
#include "third_party/khronos/GLES2/gl2ext.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "third_party/skia/include/core/SkCanvas.h"
#include "ui/gfx/size.h"

class GrContext;

namespace gpu {
namespace gles {
class GLES2Interface;
}
}

namespace gfx {
class Rect;
class Vector2d;
}

namespace cc {
class BlockingTaskRunner;
class IdAllocator;
class SharedBitmap;
class SharedBitmapManager;
class TextureUploader;

class CC_EXPORT ResourceProvider {
 public:
  typedef unsigned ResourceId;
  typedef std::vector<ResourceId> ResourceIdArray;
  typedef std::set<ResourceId> ResourceIdSet;
  typedef base::hash_map<ResourceId, ResourceId> ResourceIdMap;
  enum TextureHint {
    TextureHintDefault = 0x0,
    TextureHintImmutable = 0x1,
    TextureHintFramebuffer = 0x2,
    TextureHintImmutableFramebuffer =
        TextureHintImmutable | TextureHintFramebuffer
  };
  enum ResourceType {
    InvalidType = 0,
    GLTexture = 1,
    Bitmap,
  };

  static scoped_ptr<ResourceProvider> Create(
      OutputSurface* output_surface,
      SharedBitmapManager* shared_bitmap_manager,
      BlockingTaskRunner* blocking_main_thread_task_runner,
      int highp_threshold_min,
      bool use_rgba_4444_texture_format,
      size_t id_allocation_chunk_size,
      bool use_distance_field_text);
  virtual ~ResourceProvider();

  void InitializeSoftware();
  void InitializeGL();

  void DidLoseOutputSurface() { lost_output_surface_ = true; }

  int max_texture_size() const { return max_texture_size_; }
  ResourceFormat memory_efficient_texture_format() const {
    return use_rgba_4444_texture_format_ ? RGBA_4444 : best_texture_format_;
  }
  ResourceFormat best_texture_format() const { return best_texture_format_; }
  bool use_sync_query() const { return use_sync_query_; }
  size_t num_resources() const { return resources_.size(); }

  
  bool InUseByConsumer(ResourceId id);

  bool IsLost(ResourceId id);
  bool AllowOverlay(ResourceId id);

  

  ResourceType default_resource_type() const { return default_resource_type_; }
  ResourceType GetResourceType(ResourceId id);

  
  ResourceId CreateResource(const gfx::Size& size,
                            GLint wrap_mode,
                            TextureHint hint,
                            ResourceFormat format);

  
  
  ResourceId CreateManagedResource(const gfx::Size& size,
                                   GLenum target,
                                   GLint wrap_mode,
                                   TextureHint hint,
                                   ResourceFormat format);

  
  ResourceId CreateGLTexture(const gfx::Size& size,
                             GLenum target,
                             GLenum texture_pool,
                             GLint wrap_mode,
                             TextureHint hint,
                             ResourceFormat format);

  ResourceId CreateBitmap(const gfx::Size& size, GLint wrap_mode);
  
  ResourceId CreateResourceFromIOSurface(const gfx::Size& size,
                                         unsigned io_surface_id);

  
  ResourceId CreateResourceFromTextureMailbox(
      const TextureMailbox& mailbox,
      scoped_ptr<SingleReleaseCallbackImpl> release_callback_impl);

  void DeleteResource(ResourceId id);

  
  
  void SetPixels(ResourceId id,
                 const uint8_t* image,
                 const gfx::Rect& image_rect,
                 const gfx::Rect& source_rect,
                 const gfx::Vector2d& dest_offset);

  
  size_t NumBlockingUploads();
  void MarkPendingUploadsAsNonBlocking();
  size_t EstimatedUploadsPerTick();
  void FlushUploads();
  void ReleaseCachedData();
  base::TimeTicks EstimatedUploadCompletionTime(size_t uploads_per_tick);

  
  
  bool ShallowFlushIfSupported();

  
  int CreateChild(const ReturnCallback& return_callback);

  
  void DestroyChild(int child);

  
  const ResourceIdMap& GetChildToParentMap(int child) const;

  
  
  
  
  void PrepareSendToParent(const ResourceIdArray& resources,
                           TransferableResourceArray* transferable_resources);

  
  
  
  
  
  
  
  
  
  void ReceiveFromChild(
      int child, const TransferableResourceArray& transferable_resources);

  
  
  
  void DeclareUsedResourcesFromChild(
      int child,
      const ResourceIdArray& resources_from_child);

  
  
  
  
  void ReceiveReturnsFromParent(
      const ReturnedResourceArray& transferable_resources);

  
  
  
  
  class CC_EXPORT ScopedReadLockGL {
   public:
    ScopedReadLockGL(ResourceProvider* resource_provider,
                     ResourceProvider::ResourceId resource_id);
    virtual ~ScopedReadLockGL();

    unsigned texture_id() const { return texture_id_; }

   protected:
    ResourceProvider* resource_provider_;
    ResourceProvider::ResourceId resource_id_;

   private:
    unsigned texture_id_;

    DISALLOW_COPY_AND_ASSIGN(ScopedReadLockGL);
  };

  class CC_EXPORT ScopedSamplerGL : public ScopedReadLockGL {
   public:
    ScopedSamplerGL(ResourceProvider* resource_provider,
                    ResourceProvider::ResourceId resource_id,
                    GLenum filter);
    ScopedSamplerGL(ResourceProvider* resource_provider,
                    ResourceProvider::ResourceId resource_id,
                    GLenum unit,
                    GLenum filter);
    virtual ~ScopedSamplerGL();

    GLenum target() const { return target_; }

   private:
    GLenum unit_;
    GLenum target_;

    DISALLOW_COPY_AND_ASSIGN(ScopedSamplerGL);
  };

  class CC_EXPORT ScopedWriteLockGL {
   public:
    ScopedWriteLockGL(ResourceProvider* resource_provider,
                      ResourceProvider::ResourceId resource_id);
    ~ScopedWriteLockGL();

    unsigned texture_id() const { return texture_id_; }

   private:
    ResourceProvider* resource_provider_;
    ResourceProvider::ResourceId resource_id_;
    unsigned texture_id_;

    DISALLOW_COPY_AND_ASSIGN(ScopedWriteLockGL);
  };

  class CC_EXPORT ScopedReadLockSoftware {
   public:
    ScopedReadLockSoftware(ResourceProvider* resource_provider,
                           ResourceProvider::ResourceId resource_id);
    ~ScopedReadLockSoftware();

    const SkBitmap* sk_bitmap() const {
      DCHECK(valid());
      return &sk_bitmap_;
    }
    GLint wrap_mode() const { return wrap_mode_; }

    bool valid() const { return !!sk_bitmap_.getPixels(); }

   private:
    ResourceProvider* resource_provider_;
    ResourceProvider::ResourceId resource_id_;
    SkBitmap sk_bitmap_;
    GLint wrap_mode_;

    DISALLOW_COPY_AND_ASSIGN(ScopedReadLockSoftware);
  };

  class CC_EXPORT ScopedWriteLockSoftware {
   public:
    ScopedWriteLockSoftware(ResourceProvider* resource_provider,
                            ResourceProvider::ResourceId resource_id);
    ~ScopedWriteLockSoftware();

    SkCanvas* sk_canvas() { return sk_canvas_.get(); }
    bool valid() const { return !!sk_bitmap_.getPixels(); }

   private:
    ResourceProvider* resource_provider_;
    ResourceProvider::ResourceId resource_id_;
    SkBitmap sk_bitmap_;
    scoped_ptr<SkCanvas> sk_canvas_;

    DISALLOW_COPY_AND_ASSIGN(ScopedWriteLockSoftware);
  };

  class Fence : public base::RefCounted<Fence> {
   public:
    Fence() {}

    virtual void Set() = 0;
    virtual bool HasPassed() = 0;

   protected:
    friend class base::RefCounted<Fence>;
    virtual ~Fence() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(Fence);
  };

  
  
  void AcquirePixelBuffer(ResourceId resource);
  void ReleasePixelBuffer(ResourceId resource);
  
  uint8_t* MapPixelBuffer(ResourceId id, int* stride);
  void UnmapPixelBuffer(ResourceId id);
  
  void BeginSetPixels(ResourceId id);
  void ForceSetPixelsToComplete(ResourceId id);
  bool DidSetPixelsComplete(ResourceId id);

  
  
  void AcquireImage(ResourceId id);
  void ReleaseImage(ResourceId id);
  
  
  uint8_t* MapImage(ResourceId id, int* stride);
  void UnmapImage(ResourceId id);

  
  void AcquireSkSurface(ResourceId id);
  void ReleaseSkSurface(ResourceId id);
  
  SkSurface* LockForWriteToSkSurface(ResourceId id);
  void UnlockForWriteToSkSurface(ResourceId id);

  
  
  void AllocateForTesting(ResourceId id);

  
  void CreateForTesting(ResourceId id);

  GLenum TargetForTesting(ResourceId id);

  
  
  
  void SetReadLockFence(Fence* fence) { current_read_lock_fence_ = fence; }

  
  void EnableReadLockFences(ResourceId id);

  
  bool CanLockForWrite(ResourceId id);

  
  void CopyResource(ResourceId source_id, ResourceId dest_id);

  void WaitSyncPointIfNeeded(ResourceId id);

  static GLint GetActiveTextureUnit(gpu::gles2::GLES2Interface* gl);

 private:
  struct Resource {
    enum Origin { Internal, External, Delegated };

    Resource();
    ~Resource();
    Resource(unsigned texture_id,
             const gfx::Size& size,
             Origin origin,
             GLenum target,
             GLenum filter,
             GLenum texture_pool,
             GLint wrap_mode,
             TextureHint hint,
             ResourceFormat format);
    Resource(uint8_t* pixels,
             SharedBitmap* bitmap,
             const gfx::Size& size,
             Origin origin,
             GLenum filter,
             GLint wrap_mode);
    Resource(const SharedBitmapId& bitmap_id,
             const gfx::Size& size,
             Origin origin,
             GLenum filter,
             GLint wrap_mode);

    int child_id;
    unsigned gl_id;
    
    unsigned gl_pixel_buffer_id;
    
    unsigned gl_upload_query_id;
    
    unsigned gl_read_lock_query_id;
    TextureMailbox mailbox;
    ReleaseCallbackImpl release_callback_impl;
    uint8_t* pixels;
    int lock_for_read_count;
    int imported_count;
    int exported_count;
    bool dirty_image : 1;
    bool locked_for_write : 1;
    bool lost : 1;
    bool marked_for_deletion : 1;
    bool pending_set_pixels : 1;
    bool set_pixels_completion_forced : 1;
    bool allocated : 1;
    bool read_lock_fences_enabled : 1;
    bool has_shared_bitmap_id : 1;
    bool allow_overlay : 1;
    scoped_refptr<Fence> read_lock_fence;
    gfx::Size size;
    Origin origin;
    GLenum target;
    
    GLenum original_filter;
    GLenum filter;
    unsigned image_id;
    unsigned bound_image_id;
    GLenum texture_pool;
    GLint wrap_mode;
    TextureHint hint;
    ResourceType type;
    ResourceFormat format;
    SharedBitmapId shared_bitmap_id;
    SharedBitmap* shared_bitmap;
    skia::RefPtr<SkSurface> sk_surface;
  };
  typedef base::hash_map<ResourceId, Resource> ResourceMap;

  static bool CompareResourceMapIteratorsByChildId(
      const std::pair<ReturnedResource, ResourceMap::iterator>& a,
      const std::pair<ReturnedResource, ResourceMap::iterator>& b);

  struct Child {
    Child();
    ~Child();

    ResourceIdMap child_to_parent_map;
    ResourceIdMap parent_to_child_map;
    ReturnCallback return_callback;
    ResourceIdSet in_use_resources;
    bool marked_for_deletion;
  };
  typedef base::hash_map<int, Child> ChildMap;

  bool ReadLockFenceHasPassed(const Resource* resource) {
    return !resource->read_lock_fence.get() ||
           resource->read_lock_fence->HasPassed();
  }

  ResourceProvider(OutputSurface* output_surface,
                   SharedBitmapManager* shared_bitmap_manager,
                   BlockingTaskRunner* blocking_main_thread_task_runner,
                   int highp_threshold_min,
                   bool use_rgba_4444_texture_format,
                   size_t id_allocation_chunk_size,
                   bool use_distance_field_text);

  void CleanUpGLIfNeeded();

  Resource* GetResource(ResourceId id);
  const Resource* LockForRead(ResourceId id);
  void UnlockForRead(ResourceId id);
  const Resource* LockForWrite(ResourceId id);
  void UnlockForWrite(ResourceId id);
  static void PopulateSkBitmapWithResource(SkBitmap* sk_bitmap,
                                           const Resource* resource);

  void TransferResource(gpu::gles2::GLES2Interface* gl,
                        ResourceId id,
                        TransferableResource* resource);
  enum DeleteStyle {
    Normal,
    ForShutdown,
  };
  void DeleteResourceInternal(ResourceMap::iterator it, DeleteStyle style);
  void DeleteAndReturnUnusedResourcesToChild(ChildMap::iterator child_it,
                                             DeleteStyle style,
                                             const ResourceIdArray& unused);
  void DestroyChildInternal(ChildMap::iterator it, DeleteStyle style);
  void LazyCreate(Resource* resource);
  void LazyAllocate(Resource* resource);

  void BindImageForSampling(Resource* resource);
  
  
  
  GLenum BindForSampling(ResourceId resource_id, GLenum unit, GLenum filter);

  
  gpu::gles2::GLES2Interface* ContextGL() const;
  class GrContext* GrContext() const;

  OutputSurface* output_surface_;
  SharedBitmapManager* shared_bitmap_manager_;
  BlockingTaskRunner* blocking_main_thread_task_runner_;
  bool lost_output_surface_;
  int highp_threshold_min_;
  ResourceId next_id_;
  ResourceMap resources_;
  int next_child_;
  ChildMap children_;

  ResourceType default_resource_type_;
  bool use_texture_storage_ext_;
  bool use_texture_format_bgra_;
  bool use_texture_usage_hint_;
  bool use_compressed_texture_etc1_;
  scoped_ptr<TextureUploader> texture_uploader_;
  int max_texture_size_;
  ResourceFormat best_texture_format_;

  base::ThreadChecker thread_checker_;

  scoped_refptr<Fence> current_read_lock_fence_;
  bool use_rgba_4444_texture_format_;

  const size_t id_allocation_chunk_size_;
  scoped_ptr<IdAllocator> texture_id_allocator_;
  scoped_ptr<IdAllocator> buffer_id_allocator_;

  bool use_sync_query_;

  bool use_distance_field_text_;

  DISALLOW_COPY_AND_ASSIGN(ResourceProvider);
};


inline unsigned BitsPerPixel(ResourceFormat format) {
  DCHECK_LE(format, RESOURCE_FORMAT_MAX);
  static const unsigned format_bits_per_pixel[RESOURCE_FORMAT_MAX + 1] = {
    32,  
    16,  
    32,  
    8,   
    8,   
    16,  
    4    
  };
  return format_bits_per_pixel[format];
}

inline GLenum GLDataType(ResourceFormat format) {
  DCHECK_LE(format, RESOURCE_FORMAT_MAX);
  static const unsigned format_gl_data_type[RESOURCE_FORMAT_MAX + 1] = {
    GL_UNSIGNED_BYTE,           
    GL_UNSIGNED_SHORT_4_4_4_4,  
    GL_UNSIGNED_BYTE,           
    GL_UNSIGNED_BYTE,           
    GL_UNSIGNED_BYTE,           
    GL_UNSIGNED_SHORT_5_6_5,    
    GL_UNSIGNED_BYTE            
  };
  return format_gl_data_type[format];
}

inline GLenum GLDataFormat(ResourceFormat format) {
  DCHECK_LE(format, RESOURCE_FORMAT_MAX);
  static const unsigned format_gl_data_format[RESOURCE_FORMAT_MAX + 1] = {
    GL_RGBA,           
    GL_RGBA,           
    GL_BGRA_EXT,       
    GL_ALPHA,          
    GL_LUMINANCE,      
    GL_RGB,            
    GL_ETC1_RGB8_OES   
  };
  return format_gl_data_format[format];
}

inline GLenum GLInternalFormat(ResourceFormat format) {
  return GLDataFormat(format);
}

}  

#endif  
