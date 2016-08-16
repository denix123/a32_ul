// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_VIDEO_FRAME_H_
#define MEDIA_BASE_VIDEO_FRAME_H_

#include <vector>

#include "base/callback.h"
#include "base/md5.h"
#include "base/memory/shared_memory.h"
#include "base/synchronization/lock.h"
#include "media/base/buffers.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"

#if defined(OS_MACOSX)
#include <CoreVideo/CVPixelBuffer.h>
#include "base/mac/scoped_cftyperef.h"
#endif

class SkBitmap;

namespace gpu {
struct MailboxHolder;
}  

namespace media {

class MEDIA_EXPORT VideoFrame : public base::RefCountedThreadSafe<VideoFrame> {
 public:
  enum {
    kFrameSizeAlignment = 16,
    kFrameSizePadding = 16,
    kFrameAddressAlignment = 32
  };

  enum {
    kMaxPlanes = 4,

    kYPlane = 0,
    kUPlane = 1,
    kUVPlane = kUPlane,
    kVPlane = 2,
    kAPlane = 3,
  };

  
  
  
  
  enum Format {
    UNKNOWN = 0,  
    YV12 = 1,  
    YV16 = 2,  
    I420 = 3,  
    YV12A = 4,  
#if defined(VIDEO_HOLE)
    HOLE = 5,  
#endif  
    NATIVE_TEXTURE = 6,  
    YV12J = 7,  
    NV12 = 8,  
    YV24 = 9,  
    FORMAT_MAX = YV24,  
  };

  
  static std::string FormatToString(Format format);

  
  
  static scoped_refptr<VideoFrame> CreateFrame(
      Format format,
      const gfx::Size& coded_size,
      const gfx::Rect& visible_rect,
      const gfx::Size& natural_size,
      base::TimeDelta timestamp);

  
  
  
  static bool IsValidConfig(Format format, const gfx::Size& coded_size,
                            const gfx::Rect& visible_rect,
                            const gfx::Size& natural_size);

  
  
  typedef base::Callback<void(const SkBitmap&)> ReadPixelsCB;

  
  
  typedef base::Callback<void(uint32)> ReleaseMailboxCB;

  
  
  
  
  
  
  static scoped_refptr<VideoFrame> WrapNativeTexture(
      scoped_ptr<gpu::MailboxHolder> mailbox_holder,
      const ReleaseMailboxCB& mailbox_holder_release_cb,
      const gfx::Size& coded_size,
      const gfx::Rect& visible_rect,
      const gfx::Size& natural_size,
      base::TimeDelta timestamp,
      const ReadPixelsCB& read_pixels_cb);

#if !defined(MEDIA_FOR_CAST_IOS)
  
  
  
  void ReadPixelsFromNativeTexture(const SkBitmap& pixels);
#endif

  
  
  
  
  
  
  
  static scoped_refptr<VideoFrame> WrapExternalPackedMemory(
      Format format,
      const gfx::Size& coded_size,
      const gfx::Rect& visible_rect,
      const gfx::Size& natural_size,
      uint8* data,
      size_t data_size,
      base::SharedMemoryHandle handle,
      base::TimeDelta timestamp,
      const base::Closure& no_longer_needed_cb);

#if defined(OS_POSIX)
  
  
  
  
  
  
  
  
  
  
  
  static scoped_refptr<VideoFrame> WrapExternalDmabufs(
      Format format,
      const gfx::Size& coded_size,
      const gfx::Rect& visible_rect,
      const gfx::Size& natural_size,
      const std::vector<int> dmabuf_fds,
      base::TimeDelta timestamp,
      const base::Closure& no_longer_needed_cb);
#endif

#if defined(OS_MACOSX)
  
  
  
  
  
  
  
  
  static scoped_refptr<VideoFrame> WrapCVPixelBuffer(
      CVPixelBufferRef cv_pixel_buffer,
      base::TimeDelta timestamp);
#endif

  
  
  
  
  
  static scoped_refptr<VideoFrame> WrapExternalYuvData(
      Format format,
      const gfx::Size& coded_size,
      const gfx::Rect& visible_rect,
      const gfx::Size& natural_size,
      int32 y_stride,
      int32 u_stride,
      int32 v_stride,
      uint8* y_data,
      uint8* u_data,
      uint8* v_data,
      base::TimeDelta timestamp,
      const base::Closure& no_longer_needed_cb);

  
  
  
  static scoped_refptr<VideoFrame> WrapVideoFrame(
      const scoped_refptr<VideoFrame>& frame,
      const gfx::Rect& visible_rect,
      const gfx::Size& natural_size,
      const base::Closure& no_longer_needed_cb);

  
  static scoped_refptr<VideoFrame> CreateEOSFrame();

  
  static scoped_refptr<VideoFrame> CreateColorFrame(
      const gfx::Size& size,
      uint8 y, uint8 u, uint8 v,
      base::TimeDelta timestamp);

  
  
  static scoped_refptr<VideoFrame> CreateBlackFrame(const gfx::Size& size);

  
  
  static scoped_refptr<VideoFrame> CreateTransparentFrame(
      const gfx::Size& size);

#if defined(VIDEO_HOLE)
  
  static scoped_refptr<VideoFrame> CreateHoleFrame(const gfx::Size& size);
#endif  

  static size_t NumPlanes(Format format);

  
  
  static size_t AllocationSize(Format format, const gfx::Size& coded_size);

  
  static gfx::Size PlaneSize(Format format,
                             size_t plane,
                             const gfx::Size& coded_size);

  
  
  static size_t PlaneAllocationSize(Format format,
                                    size_t plane,
                                    const gfx::Size& coded_size);

  
  static int PlaneHorizontalBitsPerPixel(Format format, size_t plane);

  
  
  static size_t RowBytes(size_t plane, Format format, int width);

  
  
  static size_t Rows(size_t plane, Format format, int height);

  Format format() const { return format_; }

  const gfx::Size& coded_size() const { return coded_size_; }
  const gfx::Rect& visible_rect() const { return visible_rect_; }
  const gfx::Size& natural_size() const { return natural_size_; }

  int stride(size_t plane) const;

  
  
  
  
  int row_bytes(size_t plane) const;
  int rows(size_t plane) const;

  
  
  uint8* data(size_t plane) const;

  
  
  
  const gpu::MailboxHolder* mailbox_holder() const;

  
  base::SharedMemoryHandle shared_memory_handle() const;

#if defined(OS_POSIX)
  
  int dmabuf_fd(size_t plane) const;
#endif

#if defined(OS_MACOSX)
  
  CVPixelBufferRef cv_pixel_buffer() const;
#endif

  
  bool end_of_stream() const { return end_of_stream_; }

  base::TimeDelta timestamp() const {
    return timestamp_;
  }
  void set_timestamp(const base::TimeDelta& timestamp) {
    timestamp_ = timestamp;
  }

  class SyncPointClient {
   public:
    SyncPointClient() {}
    virtual uint32 InsertSyncPoint() = 0;
    virtual void WaitSyncPoint(uint32 sync_point) = 0;

   protected:
    virtual ~SyncPointClient() {}

    DISALLOW_COPY_AND_ASSIGN(SyncPointClient);
  };
  
  
  
  
  void UpdateReleaseSyncPoint(SyncPointClient* client);

  
  
  void HashFrameForTesting(base::MD5Context* context);

 private:
  friend class base::RefCountedThreadSafe<VideoFrame>;

  
  
  static bool IsValidPlane(size_t plane, VideoFrame::Format format);

  
  VideoFrame(Format format,
             const gfx::Size& coded_size,
             const gfx::Rect& visible_rect,
             const gfx::Size& natural_size,
             scoped_ptr<gpu::MailboxHolder> mailbox_holder,
             base::TimeDelta timestamp,
             bool end_of_stream);
  virtual ~VideoFrame();

  void AllocateYUV();

  
  const Format format_;

  
  
  
  
  
  const gfx::Size coded_size_;

  
  
  
  const gfx::Rect visible_rect_;

  
  
  const gfx::Size natural_size_;

  
  
  
  int32 strides_[kMaxPlanes];

  
  uint8* data_[kMaxPlanes];

  
  const scoped_ptr<gpu::MailboxHolder> mailbox_holder_;
  ReleaseMailboxCB mailbox_holder_release_cb_;
  ReadPixelsCB read_pixels_cb_;

  
  base::SharedMemoryHandle shared_memory_handle_;

#if defined(OS_POSIX)
  
  
  base::ScopedFD dmabuf_fds_[kMaxPlanes];
#endif

#if defined(OS_MACOSX)
  
  base::ScopedCFTypeRef<CVPixelBufferRef> cv_pixel_buffer_;
#endif

  base::Closure no_longer_needed_cb_;

  base::TimeDelta timestamp_;

  base::Lock release_sync_point_lock_;
  uint32 release_sync_point_;

  const bool end_of_stream_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(VideoFrame);
};

}  

#endif  
