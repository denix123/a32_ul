// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_UTILS_H_
#define GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_UTILS_H_

#include <stdint.h>

#include <limits>
#include <string>
#include <vector>

#include "gpu/command_buffer/common/gles2_utils_export.h"

namespace gpu {
namespace gles2 {


inline bool SafeMultiplyUint32(uint32_t a, uint32_t b, uint32_t* dst) {
  if (b == 0) {
    *dst = 0;
    return true;
  }
  uint32_t v = a * b;
  if (v / b != a) {
    *dst = 0;
    return false;
  }
  *dst = v;
  return true;
}

inline bool SafeAddUint32(uint32_t a, uint32_t b, uint32_t* dst) {
  if (a + b < a) {
    *dst = 0;
    return false;
  }
  *dst = a + b;
  return true;
}

inline bool SafeAddInt32(int32_t a, int32_t b, int32_t* dst) {
  int64_t sum64 = static_cast<int64_t>(a) + b;
  int32_t sum32 = static_cast<int32_t>(sum64);
  bool safe = sum64 == static_cast<int64_t>(sum32);
  *dst = safe ? sum32 : 0;
  return safe;
}

template<typename T>
inline bool FitInt32NonNegative(T value) {
  const int32_t max = std::numeric_limits<int32_t>::max();
  return (std::numeric_limits<T>::max() <= max ||
          value <= static_cast<T>(max));
}

class GLES2_UTILS_EXPORT GLES2Util {
 public:
  static const int kNumFaces = 6;

  
  enum ChannelBits {
    kRed = 0x1,
    kGreen = 0x2,
    kBlue = 0x4,
    kAlpha = 0x8,
    kDepth = 0x10000,
    kStencil = 0x20000,

    kRGB = kRed | kGreen | kBlue,
    kRGBA = kRGB | kAlpha
  };

  struct EnumToString {
    uint32_t value;
    const char* name;
  };

  GLES2Util()
      : num_compressed_texture_formats_(0),
        num_shader_binary_formats_(0) {
  }

  int num_compressed_texture_formats() const {
    return num_compressed_texture_formats_;
  }

  void set_num_compressed_texture_formats(int num_compressed_texture_formats) {
    num_compressed_texture_formats_ = num_compressed_texture_formats;
  }

  int num_shader_binary_formats() const {
    return num_shader_binary_formats_;
  }

  void set_num_shader_binary_formats(int num_shader_binary_formats) {
    num_shader_binary_formats_ = num_shader_binary_formats;
  }

  
  
  int GLGetNumValuesReturned(int id) const;

  
  static uint32_t ComputeImageGroupSize(int format, int type);

  
  static bool ComputeImagePaddedRowSize(
      int width, int format, int type, int unpack_alignment,
      uint32_t* padded_row_size);

  
  
  
  
  static bool ComputeImageDataSizes(
      int width, int height, int format, int type, int unpack_alignment,
      uint32_t* size, uint32_t* unpadded_row_size, uint32_t* padded_row_size);

  static size_t RenderbufferBytesPerPixel(int format);

  static uint32_t GetGLDataTypeSizeForUniforms(int type);

  static size_t GetGLTypeSizeForTexturesAndBuffers(uint32_t type);

  static uint32_t GLErrorToErrorBit(uint32_t gl_error);

  static uint32_t GLErrorBitToGLError(uint32_t error_bit);

  static uint32_t IndexToGLFaceTarget(int index);

  static size_t GLTargetToFaceIndex(uint32_t target);

  static uint32_t GetPreferredGLReadPixelsFormat(uint32_t internal_format);

  static uint32_t GetPreferredGLReadPixelsType(
      uint32_t internal_format, uint32_t texture_type);

  
  
  static uint32_t GetChannelsForFormat(int format);

  
  static uint32_t GetChannelsNeededForAttachmentType(
      int type, uint32_t max_color_attachments);

  
  static bool IsNPOT(uint32_t value) {
    return (value & (value - 1)) != 0;
  }

  
  static bool IsPOT(uint32_t value) {
    return (value & (value - 1)) == 0;
  }

  static std::string GetStringEnum(uint32_t value);
  static std::string GetStringBool(uint32_t value);
  static std::string GetStringError(uint32_t value);

  
  
  
  
  
  
  
  static bool ParseUniformName(
      const std::string& name,
      size_t* array_pos,
      int* element_index,
      bool* getting_array);

  #include "../common/gles2_cmd_utils_autogen.h"

 private:
  static std::string GetQualifiedEnumString(
      const EnumToString* table, size_t count, uint32_t value);

  static const EnumToString* const enum_to_string_table_;
  static const size_t enum_to_string_table_len_;

  int num_compressed_texture_formats_;
  int num_shader_binary_formats_;
};

struct GLES2_UTILS_EXPORT ContextCreationAttribHelper {
  ContextCreationAttribHelper();

  void Serialize(std::vector<int32_t>* attribs) const;
  bool Parse(const std::vector<int32_t>& attribs);

  
  int32_t alpha_size;
  int32_t blue_size;
  int32_t green_size;
  int32_t red_size;
  int32_t depth_size;
  int32_t stencil_size;
  int32_t samples;
  int32_t sample_buffers;
  bool buffer_preserved;
  bool bind_generates_resource;
  bool fail_if_major_perf_caveat;
  bool lose_context_when_out_of_memory;
};

}  
}  

#endif  

