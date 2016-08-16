// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/process/process.h"
#include "components/nacl/common/nacl_types.h"
#include "ipc/ipc_channel_handle.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"

#define IPC_MESSAGE_START NaClMsgStart

IPC_STRUCT_TRAITS_BEGIN(nacl::NaClStartParams)
  IPC_STRUCT_TRAITS_MEMBER(nexe_file)
  IPC_STRUCT_TRAITS_MEMBER(nexe_token_lo)
  IPC_STRUCT_TRAITS_MEMBER(nexe_token_hi)
  IPC_STRUCT_TRAITS_MEMBER(handles)
  IPC_STRUCT_TRAITS_MEMBER(debug_stub_server_bound_socket)
  IPC_STRUCT_TRAITS_MEMBER(validation_cache_enabled)
  IPC_STRUCT_TRAITS_MEMBER(validation_cache_key)
  IPC_STRUCT_TRAITS_MEMBER(version)
  IPC_STRUCT_TRAITS_MEMBER(enable_exception_handling)
  IPC_STRUCT_TRAITS_MEMBER(enable_debug_stub)
  IPC_STRUCT_TRAITS_MEMBER(enable_ipc_proxy)
  IPC_STRUCT_TRAITS_MEMBER(uses_irt)
  IPC_STRUCT_TRAITS_MEMBER(enable_dyncode_syscalls)
  IPC_STRUCT_TRAITS_MEMBER(crash_info_shmem_handle)
IPC_STRUCT_TRAITS_END()

IPC_MESSAGE_CONTROL1(NaClProcessMsg_Start,
                     nacl::NaClStartParams )

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(NaClProcessMsg_LaunchLoaderThroughBroker,
                     std::string )

IPC_MESSAGE_CONTROL2(NaClProcessMsg_LoaderLaunched,
                     std::string,  
                     base::ProcessHandle )

IPC_MESSAGE_CONTROL3(NaClProcessMsg_LaunchDebugExceptionHandler,
                     int32 ,
                     base::ProcessHandle ,
                     std::string )

IPC_MESSAGE_CONTROL2(NaClProcessMsg_DebugExceptionHandlerLaunched,
                     int32 ,
                     bool )

IPC_MESSAGE_CONTROL0(NaClProcessMsg_StopBroker)

IPC_SYNC_MESSAGE_CONTROL1_1(NaClProcessMsg_AttachDebugExceptionHandler,
                            std::string, 
                            bool )

IPC_MESSAGE_CONTROL1(NaClProcessHostMsg_DebugStubPortSelected,
                     uint16_t )
#endif

IPC_SYNC_MESSAGE_CONTROL1_1(NaClProcessMsg_QueryKnownToValidate,
                            std::string, 
                            bool )

IPC_MESSAGE_CONTROL1(NaClProcessMsg_SetKnownToValidate,
                     std::string )

IPC_SYNC_MESSAGE_CONTROL2_2(NaClProcessMsg_ResolveFileToken,
                            uint64, 
                            uint64, 
                            IPC::PlatformFileForTransit, 
                            base::FilePath )

IPC_MESSAGE_CONTROL2(NaClProcessMsg_ResolveFileTokenAsync,
                     uint64, 
                     uint64 )
IPC_MESSAGE_CONTROL4(NaClProcessMsg_ResolveFileTokenAsyncReply,
                     uint64, 
                     uint64, 
                     IPC::PlatformFileForTransit, 
                     base::FilePath )

IPC_MESSAGE_CONTROL4(NaClProcessHostMsg_PpapiChannelsCreated,
                     IPC::ChannelHandle, 
                     IPC::ChannelHandle, 
                     IPC::ChannelHandle, 
                     IPC::ChannelHandle )
