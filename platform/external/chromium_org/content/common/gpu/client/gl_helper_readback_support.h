// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_CLIENT_GL_HELPER_READBACK_SUPPORT_H_
#define CONTENT_COMMON_GPU_CLIENT_GL_HELPER_READBACK_SUPPORT_H_

#include <vector>

#include "content/common/gpu/client/gl_helper.h"

namespace content {

class CONTENT_EXPORT GLHelperReadbackSupport {
 public:
  enum FormatSupport { SUPPORTED, SWIZZLE, NOT_SUPPORTED };

  GLHelperReadbackSupport(gpu::gles2::GLES2Interface* gl);

  ~GLHelperReadbackSupport();

  
  
  
  
  
  
  
  
  FormatSupport GetReadbackConfig(SkColorType color_type,
                                  bool can_swizzle,
                                  GLenum* format,
                                  GLenum* type,
                                  size_t* bytes_per_pixel);
  
  
  void GetAdditionalFormat(GLenum format, GLenum type, GLenum *format_out,
                           GLenum *type_out);
 private:
  struct FormatCacheEntry {
    GLenum format;
    GLenum type;
    GLenum read_format;
    GLenum read_type;
  };

  
  
  void InitializeReadbackSupport();

  
  
  
  
  void CheckForReadbackSupport(SkColorType texture_format);

  
  
  
  bool SupportsFormat(GLenum format, GLenum type);

  FormatSupport format_support_table_[kLastEnum_SkColorType + 1];

  gpu::gles2::GLES2Interface* gl_;
  std::vector<struct FormatCacheEntry> format_cache_;
};

}  

#endif  
