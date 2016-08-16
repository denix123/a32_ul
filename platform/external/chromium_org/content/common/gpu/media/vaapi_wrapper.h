// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_MEDIA_VAAPI_WRAPPER_H_
#define CONTENT_COMMON_GPU_MEDIA_VAAPI_WRAPPER_H_

#include <set>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/synchronization/lock.h"
#include "content/common/content_export.h"
#include "content/common/gpu/media/va_surface.h"
#include "media/base/video_decoder_config.h"
#include "media/base/video_frame.h"
#include "third_party/libva/va/va_x11.h"
#include "ui/gfx/size.h"

namespace content {

class CONTENT_EXPORT VaapiWrapper {
 public:
  enum CodecMode {
    kDecode,
    kEncode,
  };

  
  
  static scoped_ptr<VaapiWrapper> Create(
      CodecMode mode,
      media::VideoCodecProfile profile,
      Display* x_display,
      const base::Closure& report_error_to_uma_cb);

  
  static std::vector<media::VideoCodecProfile> GetSupportedEncodeProfiles(
      Display* x_display,
      const base::Closure& report_error_to_uma_cb);

  ~VaapiWrapper();

  
  
  
  
  
  
  
  bool CreateSurfaces(gfx::Size size,
                      size_t num_surfaces,
                      std::vector<VASurfaceID>* va_surfaces);

  
  void DestroySurfaces();

  
  
  
  
  
  
  bool SubmitBuffer(VABufferType va_buffer_type, size_t size, void* buffer);

  
  
  
  
  
  
  bool SubmitVAEncMiscParamBuffer(VAEncMiscParameterType misc_param_type,
                                  size_t size,
                                  void* buffer);

  
  
  void DestroyPendingBuffers();

  
  
  bool ExecuteAndDestroyPendingBuffers(VASurfaceID va_surface_id);

  
  
  bool PutSurfaceIntoPixmap(VASurfaceID va_surface_id,
                            Pixmap x_pixmap,
                            gfx::Size dest_size);

  
  bool VAAPIVersionLessThan(int major, int minor);

  
  
  
  bool GetVaImageForTesting(VASurfaceID va_surface_id,
                            VAImage* image,
                            void** mem);

  
  
  void ReturnVaImageForTesting(VAImage* image);

  
  bool UploadVideoFrameToSurface(const scoped_refptr<media::VideoFrame>& frame,
                                 VASurfaceID va_surface_id);

  
  bool CreateCodedBuffer(size_t size, VABufferID* buffer_id);

  
  
  
  
  
  
  bool DownloadAndDestroyCodedBuffer(VABufferID buffer_id,
                                     VASurfaceID sync_surface_id,
                                     uint8* target_ptr,
                                     size_t target_size,
                                     size_t* coded_data_size);

  
  void DestroyCodedBuffers();

 private:
  VaapiWrapper();

  bool Initialize(CodecMode mode,
                  media::VideoCodecProfile profile,
                  Display* x_display,
                  const base::Closure& report_error_to_uma_cb);
  void Deinitialize();
  bool VaInitialize(Display* x_display,
                    const base::Closure& report_error_to_uma_cb);
  bool GetSupportedVaProfiles(std::vector<VAProfile>* profiles);
  bool IsEntrypointSupported(VAProfile va_profile, VAEntrypoint entrypoint);
  bool AreAttribsSupported(VAProfile va_profile,
                           VAEntrypoint entrypoint,
                           const std::vector<VAConfigAttrib>& required_attribs);

  
  
  
  bool Execute(VASurfaceID va_surface_id);

  
  void TryToSetVADisplayAttributeToLocalGPU();

  
  
  static bool PostSandboxInitialization();

  
  
  
  base::Lock va_lock_;

  
  std::vector<VASurfaceID> va_surface_ids_;

  
  int major_version_, minor_version_;

  
  
  VADisplay va_display_;
  VAConfigID va_config_id_;
  
  
  VAContextID va_context_id_;

  
  std::vector<VABufferID> pending_slice_bufs_;
  std::vector<VABufferID> pending_va_bufs_;

  
  std::set<VABufferID> coded_buffers_;

  
  
  base::Closure report_error_to_uma_cb_;

  DISALLOW_COPY_AND_ASSIGN(VaapiWrapper);
};

}  

#endif  
