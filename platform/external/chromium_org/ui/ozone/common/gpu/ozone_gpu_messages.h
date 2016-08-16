// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <vector>

#include "ipc/ipc_message_macros.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/ipc/gfx_param_traits.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/ozone/common/gpu/ozone_gpu_message_params.h"
#include "ui/ozone/ozone_export.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT OZONE_EXPORT

#define IPC_MESSAGE_START OzoneGpuMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(ui::DisplayConnectionType,
                          ui::DISPLAY_CONNECTION_TYPE_LAST)

IPC_STRUCT_TRAITS_BEGIN(ui::DisplayMode_Params)
  IPC_STRUCT_TRAITS_MEMBER(size)
  IPC_STRUCT_TRAITS_MEMBER(is_interlaced)
  IPC_STRUCT_TRAITS_MEMBER(refresh_rate)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(ui::DisplaySnapshot_Params)
  IPC_STRUCT_TRAITS_MEMBER(display_id)
  IPC_STRUCT_TRAITS_MEMBER(has_proper_display_id)
  IPC_STRUCT_TRAITS_MEMBER(origin)
  IPC_STRUCT_TRAITS_MEMBER(physical_size)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(is_aspect_preserving_scaling)
  IPC_STRUCT_TRAITS_MEMBER(has_overscan)
  IPC_STRUCT_TRAITS_MEMBER(display_name)
  IPC_STRUCT_TRAITS_MEMBER(modes)
  IPC_STRUCT_TRAITS_MEMBER(has_current_mode)
  IPC_STRUCT_TRAITS_MEMBER(current_mode)
  IPC_STRUCT_TRAITS_MEMBER(has_native_mode)
  IPC_STRUCT_TRAITS_MEMBER(native_mode)
  IPC_STRUCT_TRAITS_MEMBER(string_representation)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_CONTROL4(OzoneGpuMsg_CursorSet,
                     gfx::AcceleratedWidget,
                     std::vector<SkBitmap>,
                     gfx::Point ,
                     int )

IPC_MESSAGE_CONTROL2(OzoneGpuMsg_CursorMove,
                     gfx::AcceleratedWidget, gfx::Point)

IPC_MESSAGE_CONTROL1(OzoneGpuMsg_CreateWindowDelegate,
                     gfx::AcceleratedWidget )

IPC_MESSAGE_CONTROL1(OzoneGpuMsg_DestroyWindowDelegate,
                     gfx::AcceleratedWidget )

IPC_MESSAGE_CONTROL2(OzoneGpuMsg_WindowBoundsChanged,
                     gfx::AcceleratedWidget ,
                     gfx::Rect )

#if defined(OS_CHROMEOS)
IPC_MESSAGE_CONTROL0(OzoneGpuMsg_ForceDPMSOn)

IPC_MESSAGE_CONTROL1(OzoneGpuMsg_RefreshNativeDisplays,
                     std::vector<ui::DisplaySnapshot_Params> )

IPC_MESSAGE_CONTROL3(OzoneGpuMsg_ConfigureNativeDisplay,
                     int64_t,  
                     ui::DisplayMode_Params,  
                     gfx::Point)  

IPC_MESSAGE_CONTROL1(OzoneGpuMsg_DisableNativeDisplay,
                     int64_t)  


IPC_MESSAGE_CONTROL1(OzoneHostMsg_UpdateNativeDisplays,
                     std::vector<ui::DisplaySnapshot_Params>)
#endif
