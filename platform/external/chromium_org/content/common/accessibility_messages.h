// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/basictypes.h"
#include "content/common/content_export.h"
#include "content/common/view_message_enums.h"
#include "content/public/common/common_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"
#include "ipc/ipc_param_traits.h"
#include "ipc/param_traits_macros.h"
#include "third_party/WebKit/public/web/WebAXEnums.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/accessibility/ax_tree_update.h"

#ifndef CONTENT_COMMON_ACCESSIBILITY_MESSAGES_H_
#define CONTENT_COMMON_ACCESSIBILITY_MESSAGES_H_

typedef std::map<int32, int> FrameIDMap;

#endif  

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START AccessibilityMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(ui::AXEvent, ui::AX_EVENT_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(ui::AXRole, ui::AX_ROLE_LAST)

IPC_ENUM_TRAITS_MAX_VALUE(ui::AXBoolAttribute, ui::AX_BOOL_ATTRIBUTE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(ui::AXFloatAttribute, ui::AX_FLOAT_ATTRIBUTE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(ui::AXIntAttribute, ui::AX_INT_ATTRIBUTE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(ui::AXIntListAttribute,
                          ui::AX_INT_LIST_ATTRIBUTE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(ui::AXStringAttribute, ui::AX_STRING_ATTRIBUTE_LAST)

IPC_STRUCT_TRAITS_BEGIN(ui::AXNodeData)
  IPC_STRUCT_TRAITS_MEMBER(id)
  IPC_STRUCT_TRAITS_MEMBER(role)
  IPC_STRUCT_TRAITS_MEMBER(state)
  IPC_STRUCT_TRAITS_MEMBER(location)
  IPC_STRUCT_TRAITS_MEMBER(string_attributes)
  IPC_STRUCT_TRAITS_MEMBER(int_attributes)
  IPC_STRUCT_TRAITS_MEMBER(float_attributes)
  IPC_STRUCT_TRAITS_MEMBER(bool_attributes)
  IPC_STRUCT_TRAITS_MEMBER(intlist_attributes)
  IPC_STRUCT_TRAITS_MEMBER(html_attributes)
  IPC_STRUCT_TRAITS_MEMBER(child_ids)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(ui::AXTreeUpdate)
  IPC_STRUCT_TRAITS_MEMBER(node_id_to_clear)
  IPC_STRUCT_TRAITS_MEMBER(nodes)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_BEGIN(AccessibilityHostMsg_EventParams)
  
  IPC_STRUCT_MEMBER(ui::AXTreeUpdate, update)

  
  
  
  IPC_STRUCT_MEMBER(FrameIDMap, node_to_frame_routing_id_map)

  
  
  IPC_STRUCT_MEMBER(FrameIDMap, node_to_browser_plugin_instance_id_map)

  
  IPC_STRUCT_MEMBER(ui::AXEvent, event_type)

  
  IPC_STRUCT_MEMBER(int, id)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(AccessibilityHostMsg_LocationChangeParams)
  
  IPC_STRUCT_MEMBER(int, id)

  
  
  IPC_STRUCT_MEMBER(gfx::Rect, new_location)
IPC_STRUCT_END()


IPC_MESSAGE_ROUTED1(AccessibilityMsg_SetFocus,
                    int )

IPC_MESSAGE_ROUTED1(AccessibilityMsg_DoDefaultAction,
                    int )

IPC_MESSAGE_ROUTED2(AccessibilityMsg_ScrollToMakeVisible,
                    int ,
                    gfx::Rect )

IPC_MESSAGE_ROUTED2(AccessibilityMsg_ScrollToPoint,
                    int ,
                    gfx::Point )

IPC_MESSAGE_ROUTED3(AccessibilityMsg_SetTextSelection,
                    int ,
                    int ,
                    int )

IPC_MESSAGE_ROUTED1(AccessibilityMsg_HitTest,
                    gfx::Point )

IPC_MESSAGE_ROUTED0(AccessibilityMsg_Events_ACK)

IPC_MESSAGE_ROUTED1(AccessibilityMsg_Reset,
                    int );

IPC_MESSAGE_ROUTED0(AccessibilityMsg_FatalError)


IPC_MESSAGE_ROUTED2(
    AccessibilityHostMsg_Events,
    std::vector<AccessibilityHostMsg_EventParams> ,
    int )

IPC_MESSAGE_ROUTED1(
    AccessibilityHostMsg_LocationChanges,
    std::vector<AccessibilityHostMsg_LocationChangeParams>)
