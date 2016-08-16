// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/memory/shared_memory.h"
#include "content/common/content_export.h"
#include "content/common/gpu/gpu_memory_uma_stats.h"
#include "content/common/gpu/gpu_process_launch_causes.h"
#include "content/common/gpu/gpu_result_codes.h"
#include "content/public/common/common_param_traits.h"
#include "content/public/common/gpu_memory_stats.h"
#include "gpu/command_buffer/common/capabilities.h"
#include "gpu/command_buffer/common/command_buffer.h"
#include "gpu/command_buffer/common/constants.h"
#include "gpu/command_buffer/common/gpu_memory_allocation.h"
#include "gpu/command_buffer/common/mailbox.h"
#include "gpu/config/gpu_info.h"
#include "gpu/ipc/gpu_command_buffer_traits.h"
#include "ipc/ipc_channel_handle.h"
#include "ipc/ipc_message_macros.h"
#include "media/base/video_frame.h"
#include "media/video/video_decode_accelerator.h"
#include "media/video/video_encode_accelerator.h"
#include "ui/events/latency_info.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/size.h"
#include "ui/gl/gpu_preference.h"

#if defined(OS_ANDROID)
#include "content/common/android/surface_texture_peer.h"
#endif

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START GpuMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(content::CauseForGpuLaunch,
                          content::CAUSE_FOR_GPU_LAUNCH_MAX_ENUM - 1)
IPC_ENUM_TRAITS_MAX_VALUE(content::CreateCommandBufferResult,
                          content::CREATE_COMMAND_BUFFER_RESULT_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(gfx::GpuPreference,
                          gfx::GpuPreferenceLast)
IPC_ENUM_TRAITS_MAX_VALUE(gfx::SurfaceType,
                          gfx::SURFACE_TYPE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(gpu::MemoryAllocation::PriorityCutoff,
                          gpu::MemoryAllocation::CUTOFF_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(gpu::error::ContextLostReason,
                          gpu::error::kContextLostReasonLast)
IPC_ENUM_TRAITS_MAX_VALUE(media::VideoEncodeAccelerator::Error,
                          media::VideoEncodeAccelerator::kErrorMax)
IPC_ENUM_TRAITS_MAX_VALUE(media::VideoFrame::Format,
                          media::VideoFrame::FORMAT_MAX)
IPC_ENUM_TRAITS_MIN_MAX_VALUE(media::VideoCodecProfile,
                              media::VIDEO_CODEC_PROFILE_MIN,
                              media::VIDEO_CODEC_PROFILE_MAX)
IPC_ENUM_TRAITS_MIN_MAX_VALUE(gpu::CollectInfoResult,
                              gpu::kCollectInfoNone,
                              gpu::kCollectInfoFatalFailure)

IPC_STRUCT_BEGIN(GPUCreateCommandBufferConfig)
  IPC_STRUCT_MEMBER(int32, share_group_id)
  IPC_STRUCT_MEMBER(std::vector<int>, attribs)
  IPC_STRUCT_MEMBER(GURL, active_url)
  IPC_STRUCT_MEMBER(gfx::GpuPreference, gpu_preference)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(GpuHostMsg_AcceleratedSurfaceBuffersSwapped_Params)
  IPC_STRUCT_MEMBER(int32, surface_id)
  IPC_STRUCT_MEMBER(uint64, surface_handle)
  IPC_STRUCT_MEMBER(int32, route_id)
  IPC_STRUCT_MEMBER(gpu::Mailbox, mailbox)
  IPC_STRUCT_MEMBER(gfx::Size, size)
  IPC_STRUCT_MEMBER(float, scale_factor)
  IPC_STRUCT_MEMBER(std::vector<ui::LatencyInfo>, latency_info)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params)
  IPC_STRUCT_MEMBER(int32, surface_id)
  IPC_STRUCT_MEMBER(uint64, surface_handle)
  IPC_STRUCT_MEMBER(int32, route_id)
  IPC_STRUCT_MEMBER(int, x)
  IPC_STRUCT_MEMBER(int, y)
  IPC_STRUCT_MEMBER(int, width)
  IPC_STRUCT_MEMBER(int, height)
  IPC_STRUCT_MEMBER(gpu::Mailbox, mailbox)
  IPC_STRUCT_MEMBER(gfx::Size, surface_size)
  IPC_STRUCT_MEMBER(float, surface_scale_factor)
  IPC_STRUCT_MEMBER(std::vector<ui::LatencyInfo>, latency_info)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(GpuHostMsg_AcceleratedSurfaceRelease_Params)
  IPC_STRUCT_MEMBER(int32, surface_id)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(AcceleratedSurfaceMsg_BufferPresented_Params)
  IPC_STRUCT_MEMBER(gpu::Mailbox, mailbox)
  IPC_STRUCT_MEMBER(uint32, sync_point)
#if defined(OS_MACOSX)
  IPC_STRUCT_MEMBER(int32, renderer_id)
#endif
#if defined(OS_WIN)
  IPC_STRUCT_MEMBER(base::TimeTicks, vsync_timebase)
  IPC_STRUCT_MEMBER(base::TimeDelta, vsync_interval)
#endif
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(GPUCommandBufferConsoleMessage)
  IPC_STRUCT_MEMBER(int32, id)
  IPC_STRUCT_MEMBER(std::string, message)
IPC_STRUCT_END()

#if defined(OS_ANDROID)
IPC_STRUCT_BEGIN(GpuStreamTextureMsg_MatrixChanged_Params)
  IPC_STRUCT_MEMBER(float, m00)
  IPC_STRUCT_MEMBER(float, m01)
  IPC_STRUCT_MEMBER(float, m02)
  IPC_STRUCT_MEMBER(float, m03)
  IPC_STRUCT_MEMBER(float, m10)
  IPC_STRUCT_MEMBER(float, m11)
  IPC_STRUCT_MEMBER(float, m12)
  IPC_STRUCT_MEMBER(float, m13)
  IPC_STRUCT_MEMBER(float, m20)
  IPC_STRUCT_MEMBER(float, m21)
  IPC_STRUCT_MEMBER(float, m22)
  IPC_STRUCT_MEMBER(float, m23)
  IPC_STRUCT_MEMBER(float, m30)
  IPC_STRUCT_MEMBER(float, m31)
  IPC_STRUCT_MEMBER(float, m32)
  IPC_STRUCT_MEMBER(float, m33)
IPC_STRUCT_END()
#endif

  IPC_STRUCT_TRAITS_BEGIN(gpu::DxDiagNode)
  IPC_STRUCT_TRAITS_MEMBER(values)
  IPC_STRUCT_TRAITS_MEMBER(children)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(gpu::GpuPerformanceStats)
  IPC_STRUCT_TRAITS_MEMBER(graphics)
  IPC_STRUCT_TRAITS_MEMBER(gaming)
  IPC_STRUCT_TRAITS_MEMBER(overall)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(gpu::GPUInfo::GPUDevice)
  IPC_STRUCT_TRAITS_MEMBER(vendor_id)
  IPC_STRUCT_TRAITS_MEMBER(device_id)
  IPC_STRUCT_TRAITS_MEMBER(active)
  IPC_STRUCT_TRAITS_MEMBER(vendor_string)
  IPC_STRUCT_TRAITS_MEMBER(device_string)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(media::VideoEncodeAccelerator::SupportedProfile)
  IPC_STRUCT_TRAITS_MEMBER(profile)
  IPC_STRUCT_TRAITS_MEMBER(max_resolution)
  IPC_STRUCT_TRAITS_MEMBER(max_framerate_numerator)
  IPC_STRUCT_TRAITS_MEMBER(max_framerate_denominator)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(gpu::GPUInfo)
  IPC_STRUCT_TRAITS_MEMBER(initialization_time)
  IPC_STRUCT_TRAITS_MEMBER(optimus)
  IPC_STRUCT_TRAITS_MEMBER(amd_switchable)
  IPC_STRUCT_TRAITS_MEMBER(lenovo_dcute)
  IPC_STRUCT_TRAITS_MEMBER(gpu)
  IPC_STRUCT_TRAITS_MEMBER(secondary_gpus)
  IPC_STRUCT_TRAITS_MEMBER(adapter_luid)
  IPC_STRUCT_TRAITS_MEMBER(driver_vendor)
  IPC_STRUCT_TRAITS_MEMBER(driver_version)
  IPC_STRUCT_TRAITS_MEMBER(driver_date)
  IPC_STRUCT_TRAITS_MEMBER(pixel_shader_version)
  IPC_STRUCT_TRAITS_MEMBER(vertex_shader_version)
  IPC_STRUCT_TRAITS_MEMBER(machine_model_name)
  IPC_STRUCT_TRAITS_MEMBER(machine_model_version)
  IPC_STRUCT_TRAITS_MEMBER(gl_version)
  IPC_STRUCT_TRAITS_MEMBER(gl_vendor)
  IPC_STRUCT_TRAITS_MEMBER(gl_renderer)
  IPC_STRUCT_TRAITS_MEMBER(gl_extensions)
  IPC_STRUCT_TRAITS_MEMBER(gl_ws_vendor)
  IPC_STRUCT_TRAITS_MEMBER(gl_ws_version)
  IPC_STRUCT_TRAITS_MEMBER(gl_ws_extensions)
  IPC_STRUCT_TRAITS_MEMBER(gl_reset_notification_strategy)
  IPC_STRUCT_TRAITS_MEMBER(can_lose_context)
  IPC_STRUCT_TRAITS_MEMBER(performance_stats)
  IPC_STRUCT_TRAITS_MEMBER(software_rendering)
  IPC_STRUCT_TRAITS_MEMBER(direct_rendering)
  IPC_STRUCT_TRAITS_MEMBER(sandboxed)
  IPC_STRUCT_TRAITS_MEMBER(process_crash_count)
  IPC_STRUCT_TRAITS_MEMBER(basic_info_state)
  IPC_STRUCT_TRAITS_MEMBER(context_info_state)
#if defined(OS_WIN)
  IPC_STRUCT_TRAITS_MEMBER(dx_diagnostics_info_state)
  IPC_STRUCT_TRAITS_MEMBER(dx_diagnostics)
#endif
  IPC_STRUCT_TRAITS_MEMBER(video_encode_accelerator_supported_profiles)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(gpu::Capabilities)
  IPC_STRUCT_TRAITS_MEMBER(post_sub_buffer)
  IPC_STRUCT_TRAITS_MEMBER(egl_image_external)
  IPC_STRUCT_TRAITS_MEMBER(texture_format_bgra8888)
  IPC_STRUCT_TRAITS_MEMBER(texture_format_etc1)
  IPC_STRUCT_TRAITS_MEMBER(texture_format_etc1_npot)
  IPC_STRUCT_TRAITS_MEMBER(texture_rectangle)
  IPC_STRUCT_TRAITS_MEMBER(iosurface)
  IPC_STRUCT_TRAITS_MEMBER(texture_usage)
  IPC_STRUCT_TRAITS_MEMBER(texture_storage)
  IPC_STRUCT_TRAITS_MEMBER(discard_framebuffer)
  IPC_STRUCT_TRAITS_MEMBER(sync_query)
  IPC_STRUCT_TRAITS_MEMBER(map_image)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::GPUVideoMemoryUsageStats::ProcessStats)
  IPC_STRUCT_TRAITS_MEMBER(video_memory)
  IPC_STRUCT_TRAITS_MEMBER(has_duplicates)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::GPUVideoMemoryUsageStats)
  IPC_STRUCT_TRAITS_MEMBER(process_map)
  IPC_STRUCT_TRAITS_MEMBER(bytes_allocated)
  IPC_STRUCT_TRAITS_MEMBER(bytes_allocated_historical_max)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::GPUMemoryUmaStats)
  IPC_STRUCT_TRAITS_MEMBER(bytes_allocated_current)
  IPC_STRUCT_TRAITS_MEMBER(bytes_allocated_max)
  IPC_STRUCT_TRAITS_MEMBER(bytes_limit)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(gpu::MemoryAllocation)
  IPC_STRUCT_TRAITS_MEMBER(bytes_limit_when_visible)
  IPC_STRUCT_TRAITS_MEMBER(priority_cutoff_when_visible)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(gfx::GLSurfaceHandle)
  IPC_STRUCT_TRAITS_MEMBER(handle)
  IPC_STRUCT_TRAITS_MEMBER(transport_type)
  IPC_STRUCT_TRAITS_MEMBER(parent_client_id)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_CONTROL0(GpuMsg_Initialize)

IPC_MESSAGE_CONTROL3(GpuMsg_EstablishChannel,
                     int ,
                     bool ,
                     bool )

IPC_MESSAGE_CONTROL1(GpuMsg_CloseChannel,
                     IPC::ChannelHandle )

IPC_MESSAGE_CONTROL5(GpuMsg_CreateViewCommandBuffer,
                     gfx::GLSurfaceHandle, 
                     int32, 
                     int32, 
                     GPUCreateCommandBufferConfig, 
                     int32 )

IPC_MESSAGE_CONTROL4(GpuMsg_CreateGpuMemoryBuffer,
                     gfx::GpuMemoryBufferHandle, 
                     gfx::Size, 
                     unsigned, 
                     unsigned )

IPC_MESSAGE_CONTROL2(GpuMsg_DestroyGpuMemoryBuffer,
                     gfx::GpuMemoryBufferHandle, 
                     int32 )

IPC_MESSAGE_CONTROL0(GpuMsg_CollectGraphicsInfo)

IPC_MESSAGE_CONTROL0(GpuMsg_GetVideoMemoryUsageStats)

IPC_MESSAGE_ROUTED1(AcceleratedSurfaceMsg_BufferPresented,
                    AcceleratedSurfaceMsg_BufferPresented_Params)

IPC_MESSAGE_ROUTED0(AcceleratedSurfaceMsg_WakeUpGpu)

IPC_MESSAGE_CONTROL0(GpuMsg_Clean)

IPC_MESSAGE_CONTROL0(GpuMsg_Crash)

IPC_MESSAGE_CONTROL0(GpuMsg_Hang)

IPC_MESSAGE_CONTROL0(GpuMsg_DisableWatchdog)


IPC_SYNC_MESSAGE_CONTROL1_3(GpuHostMsg_EstablishGpuChannel,
                            content::CauseForGpuLaunch,
                            int ,
                            IPC::ChannelHandle ,
                            gpu::GPUInfo )

IPC_SYNC_MESSAGE_CONTROL3_1(GpuHostMsg_CreateViewCommandBuffer,
                            int32, 
                            GPUCreateCommandBufferConfig, 
                            int32, 
                            content::CreateCommandBufferResult )

IPC_MESSAGE_CONTROL2(GpuHostMsg_Initialized,
                     bool ,
                     ::gpu::GPUInfo )

IPC_MESSAGE_CONTROL1(GpuHostMsg_ChannelEstablished,
                     IPC::ChannelHandle )

IPC_MESSAGE_CONTROL1(GpuHostMsg_DestroyChannel,
                     int32 )

IPC_MESSAGE_CONTROL3(GpuHostMsg_CacheShader,
                     int32 ,
                     std::string ,
                     std::string )

IPC_MESSAGE_CONTROL1(GpuMsg_LoadedShader,
                     std::string )

IPC_MESSAGE_CONTROL1(GpuHostMsg_CommandBufferCreated,
                     content::CreateCommandBufferResult )

IPC_MESSAGE_CONTROL1(GpuHostMsg_DestroyCommandBuffer,
                     int32 )

IPC_MESSAGE_CONTROL1(GpuHostMsg_GpuMemoryBufferCreated,
                     gfx::GpuMemoryBufferHandle )

IPC_MESSAGE_CONTROL1(GpuHostMsg_GraphicsInfoCollected,
                     gpu::GPUInfo )

IPC_MESSAGE_CONTROL1(GpuHostMsg_VideoMemoryUsageStats,
                     content::GPUVideoMemoryUsageStats )

IPC_MESSAGE_CONTROL3(GpuHostMsg_OnLogMessage,
                     int ,
                     std::string ,
                     std::string )

IPC_MESSAGE_CONTROL2(GpuHostMsg_AcceleratedSurfaceInitialized,
                     int32 ,
                     int32 )

IPC_MESSAGE_CONTROL1(GpuHostMsg_FrameDrawn,
                     std::vector<ui::LatencyInfo> )

IPC_MESSAGE_CONTROL1(GpuHostMsg_AcceleratedSurfaceBuffersSwapped,
                     GpuHostMsg_AcceleratedSurfaceBuffersSwapped_Params)

IPC_MESSAGE_CONTROL1(GpuHostMsg_AcceleratedSurfacePostSubBuffer,
                     GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params)

IPC_MESSAGE_CONTROL1(GpuHostMsg_AcceleratedSurfaceRelease,
                     GpuHostMsg_AcceleratedSurfaceRelease_Params)

IPC_MESSAGE_CONTROL1(GpuHostMsg_AcceleratedSurfaceSuspend,
                     int32 )

IPC_MESSAGE_CONTROL3(GpuHostMsg_UpdateVSyncParameters,
                     int32 ,
                     base::TimeTicks ,
                     base::TimeDelta )

IPC_MESSAGE_CONTROL1(GpuHostMsg_DidCreateOffscreenContext,
                     GURL )

IPC_MESSAGE_CONTROL3(GpuHostMsg_DidLoseContext,
                     bool ,
                     gpu::error::ContextLostReason ,
                     GURL )

IPC_MESSAGE_CONTROL1(GpuHostMsg_DidDestroyOffscreenContext,
                     GURL )

IPC_MESSAGE_CONTROL1(GpuHostMsg_GpuMemoryUmaStats,
                     content::GPUMemoryUmaStats )


IPC_SYNC_MESSAGE_CONTROL3_1(GpuChannelMsg_CreateOffscreenCommandBuffer,
                            gfx::Size, 
                            GPUCreateCommandBufferConfig, 
                            int32, 
                            bool )

IPC_SYNC_MESSAGE_CONTROL1_0(GpuChannelMsg_DestroyCommandBuffer,
                            int32 )

IPC_SYNC_MESSAGE_CONTROL1_1(GpuChannelMsg_DevToolsStartEventsRecording,
                            int32, 
                            bool )

IPC_MESSAGE_CONTROL0(GpuChannelMsg_DevToolsStopEventsRecording)

#if defined(OS_ANDROID)
IPC_MESSAGE_ROUTED2(GpuStreamTextureMsg_EstablishPeer,
                    int32, 
                    int32  )

IPC_MESSAGE_ROUTED1(GpuStreamTextureMsg_SetSize,
                    gfx::Size )

IPC_MESSAGE_ROUTED0(GpuStreamTextureMsg_StartListening)

IPC_MESSAGE_ROUTED0(GpuStreamTextureMsg_FrameAvailable)

IPC_MESSAGE_ROUTED1(GpuStreamTextureMsg_MatrixChanged,
                    GpuStreamTextureMsg_MatrixChanged_Params )
#endif

IPC_SYNC_MESSAGE_ROUTED1_2(GpuCommandBufferMsg_Initialize,
                           base::SharedMemoryHandle ,
                           bool ,
                           gpu::Capabilities )

IPC_SYNC_MESSAGE_ROUTED1_0(GpuCommandBufferMsg_SetGetBuffer,
                           int32 )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_ProduceFrontBuffer,
                    gpu::Mailbox )

IPC_SYNC_MESSAGE_ROUTED2_1(GpuCommandBufferMsg_WaitForTokenInRange,
                           int32 ,
                           int32 ,
                           gpu::CommandBuffer::State )

IPC_SYNC_MESSAGE_ROUTED2_1(GpuCommandBufferMsg_WaitForGetOffsetInRange,
                           int32 ,
                           int32 ,
                           gpu::CommandBuffer::State )

IPC_MESSAGE_ROUTED3(GpuCommandBufferMsg_AsyncFlush,
                    int32 ,
                    uint32 ,
                    std::vector<ui::LatencyInfo> )

IPC_MESSAGE_ROUTED0(GpuCommandBufferMsg_Rescheduled)

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_ConsoleMsg,
                    GPUCommandBufferConsoleMessage )

IPC_MESSAGE_ROUTED3(GpuCommandBufferMsg_RegisterTransferBuffer,
                    int32 ,
                    base::SharedMemoryHandle ,
                    uint32 )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_DestroyTransferBuffer,
                    int32 )

IPC_SYNC_MESSAGE_ROUTED2_1(GpuCommandBufferMsg_CreateVideoDecoder,
                           media::VideoCodecProfile ,
                           int32, 
                           bool )

IPC_SYNC_MESSAGE_ROUTED5_1(GpuCommandBufferMsg_CreateVideoEncoder,
                           media::VideoFrame::Format ,
                           gfx::Size ,
                           media::VideoCodecProfile ,
                           uint32 ,
                           int32, 
                           bool )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_Destroyed,
                    gpu::error::ContextLostReason )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_Echo,
                    IPC::Message )

IPC_MESSAGE_ROUTED0(GpuCommandBufferMsg_EchoAck)

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_SetSurfaceVisible, bool )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_SetMemoryAllocation,
                    gpu::MemoryAllocation )

IPC_MESSAGE_ROUTED1(
    GpuCommandBufferMsg_SetClientHasMemoryAllocationChangedCallback,
    bool )

IPC_SYNC_MESSAGE_ROUTED1_1(GpuCommandBufferMsg_InsertSyncPoint,
                           bool ,
                           uint32 )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_RetireSyncPoint,
                    uint32 )

IPC_MESSAGE_ROUTED2(GpuCommandBufferMsg_SignalSyncPoint,
                    uint32 ,
                    uint32 )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_SignalSyncPointAck,
                    uint32 )

IPC_MESSAGE_ROUTED2(GpuCommandBufferMsg_SignalQuery,
                    uint32 ,
                    uint32 )

IPC_MESSAGE_ROUTED5(GpuCommandBufferMsg_RegisterGpuMemoryBuffer,
                    int32 ,
                    gfx::GpuMemoryBufferHandle ,
                    uint32 ,
                    uint32 ,
                    uint32 )

IPC_MESSAGE_ROUTED1(GpuCommandBufferMsg_UnregisterGpuMemoryBuffer,
                    int32 )

IPC_SYNC_MESSAGE_ROUTED2_1(GpuCommandBufferMsg_CreateStreamTexture,
                           uint32, 
                           int32, 
                           bool )


IPC_MESSAGE_ROUTED3(AcceleratedVideoDecoderMsg_Decode,
                    base::SharedMemoryHandle, 
                    int32, 
                    uint32) 

IPC_MESSAGE_ROUTED2(AcceleratedVideoDecoderMsg_AssignPictureBuffers,
                    std::vector<int32>,  
                    std::vector<uint32>) 

IPC_MESSAGE_ROUTED1(AcceleratedVideoDecoderMsg_ReusePictureBuffer,
                    int32) 

IPC_MESSAGE_ROUTED0(AcceleratedVideoDecoderMsg_Flush)

IPC_MESSAGE_ROUTED0(AcceleratedVideoDecoderMsg_Reset)

IPC_MESSAGE_ROUTED0(AcceleratedVideoDecoderMsg_Destroy)


IPC_MESSAGE_ROUTED1(AcceleratedVideoDecoderHostMsg_BitstreamBufferProcessed,
                    int32) 

IPC_MESSAGE_ROUTED3(
    AcceleratedVideoDecoderHostMsg_ProvidePictureBuffers,
    int32, 
    gfx::Size, 
    uint32 ) 

IPC_MESSAGE_ROUTED1(AcceleratedVideoDecoderHostMsg_DismissPictureBuffer,
                    int32) 

IPC_MESSAGE_ROUTED3(AcceleratedVideoDecoderHostMsg_PictureReady,
                    int32,     
                    int32,     
                    gfx::Rect) 

IPC_MESSAGE_ROUTED0(AcceleratedVideoDecoderHostMsg_FlushDone)

IPC_MESSAGE_ROUTED0(AcceleratedVideoDecoderHostMsg_ResetDone)

IPC_MESSAGE_ROUTED1(AcceleratedVideoDecoderHostMsg_ErrorNotification,
                    uint32) 


IPC_MESSAGE_ROUTED4(AcceleratedVideoEncoderMsg_Encode,
                    int32 ,
                    base::SharedMemoryHandle ,
                    uint32 ,
                    bool )

IPC_MESSAGE_ROUTED3(AcceleratedVideoEncoderMsg_UseOutputBitstreamBuffer,
                    int32 ,
                    base::SharedMemoryHandle ,
                    uint32 )

IPC_MESSAGE_ROUTED2(AcceleratedVideoEncoderMsg_RequestEncodingParametersChange,
                    uint32 ,
                    uint32 )


IPC_MESSAGE_ROUTED3(AcceleratedVideoEncoderHostMsg_RequireBitstreamBuffers,
                    uint32 ,
                    gfx::Size ,
                    uint32 )

IPC_MESSAGE_ROUTED1(AcceleratedVideoEncoderHostMsg_NotifyInputDone,
                    int32 )

IPC_MESSAGE_ROUTED3(AcceleratedVideoEncoderHostMsg_BitstreamBufferReady,
                    int32 ,
                    uint32 ,
                    bool )

IPC_MESSAGE_ROUTED1(AcceleratedVideoEncoderHostMsg_NotifyError,
                    media::VideoEncodeAccelerator::Error )

IPC_MESSAGE_ROUTED0(AcceleratedVideoEncoderMsg_Destroy)
