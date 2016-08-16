// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_FORMAT_H_
#define GPU_COMMAND_BUFFER_COMMON_GLES2_CMD_FORMAT_H_


#include <KHR/khrplatform.h>

#include <stdint.h>
#include <string.h>

#include "base/atomicops.h"
#include "base/logging.h"
#include "base/macros.h"
#include "gpu/command_buffer/common/bitfield_helpers.h"
#include "gpu/command_buffer/common/cmd_buffer_common.h"
#include "gpu/command_buffer/common/gles2_cmd_ids.h"

typedef unsigned int GLenum;
typedef unsigned int GLbitfield;
typedef unsigned int GLuint;
typedef int GLint;
typedef int GLsizei;
typedef unsigned char GLboolean;
typedef signed char GLbyte;
typedef short GLshort;
typedef unsigned char GLubyte;
typedef unsigned short GLushort;
typedef unsigned long GLulong;
typedef float GLfloat;
typedef float GLclampf;
typedef double GLdouble;
typedef double GLclampd;
typedef void GLvoid;
typedef khronos_intptr_t GLintptr;
typedef khronos_ssize_t  GLsizeiptr;

namespace gpu {
namespace gles2 {

#pragma pack(push, GPU_COMMAND_BUFFER_ENTRY_ALIGNMENT)

namespace id_namespaces {

enum IdNamespaces {
  kBuffers,
  kFramebuffers,
  kProgramsAndShaders,
  kRenderbuffers,
  kTextures,
  kQueries,
  kVertexArrays,
  kNumIdNamespaces
};

COMPILE_ASSERT(kBuffers == 0, kBuffers_is_not_0);
COMPILE_ASSERT(kFramebuffers == 1, kFramebuffers_is_not_1);
COMPILE_ASSERT(kProgramsAndShaders == 2, kProgramsAndShaders_is_not_2);
COMPILE_ASSERT(kRenderbuffers == 3, kRenderbuffers_is_not_3);
COMPILE_ASSERT(kTextures == 4, kTextures_is_not_4);

}  

template <typename T>
struct SizedResult {
  typedef T Type;

  T* GetData() {
    return static_cast<T*>(static_cast<void*>(&data));
  }

  
  
  static size_t ComputeSize(size_t num_results) {
    return sizeof(T) * num_results + sizeof(uint32_t);  
  }

  
  
  static size_t ComputeSizeFromBytes(size_t size_of_result_in_bytes) {
    return size_of_result_in_bytes + sizeof(uint32_t);  
  }

  
  static uint32_t ComputeMaxResults(size_t size_of_buffer) {
    return (size_of_buffer >= sizeof(uint32_t)) ?
        ((size_of_buffer - sizeof(uint32_t)) / sizeof(T)) : 0;  
  }

  
  void SetNumResults(size_t num_results) {
    size = sizeof(T) * num_results;  
  }

  
  int32_t GetNumResults() const {
    return size / sizeof(T);  
  }

  
  void CopyResult(void* dst) const {
    memcpy(dst, &data, size);
  }

  uint32_t size;  
  int32_t data;  
};

COMPILE_ASSERT(sizeof(SizedResult<int8_t>) == 8, SizedResult_size_not_8);
COMPILE_ASSERT(offsetof(SizedResult<int8_t>, size) == 0,
               OffsetOf_SizedResult_size_not_0);
COMPILE_ASSERT(offsetof(SizedResult<int8_t>, data) == 4,
               OffsetOf_SizedResult_data_not_4);

struct ProgramInput {
  uint32_t type;             
  int32_t size;              
  uint32_t location_offset;  
                             
  uint32_t name_offset;      
  uint32_t name_length;      
};

struct ProgramInfoHeader {
  uint32_t link_status;
  uint32_t num_attribs;
  uint32_t num_uniforms;
  
};

struct QuerySync {
  void Reset() {
    process_count = 0;
    result = 0;
  }

  base::subtle::Atomic32 process_count;
  uint64_t result;
};

struct AsyncUploadSync {
  void Reset() {
    base::subtle::Release_Store(&async_upload_token, 0);
  }

  void SetAsyncUploadToken(uint32_t token) {
    DCHECK_NE(token, 0u);
    base::subtle::Release_Store(&async_upload_token, token);
  }

  bool HasAsyncUploadTokenPassed(uint32_t token) {
    DCHECK_NE(token, 0u);
    uint32_t current_token = base::subtle::Acquire_Load(&async_upload_token);
    return (current_token - token < 0x80000000);
  }

  base::subtle::Atomic32 async_upload_token;
};

COMPILE_ASSERT(sizeof(ProgramInput) == 20, ProgramInput_size_not_20);
COMPILE_ASSERT(offsetof(ProgramInput, type) == 0,
               OffsetOf_ProgramInput_type_not_0);
COMPILE_ASSERT(offsetof(ProgramInput, size) == 4,
               OffsetOf_ProgramInput_size_not_4);
COMPILE_ASSERT(offsetof(ProgramInput, location_offset) == 8,
               OffsetOf_ProgramInput_location_offset_not_8);
COMPILE_ASSERT(offsetof(ProgramInput, name_offset) == 12,
               OffsetOf_ProgramInput_name_offset_not_12);
COMPILE_ASSERT(offsetof(ProgramInput, name_length) == 16,
               OffsetOf_ProgramInput_name_length_not_16);

COMPILE_ASSERT(sizeof(ProgramInfoHeader) == 12, ProgramInfoHeader_size_not_12);
COMPILE_ASSERT(offsetof(ProgramInfoHeader, link_status) == 0,
               OffsetOf_ProgramInfoHeader_link_status_not_0);
COMPILE_ASSERT(offsetof(ProgramInfoHeader, num_attribs) == 4,
               OffsetOf_ProgramInfoHeader_num_attribs_not_4);
COMPILE_ASSERT(offsetof(ProgramInfoHeader, num_uniforms) == 8,
               OffsetOf_ProgramInfoHeader_num_uniforms_not_8);

namespace cmds {

#include "../common/gles2_cmd_format_autogen.h"

// These are hand written commands.

struct GenMailboxCHROMIUM {
  typedef GenMailboxCHROMIUM ValueType;
  static const CommandId kCmdId = kGenMailboxCHROMIUM;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;
  static const uint8 cmd_flags = CMD_FLAG_SET_TRACE_LEVEL(3);
  CommandHeader header;
};

struct InsertSyncPointCHROMIUM {
  typedef InsertSyncPointCHROMIUM ValueType;
  static const CommandId kCmdId = kInsertSyncPointCHROMIUM;
  static const cmd::ArgFlags kArgFlags = cmd::kFixed;
  static const uint8 cmd_flags = CMD_FLAG_SET_TRACE_LEVEL(3);
  CommandHeader header;
};

struct CreateAndConsumeTextureCHROMIUMImmediate {
  typedef CreateAndConsumeTextureCHROMIUMImmediate ValueType;
  static const CommandId kCmdId = kCreateAndConsumeTextureCHROMIUMImmediate;
  static const cmd::ArgFlags kArgFlags = cmd::kAtLeastN;
  static const uint8 cmd_flags = CMD_FLAG_SET_TRACE_LEVEL(1);

  static uint32_t ComputeDataSize() {
    return static_cast<uint32_t>(sizeof(GLbyte) * 64);  
  }

  static uint32_t ComputeSize() {
    return static_cast<uint32_t>(sizeof(ValueType) +
                                 ComputeDataSize());  
  }

  void SetHeader(uint32_t size_in_bytes) {
    header.SetCmdByTotalSize<ValueType>(size_in_bytes);
  }

  void Init(GLenum _target, uint32_t _client_id, const GLbyte* _mailbox) {
    SetHeader(ComputeSize());
    target = _target;
    client_id = _client_id;
    memcpy(ImmediateDataAddress(this), _mailbox, ComputeDataSize());
  }

  void* Set(void* cmd,
            GLenum _target,
            uint32_t _client_id,
            const GLbyte* _mailbox) {
    static_cast<ValueType*>(cmd)->Init(_target, _client_id, _mailbox);
    const uint32_t size = ComputeSize();
    return NextImmediateCmdAddressTotalSize<ValueType>(cmd, size);
  }

  gpu::CommandHeader header;
  uint32_t target;
  uint32_t client_id;
};

COMPILE_ASSERT(sizeof(CreateAndConsumeTextureCHROMIUMImmediate) == 12,
               Sizeof_CreateAndConsumeTextureCHROMIUMImmediate_is_not_12);
COMPILE_ASSERT(offsetof(CreateAndConsumeTextureCHROMIUMImmediate, header) == 0,
               OffsetOf_CreateAndConsumeTextureCHROMIUMImmediate_header_not_0);
COMPILE_ASSERT(offsetof(CreateAndConsumeTextureCHROMIUMImmediate, target) == 4,
               OffsetOf_CreateAndConsumeTextureCHROMIUMImmediate_target_not_4);
COMPILE_ASSERT(
    offsetof(CreateAndConsumeTextureCHROMIUMImmediate, client_id) == 8,
    OffsetOf_CreateAndConsumeTextureCHROMIUMImmediate_client_id_not_8);


#pragma pack(pop)

}  
}  
}  

#endif  
