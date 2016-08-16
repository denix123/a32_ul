// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_COMMON_NACL_TYPES_H_
#define COMPONENTS_NACL_COMMON_NACL_TYPES_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/shared_memory.h"
#include "base/process/process_handle.h"
#include "build/build_config.h"
#include "ipc/ipc_channel.h"
#include "ipc/ipc_platform_file.h"

#if defined(OS_POSIX)
#include "base/file_descriptor_posix.h"
#endif

#if defined(OS_WIN)
#include <windows.h>   
#endif

namespace nacl {

#if defined(OS_WIN)
typedef HANDLE FileDescriptor;
inline HANDLE ToNativeHandle(const FileDescriptor& desc) {
  return desc;
}
#elif defined(OS_POSIX)
typedef base::FileDescriptor FileDescriptor;
inline int ToNativeHandle(const FileDescriptor& desc) {
  return desc.fd;
}
#endif

static const int kNaClCrashInfoShmemSize = 4096;
static const int kNaClCrashInfoMaxLogSize = 1024;

struct NaClStartParams {
  NaClStartParams();
  ~NaClStartParams();

  IPC::PlatformFileForTransit nexe_file;
  uint64_t nexe_token_lo;
  uint64_t nexe_token_hi;

  std::vector<FileDescriptor> handles;
  FileDescriptor debug_stub_server_bound_socket;

  bool validation_cache_enabled;
  std::string validation_cache_key;
  
  
  
  std::string version;

  bool enable_exception_handling;
  bool enable_debug_stub;
  bool enable_ipc_proxy;
  bool uses_irt;
  bool enable_dyncode_syscalls;

  
  base::SharedMemoryHandle crash_info_shmem_handle;

  
  
  
};

struct NaClLaunchParams {
  NaClLaunchParams();
  NaClLaunchParams(const std::string& manifest_url,
                   const IPC::PlatformFileForTransit& nexe_file,
                   uint64_t nexe_token_lo,
                   uint64_t nexe_token_hi,
                   int render_view_id,
                   uint32 permission_bits,
                   bool uses_irt,
                   bool uses_nonsfi_mode,
                   bool enable_dyncode_syscalls,
                   bool enable_exception_handling,
                   bool enable_crash_throttling);
  ~NaClLaunchParams();

  std::string manifest_url;
  
  
  
  IPC::PlatformFileForTransit nexe_file;
  uint64_t nexe_token_lo;
  uint64_t nexe_token_hi;

  int render_view_id;
  uint32 permission_bits;
  bool uses_irt;
  bool uses_nonsfi_mode;
  bool enable_dyncode_syscalls;
  bool enable_exception_handling;
  bool enable_crash_throttling;
};

struct NaClLaunchResult {
  NaClLaunchResult();
  NaClLaunchResult(
      FileDescriptor imc_channel_handle,
      const IPC::ChannelHandle& ppapi_ipc_channel_handle,
      const IPC::ChannelHandle& trusted_ipc_channel_handle,
      const IPC::ChannelHandle& manifest_service_ipc_channel_handle,
      base::ProcessId plugin_pid,
      int plugin_child_id,
      base::SharedMemoryHandle crash_info_shmem_handle);
  ~NaClLaunchResult();

  
  FileDescriptor imc_channel_handle;

  
  IPC::ChannelHandle ppapi_ipc_channel_handle;

  
  
  IPC::ChannelHandle trusted_ipc_channel_handle;

  
  IPC::ChannelHandle manifest_service_ipc_channel_handle;

  base::ProcessId plugin_pid;
  int plugin_child_id;

  
  base::SharedMemoryHandle crash_info_shmem_handle;
};

}  

#endif  
