// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>

#include "base/basictypes.h"
#include "base/process/process.h"
#include "content/common/content_export.h"
#include "content/common/content_param_traits.h"
#include "content/common/cursors/webcursor.h"
#include "content/common/edit_command.h"
#include "content/common/frame_param_macros.h"
#include "content/public/common/common_param_traits.h"
#include "content/public/common/drop_data.h"
#include "ipc/ipc_channel_handle.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"
#include "third_party/WebKit/public/web/WebCompositionUnderline.h"
#include "third_party/WebKit/public/web/WebDragOperation.h"
#include "third_party/WebKit/public/web/WebDragStatus.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/ipc/gfx_param_traits.h"
#include "ui/gfx/point.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/size.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START BrowserPluginMsgStart


IPC_ENUM_TRAITS_MAX_VALUE(blink::WebDragStatus, blink::WebDragStatusLast)

IPC_STRUCT_BEGIN(BrowserPluginHostMsg_ResizeGuest_Params)
  
  IPC_STRUCT_MEMBER(gfx::Size, view_size)
  
  IPC_STRUCT_MEMBER(float, scale_factor)
  
  
  
  IPC_STRUCT_MEMBER(bool, repaint)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(BrowserPluginHostMsg_Attach_Params)
  IPC_STRUCT_MEMBER(bool, focused)
  IPC_STRUCT_MEMBER(bool, visible)
  IPC_STRUCT_MEMBER(BrowserPluginHostMsg_ResizeGuest_Params,
                    resize_guest_params)
  IPC_STRUCT_MEMBER(gfx::Point, origin)
IPC_STRUCT_END()



IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_ExecuteEditCommand,
                    int ,
                    std::string )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_SetEditCommandsForNextKeyEvent,
                    int ,
                    std::vector<content::EditCommand> )

IPC_MESSAGE_ROUTED5(
    BrowserPluginHostMsg_ImeSetComposition,
    int ,
    std::string ,
    std::vector<blink::WebCompositionUnderline> ,
    int ,
    int )

IPC_MESSAGE_ROUTED3(BrowserPluginHostMsg_ImeConfirmComposition,
                    int ,
                    std::string ,
                    bool )

IPC_MESSAGE_ROUTED3(BrowserPluginHostMsg_ExtendSelectionAndDelete,
                    int ,
                    int ,
                    int )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_Attach,
                    int ,
                    BrowserPluginHostMsg_Attach_Params )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_SetFocus,
                    int ,
                    bool )

IPC_MESSAGE_ROUTED3(BrowserPluginHostMsg_HandleInputEvent,
                    int ,
                    gfx::Rect ,
                    IPC::WebInputEventPointer )

IPC_MESSAGE_ROUTED3(BrowserPluginHostMsg_CopyFromCompositingSurfaceAck,
                    int ,
                    int ,
                    SkBitmap)

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_ReclaimCompositorResources,
                    int ,
                    FrameHostMsg_ReclaimCompositorResources_Params )

IPC_MESSAGE_ROUTED1(BrowserPluginHostMsg_PluginDestroyed,
                    int )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_SetVisibility,
                    int ,
                    bool )

IPC_MESSAGE_ROUTED5(BrowserPluginHostMsg_DragStatusUpdate,
                    int ,
                    blink::WebDragStatus ,
                    content::DropData ,
                    blink::WebDragOperationsMask ,
                    gfx::Point )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_LockMouse_ACK,
                    int ,
                    bool )

IPC_MESSAGE_ROUTED1(BrowserPluginHostMsg_UnlockMouse_ACK,
                    int )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_UpdateGeometry,
                    int ,
                    gfx::Rect )


IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_ResizeGuest,
                    int ,
                    BrowserPluginHostMsg_ResizeGuest_Params)


IPC_MESSAGE_CONTROL1(BrowserPluginMsg_Attach_ACK,
                     int )

IPC_MESSAGE_CONTROL1(BrowserPluginMsg_GuestGone,
                     int )

IPC_MESSAGE_CONTROL2(BrowserPluginMsg_AdvanceFocus,
                     int ,
                     bool )

IPC_MESSAGE_CONTROL2(BrowserPluginMsg_ShouldAcceptTouchEvents,
                     int ,
                     bool )

IPC_MESSAGE_CONTROL2(BrowserPluginMsg_SetContentsOpaque,
                     int ,
                     bool )

IPC_MESSAGE_CONTROL2(BrowserPluginMsg_SetCursor,
                     int ,
                     content::WebCursor )

IPC_MESSAGE_CONTROL4(BrowserPluginMsg_CopyFromCompositingSurface,
                     int ,
                     int ,
                     gfx::Rect  ,
                     gfx::Size  )

IPC_MESSAGE_CONTROL2(BrowserPluginMsg_CompositorFrameSwapped,
                     int ,
                     FrameMsg_CompositorFrameSwapped_Params )

IPC_MESSAGE_CONTROL2(BrowserPluginMsg_SetMouseLock,
                     int ,
                     bool )

IPC_MESSAGE_ROUTED2(BrowserPluginHostMsg_CompositorFrameSwappedACK,
                    int ,
                    FrameHostMsg_CompositorFrameSwappedACK_Params )
