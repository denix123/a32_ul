// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/memory/shared_memory.h"
#include "base/values.h"
#include "content/public/common/common_param_traits.h"
#include "content/public/common/socket_permission_request.h"
#include "extensions/common/api/messaging/message.h"
#include "extensions/common/draggable_region.h"
#include "extensions/common/extension.h"
#include "extensions/common/extensions_client.h"
#include "extensions/common/permissions/media_galleries_permission_data.h"
#include "extensions/common/permissions/permission_set.h"
#include "extensions/common/permissions/socket_permission_data.h"
#include "extensions/common/permissions/usb_device_permission_data.h"
#include "extensions/common/stack_frame.h"
#include "extensions/common/url_pattern.h"
#include "extensions/common/url_pattern_set.h"
#include "extensions/common/user_script.h"
#include "extensions/common/view_type.h"
#include "ipc/ipc_message_macros.h"
#include "ui/gfx/ipc/gfx_param_traits.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START ExtensionMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(extensions::ViewType, extensions::VIEW_TYPE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(content::SocketPermissionRequest::OperationType,
                          content::SocketPermissionRequest::OPERATION_TYPE_LAST)

IPC_ENUM_TRAITS_MAX_VALUE(extensions::UserScript::InjectionType,
                          extensions::UserScript::INJECTION_TYPE_LAST)

IPC_STRUCT_BEGIN(ExtensionHostMsg_APIActionOrEvent_Params)
  
  IPC_STRUCT_MEMBER(std::string, api_call)

  
  IPC_STRUCT_MEMBER(base::ListValue, arguments)

  
  IPC_STRUCT_MEMBER(std::string, extra)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(ExtensionHostMsg_DOMAction_Params)
  
  IPC_STRUCT_MEMBER(GURL, url)

  
  IPC_STRUCT_MEMBER(base::string16, url_title)

  
  IPC_STRUCT_MEMBER(std::string, api_call)

  
  IPC_STRUCT_MEMBER(base::ListValue, arguments)

  
  IPC_STRUCT_MEMBER(int, call_type)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(ExtensionHostMsg_Request_Params)
  
  IPC_STRUCT_MEMBER(std::string, name)

  
  IPC_STRUCT_MEMBER(base::ListValue, arguments)

  
  
  
  IPC_STRUCT_MEMBER(std::string, extension_id)

  
  
  
  
  IPC_STRUCT_MEMBER(GURL, source_url)

  
  IPC_STRUCT_MEMBER(int, source_tab_id)

  
  IPC_STRUCT_MEMBER(int, request_id)

  
  IPC_STRUCT_MEMBER(bool, has_callback)

  
  IPC_STRUCT_MEMBER(bool, user_gesture)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(ExtensionMsg_ExecuteCode_Params)
  
  IPC_STRUCT_MEMBER(int, request_id)

  
  
  IPC_STRUCT_MEMBER(std::string, extension_id)

  
  IPC_STRUCT_MEMBER(bool, is_javascript)

  
  IPC_STRUCT_MEMBER(std::string, code)

  
  IPC_STRUCT_MEMBER(GURL, webview_src)

  
  IPC_STRUCT_MEMBER(bool, all_frames)

  
  IPC_STRUCT_MEMBER(bool, match_about_blank)

  
  IPC_STRUCT_MEMBER(int, run_at)

  
  
  IPC_STRUCT_MEMBER(bool, in_main_world)

  
  IPC_STRUCT_MEMBER(bool, is_web_view)

  
  
  
  IPC_STRUCT_MEMBER(bool, wants_result)

  
  IPC_STRUCT_MEMBER(GURL, file_url)

  
  IPC_STRUCT_MEMBER(bool, user_gesture)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(ExtensionMsg_ExternalConnectionInfo)
  
  IPC_STRUCT_MEMBER(std::string, target_id)

  
  
  IPC_STRUCT_MEMBER(std::string, source_id)

  
  IPC_STRUCT_MEMBER(GURL, source_url)
IPC_STRUCT_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::DraggableRegion)
  IPC_STRUCT_TRAITS_MEMBER(draggable)
  IPC_STRUCT_TRAITS_MEMBER(bounds)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::SocketPermissionRequest)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(host)
  IPC_STRUCT_TRAITS_MEMBER(port)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::SocketPermissionEntry)
  IPC_STRUCT_TRAITS_MEMBER(pattern_)
  IPC_STRUCT_TRAITS_MEMBER(match_subdomains_)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::SocketPermissionData)
  IPC_STRUCT_TRAITS_MEMBER(entry())
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::StackFrame)
  IPC_STRUCT_TRAITS_MEMBER(line_number)
  IPC_STRUCT_TRAITS_MEMBER(column_number)
  IPC_STRUCT_TRAITS_MEMBER(source)
  IPC_STRUCT_TRAITS_MEMBER(function)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::UsbDevicePermissionData)
  IPC_STRUCT_TRAITS_MEMBER(vendor_id())
  IPC_STRUCT_TRAITS_MEMBER(product_id())
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::MediaGalleriesPermissionData)
  IPC_STRUCT_TRAITS_MEMBER(permission())
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(extensions::Message)
  IPC_STRUCT_TRAITS_MEMBER(data)
  IPC_STRUCT_TRAITS_MEMBER(user_gesture)
IPC_STRUCT_TRAITS_END()

#ifndef EXTENSIONS_COMMON_EXTENSION_MESSAGES_H_
#define EXTENSIONS_COMMON_EXTENSION_MESSAGES_H_

typedef std::map<std::string, std::string> SubstitutionMap;

typedef std::map<std::string, std::set<std::string> > ExecutingScriptsMap;

struct ExtensionMsg_PermissionSetStruct {
  ExtensionMsg_PermissionSetStruct();
  explicit ExtensionMsg_PermissionSetStruct(
      const extensions::PermissionSet& permissions);
  ~ExtensionMsg_PermissionSetStruct();

  scoped_refptr<const extensions::PermissionSet> ToPermissionSet() const;

  extensions::APIPermissionSet apis;
  extensions::ManifestPermissionSet manifest_permissions;
  extensions::URLPatternSet explicit_hosts;
  extensions::URLPatternSet scriptable_hosts;
};

struct ExtensionMsg_Loaded_Params {
  ExtensionMsg_Loaded_Params();
  ~ExtensionMsg_Loaded_Params();
  explicit ExtensionMsg_Loaded_Params(const extensions::Extension* extension);

  
  scoped_refptr<extensions::Extension> ConvertToExtension(
      std::string* error) const;

  
  linked_ptr<base::DictionaryValue> manifest;

  
  extensions::Manifest::Location location;

  
  
  base::FilePath path;

  
  ExtensionMsg_PermissionSetStruct active_permissions;
  ExtensionMsg_PermissionSetStruct withheld_permissions;

  
  std::string id;

  
  int creation_flags;
};

namespace IPC {

template <>
struct ParamTraits<URLPattern> {
  typedef URLPattern param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<extensions::URLPatternSet> {
  typedef extensions::URLPatternSet param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<extensions::APIPermission::ID> {
  typedef extensions::APIPermission::ID param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<extensions::APIPermissionSet> {
  typedef extensions::APIPermissionSet param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* r);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<extensions::ManifestPermissionSet> {
  typedef extensions::ManifestPermissionSet param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* r);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<ExtensionMsg_PermissionSetStruct> {
  typedef ExtensionMsg_PermissionSetStruct param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

template <>
struct ParamTraits<ExtensionMsg_Loaded_Params> {
  typedef ExtensionMsg_Loaded_Params param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* p);
  static void Log(const param_type& p, std::string* l);
};

}  

#endif  

IPC_STRUCT_BEGIN(ExtensionMsg_UpdatePermissions_Params)
  IPC_STRUCT_MEMBER(std::string, extension_id)
  IPC_STRUCT_MEMBER(ExtensionMsg_PermissionSetStruct, active_permissions)
  IPC_STRUCT_MEMBER(ExtensionMsg_PermissionSetStruct, withheld_permissions)
IPC_STRUCT_END()


IPC_MESSAGE_ROUTED4(ExtensionMsg_Response,
                    int ,
                    bool ,
                    base::ListValue ,
                    std::string )

IPC_MESSAGE_ROUTED5(ExtensionMsg_MessageInvoke,
                    std::string ,
                    std::string ,
                    std::string ,
                    base::ListValue ,
                    bool )

IPC_MESSAGE_CONTROL1(ExtensionMsg_SetFunctionNames,
                     std::vector<std::string>)

IPC_MESSAGE_ROUTED1(ExtensionMsg_SetFrameName,
                    std::string )

IPC_MESSAGE_CONTROL2(ExtensionMsg_SetSystemFont,
                     std::string ,
                     std::string )

IPC_MESSAGE_CONTROL1(ExtensionMsg_ActivateExtension,
                     std::string )

IPC_MESSAGE_CONTROL1(ExtensionMsg_Loaded,
                     std::vector<ExtensionMsg_Loaded_Params>)

IPC_MESSAGE_CONTROL1(ExtensionMsg_Unloaded,
                     std::string)

IPC_MESSAGE_CONTROL1(ExtensionMsg_SetScriptingWhitelist,
                     
                     extensions::ExtensionsClient::ScriptingWhitelist)

IPC_MESSAGE_ROUTED1(ExtensionMsg_ExecuteCode,
                    ExtensionMsg_ExecuteCode_Params)

IPC_MESSAGE_CONTROL3(ExtensionMsg_UpdateUserScripts,
                     base::SharedMemoryHandle,
                     extensions::ExtensionId ,
                     std::set<std::string> )

IPC_MESSAGE_ROUTED4(ExtensionMsg_ExecuteDeclarativeScript,
                    int ,
                    extensions::ExtensionId ,
                    int ,
                    GURL )

IPC_MESSAGE_ROUTED1(ExtensionMsg_UpdateBrowserWindowId,
                    int )

IPC_MESSAGE_ROUTED1(ExtensionMsg_SetTabId,
                    int )

IPC_MESSAGE_CONTROL1(ExtensionMsg_UpdatePermissions,
                     ExtensionMsg_UpdatePermissions_Params)

IPC_MESSAGE_CONTROL4(ExtensionMsg_UpdateTabSpecificPermissions,
                     GURL ,
                     int ,
                     std::string ,
                     extensions::URLPatternSet )

IPC_MESSAGE_CONTROL2(ExtensionMsg_ClearTabSpecificPermissions,
                     int ,
                     std::vector<std::string> )

IPC_MESSAGE_ROUTED1(ExtensionMsg_NotifyRenderViewType,
                    extensions::ViewType )

IPC_MESSAGE_CONTROL1(ExtensionMsg_UsingWebRequestAPI,
                     bool )

IPC_MESSAGE_CONTROL2(ExtensionMsg_ShouldSuspend,
                     std::string ,
                     uint64 )

IPC_MESSAGE_CONTROL1(ExtensionMsg_Suspend,
                     std::string )

IPC_MESSAGE_CONTROL1(ExtensionMsg_CancelSuspend,
                     std::string )

IPC_MESSAGE_ROUTED2(ExtensionMsg_GetAppInstallStateResponse,
                    std::string ,
                    int32 )

IPC_MESSAGE_ROUTED5(ExtensionMsg_DispatchOnConnect,
                    int ,
                    std::string ,
                    base::DictionaryValue ,
                    ExtensionMsg_ExternalConnectionInfo,
                    std::string )

IPC_MESSAGE_ROUTED2(ExtensionMsg_DeliverMessage,
                    int ,
                    extensions::Message)

IPC_MESSAGE_ROUTED2(ExtensionMsg_DispatchOnDisconnect,
                    int ,
                    std::string )

IPC_MESSAGE_CONTROL1(ExtensionMsg_SetChannel,
                     int )

IPC_MESSAGE_ROUTED2(ExtensionMsg_AddMessageToConsole,
                    content::ConsoleMessageLevel ,
                    std::string )

IPC_MESSAGE_ROUTED0(ExtensionMsg_AppWindowClosed)

IPC_MESSAGE_CONTROL1(ExtensionMsg_WatchPages,
                     std::vector<std::string> )

IPC_MESSAGE_CONTROL1(ExtensionMsg_TransferBlobs,
                     std::vector<std::string> )

IPC_MESSAGE_CONTROL1(ExtensionMsg_CreateMimeHandlerViewGuestACK,
                     int )

IPC_MESSAGE_ROUTED2(ExtensionMsg_GuestAttached,
                    int ,
                    int )


IPC_MESSAGE_ROUTED1(ExtensionHostMsg_Request,
                    ExtensionHostMsg_Request_Params)

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_RequestForIOThread,
                     int ,
                     ExtensionHostMsg_Request_Params)

IPC_MESSAGE_CONTROL3(ExtensionHostMsg_AddListener,
                     std::string ,
                     GURL ,
                     std::string )

IPC_MESSAGE_CONTROL3(ExtensionHostMsg_RemoveListener,
                     std::string ,
                     GURL ,
                     std::string )

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_AddLazyListener,
                     std::string ,
                     std::string )

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_RemoveLazyListener,
                     std::string ,
                     std::string )

IPC_MESSAGE_CONTROL4(ExtensionHostMsg_AddFilteredListener,
                     std::string ,
                     std::string ,
                     base::DictionaryValue ,
                     bool )

IPC_MESSAGE_CONTROL4(ExtensionHostMsg_RemoveFilteredListener,
                     std::string ,
                     std::string ,
                     base::DictionaryValue ,
                     bool )

IPC_MESSAGE_ROUTED0(ExtensionHostMsg_EventAck)

IPC_SYNC_MESSAGE_CONTROL4_1(ExtensionHostMsg_OpenChannelToExtension,
                            int ,
                            ExtensionMsg_ExternalConnectionInfo,
                            std::string ,
                            bool ,
                            int )

IPC_SYNC_MESSAGE_CONTROL3_1(ExtensionHostMsg_OpenChannelToNativeApp,
                            int ,
                            std::string ,
                            std::string ,
                            int )

IPC_SYNC_MESSAGE_CONTROL4_1(ExtensionHostMsg_OpenChannelToTab,
                            int ,
                            int ,
                            std::string ,
                            std::string ,
                            int )

IPC_MESSAGE_ROUTED2(ExtensionHostMsg_PostMessage,
                    int ,
                    extensions::Message)

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_CloseChannel,
                     int ,
                     std::string )

IPC_SYNC_MESSAGE_CONTROL1_1(ExtensionHostMsg_GetMessageBundle,
                            std::string ,
                            SubstitutionMap )

IPC_MESSAGE_ROUTED4(
    ExtensionHostMsg_ExecuteCodeFinished,
    int ,
    std::string ,
    GURL ,
    base::ListValue )

IPC_MESSAGE_ROUTED2(ExtensionHostMsg_ContentScriptsExecuting,
                    ExecutingScriptsMap,
                    GURL )

IPC_MESSAGE_ROUTED3(ExtensionHostMsg_RequestScriptInjectionPermission,
                    std::string ,
                    extensions::UserScript::InjectionType ,
                    int64 )

IPC_MESSAGE_ROUTED1(ExtensionMsg_PermitScriptInjection,
                    int64 )

IPC_MESSAGE_ROUTED3(ExtensionHostMsg_GetAppInstallState,
                    GURL ,
                    int32 ,
                    int32 )

IPC_MESSAGE_ROUTED1(ExtensionHostMsg_ResponseAck,
                    int )

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_ShouldSuspendAck,
                     std::string ,
                     uint64 )

IPC_MESSAGE_CONTROL1(ExtensionHostMsg_SuspendAck,
                     std::string )

IPC_MESSAGE_ROUTED0(ExtensionHostMsg_IncrementLazyKeepaliveCount)

IPC_MESSAGE_ROUTED0(ExtensionHostMsg_DecrementLazyKeepaliveCount)

IPC_SYNC_MESSAGE_CONTROL0_1(ExtensionHostMsg_GenerateUniqueID,
                            int )

IPC_MESSAGE_CONTROL1(ExtensionHostMsg_ResumeRequests, int )

IPC_MESSAGE_ROUTED1(ExtensionHostMsg_UpdateDraggableRegions,
                    std::vector<extensions::DraggableRegion> )

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_AddAPIActionToActivityLog,
                     std::string ,
                     ExtensionHostMsg_APIActionOrEvent_Params)

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_AddEventToActivityLog,
                    std::string ,
                    ExtensionHostMsg_APIActionOrEvent_Params)

IPC_MESSAGE_CONTROL2(ExtensionHostMsg_AddDOMActionToActivityLog,
                     std::string ,
                     ExtensionHostMsg_DOMAction_Params)

IPC_MESSAGE_ROUTED1(ExtensionHostMsg_OnWatchedPageChange,
                    std::vector<std::string> )

IPC_MESSAGE_CONTROL1(ExtensionHostMsg_TransferBlobsAck,
                     std::vector<std::string> )

IPC_MESSAGE_ROUTED2(ExtensionHostMsg_FrameNameChanged,
                    bool ,
                    std::string )

IPC_MESSAGE_ROUTED4(ExtensionHostMsg_DetailedConsoleMessageAdded,
                    base::string16 ,
                    base::string16 ,
                    extensions::StackTrace ,
                    int32 )

IPC_MESSAGE_CONTROL4(ExtensionHostMsg_AttachGuest,
                     int ,
                     int ,
                     int ,
                     base::DictionaryValue )

IPC_MESSAGE_CONTROL4(ExtensionHostMsg_CreateMimeHandlerViewGuest,
                     int ,
                     std::string ,
                     std::string ,
                     int )
