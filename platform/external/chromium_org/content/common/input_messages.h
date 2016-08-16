// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "content/common/content_param_traits.h"
#include "content/common/edit_command.h"
#include "content/common/input/did_overscroll_params.h"
#include "content/common/input/input_event.h"
#include "content/common/input/input_event_ack_state.h"
#include "content/common/input/input_param_traits.h"
#include "content/common/input/synthetic_gesture_packet.h"
#include "content/common/input/synthetic_gesture_params.h"
#include "content/common/input/synthetic_pinch_gesture_params.h"
#include "content/common/input/synthetic_smooth_scroll_gesture_params.h"
#include "content/common/input/synthetic_tap_gesture_params.h"
#include "content/common/input/touch_action.h"
#include "content/public/common/common_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/events/ipc/latency_info_param_traits.h"
#include "ui/gfx/ipc/gfx_param_traits.h"
#include "ui/gfx/point.h"
#include "ui/gfx/range/range.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/vector2d_f.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#ifdef IPC_MESSAGE_START
#error IPC_MESSAGE_START
#endif

#define IPC_MESSAGE_START InputMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(content::InputEventAckState,
                          content::INPUT_EVENT_ACK_STATE_MAX)
IPC_ENUM_TRAITS_MAX_VALUE(
    content::SyntheticGestureParams::GestureSourceType,
    content::SyntheticGestureParams::GESTURE_SOURCE_TYPE_MAX)
IPC_ENUM_TRAITS_MAX_VALUE(
    content::SyntheticGestureParams::GestureType,
    content::SyntheticGestureParams::SYNTHETIC_GESTURE_TYPE_MAX)
IPC_ENUM_TRAITS_VALIDATE(content::TouchAction, (
    value >= 0 &&
    value <= content::TOUCH_ACTION_MAX &&
    (!(value & content::TOUCH_ACTION_NONE) ||
        (value == content::TOUCH_ACTION_NONE)) &&
    (!(value & content::TOUCH_ACTION_PINCH_ZOOM) ||
        (value == content::TOUCH_ACTION_MANIPULATION))))

IPC_STRUCT_TRAITS_BEGIN(content::DidOverscrollParams)
  IPC_STRUCT_TRAITS_MEMBER(accumulated_overscroll)
  IPC_STRUCT_TRAITS_MEMBER(latest_overscroll_delta)
  IPC_STRUCT_TRAITS_MEMBER(current_fling_velocity)
  IPC_STRUCT_TRAITS_MEMBER(causal_event_viewport_point)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::EditCommand)
  IPC_STRUCT_TRAITS_MEMBER(name)
  IPC_STRUCT_TRAITS_MEMBER(value)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::InputEvent)
  IPC_STRUCT_TRAITS_MEMBER(web_event)
  IPC_STRUCT_TRAITS_MEMBER(latency_info)
  IPC_STRUCT_TRAITS_MEMBER(is_keyboard_shortcut)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::SyntheticGestureParams)
  IPC_STRUCT_TRAITS_MEMBER(gesture_source_type)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::SyntheticSmoothScrollGestureParams)
  IPC_STRUCT_TRAITS_PARENT(content::SyntheticGestureParams)
  IPC_STRUCT_TRAITS_MEMBER(anchor)
  IPC_STRUCT_TRAITS_MEMBER(distances)
  IPC_STRUCT_TRAITS_MEMBER(prevent_fling)
  IPC_STRUCT_TRAITS_MEMBER(speed_in_pixels_s)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::SyntheticPinchGestureParams)
  IPC_STRUCT_TRAITS_PARENT(content::SyntheticGestureParams)
  IPC_STRUCT_TRAITS_MEMBER(scale_factor)
  IPC_STRUCT_TRAITS_MEMBER(anchor)
  IPC_STRUCT_TRAITS_MEMBER(relative_pointer_speed_in_pixels_s)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::SyntheticTapGestureParams)
  IPC_STRUCT_TRAITS_PARENT(content::SyntheticGestureParams)
  IPC_STRUCT_TRAITS_MEMBER(position)
  IPC_STRUCT_TRAITS_MEMBER(duration_ms)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_BEGIN(InputHostMsg_HandleInputEvent_ACK_Params)
  IPC_STRUCT_MEMBER(blink::WebInputEvent::Type, type)
  IPC_STRUCT_MEMBER(content::InputEventAckState, state)
  IPC_STRUCT_MEMBER(ui::LatencyInfo, latency)
  
  IPC_STRUCT_MEMBER(scoped_ptr<content::DidOverscrollParams>, overscroll)
IPC_STRUCT_END()

IPC_MESSAGE_ROUTED3(InputMsg_HandleInputEvent,
                    IPC::WebInputEventPointer ,
                    ui::LatencyInfo ,
                    bool )

IPC_MESSAGE_ROUTED1(InputMsg_CursorVisibilityChange,
                    bool )

IPC_MESSAGE_ROUTED3(InputMsg_SetCompositionFromExistingText,
    int ,
    int ,
    std::vector<blink::WebCompositionUnderline> )

IPC_MESSAGE_ROUTED2(InputMsg_ExtendSelectionAndDelete,
                    int ,
                    int )

IPC_MESSAGE_ROUTED4(
    InputMsg_ImeSetComposition,
    base::string16, 
    std::vector<blink::WebCompositionUnderline>, 
    int, 
    int )

IPC_MESSAGE_ROUTED3(InputMsg_ImeConfirmComposition,
                    base::string16 ,
                    gfx::Range ,
                    bool )

IPC_MESSAGE_ROUTED1(InputMsg_SetEditCommandsForNextKeyEvent,
                    std::vector<content::EditCommand> )

IPC_MESSAGE_ROUTED2(InputMsg_ExecuteEditCommand,
                    std::string, 
                    std::string )

IPC_MESSAGE_ROUTED0(InputMsg_MouseCaptureLost)

IPC_MESSAGE_ROUTED1(InputMsg_SetFocus,
                    bool )

IPC_MESSAGE_ROUTED1(InputMsg_ScrollFocusedEditableNodeIntoRect, gfx::Rect)

IPC_MESSAGE_ROUTED0(InputMsg_Undo)
IPC_MESSAGE_ROUTED0(InputMsg_Redo)
IPC_MESSAGE_ROUTED0(InputMsg_Cut)
IPC_MESSAGE_ROUTED0(InputMsg_Copy)
#if defined(OS_MACOSX)
IPC_MESSAGE_ROUTED0(InputMsg_CopyToFindPboard)
#endif
IPC_MESSAGE_ROUTED0(InputMsg_Paste)
IPC_MESSAGE_ROUTED0(InputMsg_PasteAndMatchStyle)
IPC_MESSAGE_ROUTED1(InputMsg_Replace,
                    base::string16)
IPC_MESSAGE_ROUTED1(InputMsg_ReplaceMisspelling,
                    base::string16)
IPC_MESSAGE_ROUTED0(InputMsg_Delete)
IPC_MESSAGE_ROUTED0(InputMsg_SelectAll)

IPC_MESSAGE_ROUTED0(InputMsg_Unselect)

IPC_MESSAGE_ROUTED2(InputMsg_SelectRange,
                    gfx::Point ,
                    gfx::Point )

IPC_MESSAGE_ROUTED1(InputMsg_MoveCaret,
                    gfx::Point )

#if defined(OS_ANDROID)
IPC_MESSAGE_ROUTED3(InputMsg_ActivateNearestFindResult,
                    int ,
                    float ,
                    float )
#endif

IPC_MESSAGE_ROUTED0(InputMsg_SyntheticGestureCompleted)


IPC_MESSAGE_ROUTED1(InputHostMsg_HandleInputEvent_ACK,
                    InputHostMsg_HandleInputEvent_ACK_Params)

IPC_MESSAGE_ROUTED1(InputHostMsg_QueueSyntheticGesture,
                    content::SyntheticGesturePacket)

IPC_MESSAGE_ROUTED1(InputHostMsg_SetTouchAction,
                    content::TouchAction )

IPC_MESSAGE_ROUTED1(InputHostMsg_DidOverscroll,
                    content::DidOverscrollParams )

IPC_MESSAGE_ROUTED0(InputHostMsg_ImeCancelComposition)

#if defined(OS_MACOSX) || defined(USE_AURA)
IPC_MESSAGE_ROUTED2(InputHostMsg_ImeCompositionRangeChanged,
                    gfx::Range ,
                    std::vector<gfx::Rect> )
#endif

