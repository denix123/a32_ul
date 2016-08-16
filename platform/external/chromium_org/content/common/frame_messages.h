// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "content/common/content_export.h"
#include "content/common/content_param_traits.h"
#include "content/common/frame_message_enums.h"
#include "content/common/frame_param.h"
#include "content/common/navigation_gesture.h"
#include "content/common/resource_request_body.h"
#include "content/public/common/color_suggestion.h"
#include "content/public/common/common_param_traits.h"
#include "content/public/common/context_menu_params.h"
#include "content/public/common/frame_navigate_params.h"
#include "content/public/common/javascript_message_type.h"
#include "content/public/common/page_state.h"
#include "ipc/ipc_message_macros.h"
#include "ui/gfx/ipc/gfx_param_traits.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START FrameMsgStart

IPC_ENUM_TRAITS_MIN_MAX_VALUE(AccessibilityMode,
                              AccessibilityModeOff,
                              AccessibilityModeComplete)
IPC_ENUM_TRAITS_MIN_MAX_VALUE(content::JavaScriptMessageType,
                              content::JAVASCRIPT_MESSAGE_TYPE_ALERT,
                              content::JAVASCRIPT_MESSAGE_TYPE_PROMPT)
IPC_ENUM_TRAITS_MAX_VALUE(FrameMsg_Navigate_Type::Value,
                          FrameMsg_Navigate_Type::NAVIGATE_TYPE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(blink::WebContextMenuData::MediaType,
                          blink::WebContextMenuData::MediaTypeLast)
IPC_ENUM_TRAITS_MAX_VALUE(ui::MenuSourceType, ui::MENU_SOURCE_TYPE_LAST)

IPC_STRUCT_TRAITS_BEGIN(content::ColorSuggestion)
  IPC_STRUCT_TRAITS_MEMBER(color)
  IPC_STRUCT_TRAITS_MEMBER(label)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::ContextMenuParams)
  IPC_STRUCT_TRAITS_MEMBER(media_type)
  IPC_STRUCT_TRAITS_MEMBER(x)
  IPC_STRUCT_TRAITS_MEMBER(y)
  IPC_STRUCT_TRAITS_MEMBER(link_url)
  IPC_STRUCT_TRAITS_MEMBER(link_text)
  IPC_STRUCT_TRAITS_MEMBER(unfiltered_link_url)
  IPC_STRUCT_TRAITS_MEMBER(src_url)
  IPC_STRUCT_TRAITS_MEMBER(has_image_contents)
  IPC_STRUCT_TRAITS_MEMBER(page_url)
  IPC_STRUCT_TRAITS_MEMBER(keyword_url)
  IPC_STRUCT_TRAITS_MEMBER(frame_url)
  IPC_STRUCT_TRAITS_MEMBER(frame_page_state)
  IPC_STRUCT_TRAITS_MEMBER(media_flags)
  IPC_STRUCT_TRAITS_MEMBER(selection_text)
  IPC_STRUCT_TRAITS_MEMBER(suggested_filename)
  IPC_STRUCT_TRAITS_MEMBER(misspelled_word)
  IPC_STRUCT_TRAITS_MEMBER(misspelling_hash)
  IPC_STRUCT_TRAITS_MEMBER(dictionary_suggestions)
  IPC_STRUCT_TRAITS_MEMBER(spellcheck_enabled)
  IPC_STRUCT_TRAITS_MEMBER(is_editable)
  IPC_STRUCT_TRAITS_MEMBER(writing_direction_default)
  IPC_STRUCT_TRAITS_MEMBER(writing_direction_left_to_right)
  IPC_STRUCT_TRAITS_MEMBER(writing_direction_right_to_left)
  IPC_STRUCT_TRAITS_MEMBER(edit_flags)
  IPC_STRUCT_TRAITS_MEMBER(security_info)
  IPC_STRUCT_TRAITS_MEMBER(frame_charset)
  IPC_STRUCT_TRAITS_MEMBER(referrer_policy)
  IPC_STRUCT_TRAITS_MEMBER(custom_context)
  IPC_STRUCT_TRAITS_MEMBER(custom_items)
  IPC_STRUCT_TRAITS_MEMBER(source_type)
#if defined(OS_ANDROID)
  IPC_STRUCT_TRAITS_MEMBER(selection_start)
  IPC_STRUCT_TRAITS_MEMBER(selection_end)
#endif
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::CustomContextMenuContext)
  IPC_STRUCT_TRAITS_MEMBER(is_pepper_menu)
  IPC_STRUCT_TRAITS_MEMBER(request_id)
  IPC_STRUCT_TRAITS_MEMBER(render_widget_id)
  IPC_STRUCT_TRAITS_MEMBER(link_followed)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_BEGIN(FrameHostMsg_DidFailProvisionalLoadWithError_Params)
  
  IPC_STRUCT_MEMBER(int, error_code)
  
  
  IPC_STRUCT_MEMBER(base::string16, error_description)
  
  IPC_STRUCT_MEMBER(GURL, url)
  
  
  IPC_STRUCT_MEMBER(bool, showing_repost_interstitial)
IPC_STRUCT_END()

IPC_STRUCT_TRAITS_BEGIN(content::FrameNavigateParams)
  IPC_STRUCT_TRAITS_MEMBER(page_id)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(base_url)
  IPC_STRUCT_TRAITS_MEMBER(referrer)
  IPC_STRUCT_TRAITS_MEMBER(transition)
  IPC_STRUCT_TRAITS_MEMBER(redirects)
  IPC_STRUCT_TRAITS_MEMBER(should_update_history)
  IPC_STRUCT_TRAITS_MEMBER(searchable_form_url)
  IPC_STRUCT_TRAITS_MEMBER(searchable_form_encoding)
  IPC_STRUCT_TRAITS_MEMBER(contents_mime_type)
  IPC_STRUCT_TRAITS_MEMBER(socket_address)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_BEGIN_WITH_PARENT(FrameHostMsg_DidCommitProvisionalLoad_Params,
                             content::FrameNavigateParams)
  IPC_STRUCT_TRAITS_PARENT(content::FrameNavigateParams)

  
  
  IPC_STRUCT_MEMBER(std::string, security_info)

  
  IPC_STRUCT_MEMBER(content::NavigationGesture, gesture)

  
  IPC_STRUCT_MEMBER(bool, is_post)

  
  IPC_STRUCT_MEMBER(int64, post_id)

  
  
  
  IPC_STRUCT_MEMBER(bool, was_within_same_page)

  
  IPC_STRUCT_MEMBER(int, http_status_code)

  
  
  IPC_STRUCT_MEMBER(bool, url_is_unreachable)

  
  
  IPC_STRUCT_MEMBER(bool, was_fetched_via_proxy)

  
  IPC_STRUCT_MEMBER(content::PageState, page_state)

  
  IPC_STRUCT_MEMBER(GURL, original_request_url)

  
  IPC_STRUCT_MEMBER(bool, is_overriding_user_agent)

  
  
  IPC_STRUCT_MEMBER(bool, history_list_was_cleared)

  
  
  
  
  
  
  
  
  IPC_STRUCT_MEMBER(int, render_view_routing_id)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(FrameMsg_Navigate_Params)
  
  
  
  
  IPC_STRUCT_MEMBER(int32, page_id)

  
  
  
  IPC_STRUCT_MEMBER(int, pending_history_list_offset)

  
  
  IPC_STRUCT_MEMBER(int, current_history_list_offset)
  IPC_STRUCT_MEMBER(int, current_history_list_length)

  
  
  
  IPC_STRUCT_MEMBER(bool, should_clear_history_list)

  
  IPC_STRUCT_MEMBER(GURL, url)

  
  
  IPC_STRUCT_MEMBER(GURL, base_url_for_data_url)

  
  
  IPC_STRUCT_MEMBER(GURL, history_url_for_data_url)

  
  
  IPC_STRUCT_MEMBER(content::Referrer, referrer)

  
  
  IPC_STRUCT_MEMBER(std::vector<GURL>, redirects)

  
  IPC_STRUCT_MEMBER(ui::PageTransition, transition)

  
  
  
  IPC_STRUCT_MEMBER(bool, should_replace_current_entry)

  
  IPC_STRUCT_MEMBER(content::PageState, page_state)

  
  IPC_STRUCT_MEMBER(FrameMsg_Navigate_Type::Value, navigation_type)

  
  
  
  IPC_STRUCT_MEMBER(base::Time, request_time)

  
  IPC_STRUCT_MEMBER(std::string, extra_headers)

  
  
  
  
  IPC_STRUCT_MEMBER(int, transferred_request_child_id)
  IPC_STRUCT_MEMBER(int, transferred_request_request_id)

  
  IPC_STRUCT_MEMBER(bool, allow_download)

  
  IPC_STRUCT_MEMBER(bool, is_overriding_user_agent)

  
  IPC_STRUCT_MEMBER(bool, is_post)

  
  
  IPC_STRUCT_MEMBER(std::vector<unsigned char>, browser_initiated_post_data)

  
  
  IPC_STRUCT_MEMBER(bool, can_load_local_resources)

  
  IPC_STRUCT_MEMBER(std::string, frame_to_navigate)

  
  IPC_STRUCT_MEMBER(base::TimeTicks, browser_navigation_start)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(FrameHostMsg_OpenURL_Params)
  IPC_STRUCT_MEMBER(GURL, url)
  IPC_STRUCT_MEMBER(content::Referrer, referrer)
  IPC_STRUCT_MEMBER(WindowOpenDisposition, disposition)
  IPC_STRUCT_MEMBER(bool, should_replace_current_entry)
  IPC_STRUCT_MEMBER(bool, user_gesture)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(FrameHostMsg_BeginNavigation_Params)
  
  IPC_STRUCT_MEMBER(std::string, method)

  
  IPC_STRUCT_MEMBER(GURL, url)

  
  IPC_STRUCT_MEMBER(content::Referrer, referrer)

  
  IPC_STRUCT_MEMBER(std::string, headers)

  
  IPC_STRUCT_MEMBER(int, load_flags)

  
  IPC_STRUCT_MEMBER(scoped_refptr<content::ResourceRequestBody>,
                    request_body)

  
  IPC_STRUCT_MEMBER(bool, has_user_gesture)

  IPC_STRUCT_MEMBER(ui::PageTransition, transition_type)

  
  
  IPC_STRUCT_MEMBER(bool, should_replace_current_entry)

  
  IPC_STRUCT_MEMBER(bool, allow_download)
IPC_STRUCT_END()

#if defined(OS_MACOSX) || defined(OS_ANDROID)
IPC_STRUCT_BEGIN(FrameHostMsg_ShowPopup_Params)
  
  IPC_STRUCT_MEMBER(gfx::Rect, bounds)

  
  IPC_STRUCT_MEMBER(int, item_height)

  
  IPC_STRUCT_MEMBER(double, item_font_size)

  
  IPC_STRUCT_MEMBER(int, selected_item)

  
  IPC_STRUCT_MEMBER(std::vector<content::MenuItem>, popup_items)

  
  IPC_STRUCT_MEMBER(bool, right_aligned)

  
  IPC_STRUCT_MEMBER(bool, allow_multiple_selection)
IPC_STRUCT_END()
#endif


IPC_MESSAGE_ROUTED1(FrameMsg_CompositorFrameSwapped,
                    FrameMsg_CompositorFrameSwapped_Params )

IPC_MESSAGE_ROUTED0(FrameMsg_ChildFrameProcessGone)

IPC_MESSAGE_ROUTED1(FrameMsg_ContextMenuClosed,
                    content::CustomContextMenuContext )

IPC_MESSAGE_ROUTED2(FrameMsg_CustomContextMenuAction,
                    content::CustomContextMenuContext ,
                    unsigned )

IPC_MESSAGE_ROUTED0(FrameMsg_DisownOpener)

IPC_MESSAGE_CONTROL2(FrameMsg_NewFrame,
                     int ,
                     int )

IPC_MESSAGE_CONTROL3(FrameMsg_NewFrameProxy,
                     int ,
                     int ,
                     int )

IPC_MESSAGE_ROUTED1(FrameMsg_Navigate, FrameMsg_Navigate_Params)

IPC_MESSAGE_ROUTED0(FrameMsg_BeforeUnload)

IPC_MESSAGE_ROUTED1(FrameMsg_SwapOut,
                    int )

IPC_MESSAGE_ROUTED0(FrameMsg_Stop)

IPC_MESSAGE_ROUTED1(FrameMsg_CSSInsertRequest,
                    std::string  )

IPC_MESSAGE_ROUTED3(FrameMsg_JavaScriptExecuteRequest,
                    base::string16,  
                    int,  
                    bool  )

IPC_MESSAGE_ROUTED3(FrameMsg_JavaScriptExecuteRequestForTests,
                    base::string16,  
                    int,  
                    bool  )

IPC_MESSAGE_ROUTED2(FrameMsg_SetEditableSelectionOffsets,
                    int ,
                    int )

IPC_MESSAGE_ROUTED1(FrameMsg_SetupTransitionView,
                    std::string )

IPC_MESSAGE_ROUTED1(FrameMsg_BeginExitTransition,
                    std::string )

IPC_MESSAGE_ROUTED1(FrameMsg_Reload,
                    bool )

IPC_MESSAGE_ROUTED2(FrameMsg_DidChooseColorResponse, unsigned, SkColor)

IPC_MESSAGE_ROUTED1(FrameMsg_DidEndColorChooser, unsigned)

IPC_MESSAGE_ROUTED0(FrameMsg_DeleteProxy)

IPC_MESSAGE_ROUTED1(FrameMsg_TextSurroundingSelectionRequest,
                    size_t )

IPC_MESSAGE_ROUTED1(FrameMsg_AddStyleSheetByURL, std::string)

IPC_MESSAGE_ROUTED1(FrameMsg_SetAccessibilityMode,
                    AccessibilityMode)

#if defined(OS_ANDROID)

IPC_MESSAGE_ROUTED2(FrameMsg_SelectPopupMenuItems,
                    bool ,
                    std::vector<int> )

#elif defined(OS_MACOSX)

IPC_MESSAGE_ROUTED1(FrameMsg_SelectPopupMenuItem,
                    int )

#endif


IPC_MESSAGE_ROUTED4(FrameHostMsg_AddMessageToConsole,
                    int32, 
                    base::string16, 
                    int32, 
                    base::string16  )

IPC_SYNC_MESSAGE_CONTROL2_1(FrameHostMsg_CreateChildFrame,
                            int32 ,
                            std::string ,
                            int32 )

IPC_MESSAGE_ROUTED0(FrameHostMsg_Detach)

IPC_MESSAGE_ROUTED0(FrameHostMsg_FrameFocused)

IPC_MESSAGE_ROUTED2(FrameHostMsg_DidStartProvisionalLoadForFrame,
                    GURL ,
                    bool )

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidFailProvisionalLoadWithError,
                    FrameHostMsg_DidFailProvisionalLoadWithError_Params)

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidCommitProvisionalLoad,
                    FrameHostMsg_DidCommitProvisionalLoad_Params)

IPC_MESSAGE_ROUTED0(FrameHostMsg_DidFinishDocumentLoad)

IPC_MESSAGE_ROUTED3(FrameHostMsg_DidFailLoadWithError,
                    GURL ,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidStartLoading,
                    bool )

IPC_MESSAGE_ROUTED0(FrameHostMsg_DidStopLoading)

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidChangeLoadProgress,
                    double )

IPC_MESSAGE_ROUTED1(FrameHostMsg_OpenURL, FrameHostMsg_OpenURL_Params)

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidFinishLoad,
                    GURL )

IPC_MESSAGE_ROUTED0(FrameHostMsg_DocumentOnLoadCompleted)

IPC_MESSAGE_ROUTED0(FrameHostMsg_DidAccessInitialDocument)

IPC_MESSAGE_ROUTED0(FrameHostMsg_DidDisownOpener)

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidAssignPageId,
                    int32 )

IPC_MESSAGE_ROUTED3(FrameHostMsg_UpdateTitle,
                    int32 ,
                    base::string16 ,
                    blink::WebTextDirection )

IPC_MESSAGE_ROUTED1(FrameHostMsg_UpdateEncoding,
                    std::string )

IPC_MESSAGE_ROUTED2(FrameHostMsg_DomOperationResponse,
                    std::string  ,
                    int  )

IPC_MESSAGE_ROUTED3(FrameHostMsg_PepperPluginHung,
                    int ,
                    base::FilePath ,
                    bool )

IPC_MESSAGE_ROUTED2(FrameHostMsg_PluginCrashed,
                    base::FilePath ,
                    base::ProcessId )

IPC_SYNC_MESSAGE_CONTROL4_3(FrameHostMsg_GetPluginInfo,
                            int ,
                            GURL ,
                            GURL ,
                            std::string ,
                            bool ,
                            content::WebPluginInfo ,
                            std::string )

IPC_SYNC_MESSAGE_CONTROL4_2(FrameHostMsg_OpenChannelToPlugin,
                            int ,
                            GURL ,
                            GURL ,
                            std::string ,
                            IPC::ChannelHandle ,
                            content::WebPluginInfo )

IPC_MESSAGE_ROUTED1(FrameHostMsg_CompositorFrameSwappedACK,
                    FrameHostMsg_CompositorFrameSwappedACK_Params )

IPC_MESSAGE_ROUTED3(FrameHostMsg_BeforeUnload_ACK,
                    bool ,
                    base::TimeTicks ,
                    base::TimeTicks )

IPC_MESSAGE_ROUTED0(FrameHostMsg_SwapOut_ACK)

IPC_MESSAGE_ROUTED1(FrameHostMsg_ReclaimCompositorResources,
                    FrameHostMsg_ReclaimCompositorResources_Params )

IPC_MESSAGE_ROUTED1(FrameHostMsg_ForwardInputEvent,
                    IPC::WebInputEventPointer )

IPC_MESSAGE_ROUTED1(FrameHostMsg_ContextMenu, content::ContextMenuParams)

IPC_MESSAGE_ROUTED2(FrameHostMsg_InitializeChildFrame,
                    gfx::Rect ,
                    float )

IPC_MESSAGE_ROUTED2(FrameHostMsg_JavaScriptExecuteResponse,
                    int  ,
                    base::ListValue  )

IPC_SYNC_MESSAGE_ROUTED4_2(FrameHostMsg_RunJavaScriptMessage,
                           base::string16     ,
                           base::string16     ,
                           GURL               ,
                           content::JavaScriptMessageType ,
                           bool               ,
                           base::string16     )

IPC_SYNC_MESSAGE_ROUTED3_2(FrameHostMsg_RunBeforeUnloadConfirm,
                           GURL,           
                           base::string16  ,
                           bool            ,
                           bool            ,
                           base::string16  )

IPC_MESSAGE_ROUTED3(FrameHostMsg_OpenColorChooser,
                    int ,
                    SkColor ,
                    std::vector<content::ColorSuggestion> )

IPC_MESSAGE_ROUTED1(FrameHostMsg_EndColorChooser, int )

IPC_MESSAGE_ROUTED2(FrameHostMsg_SetSelectedColorInColorChooser,
                    int ,
                    SkColor )

IPC_MESSAGE_ROUTED4(FrameHostMsg_MediaPlayingNotification,
                    int64 ,
                    bool ,
                    bool ,
                    bool )

IPC_MESSAGE_ROUTED1(FrameHostMsg_MediaPausedNotification,
                    int64 )

IPC_MESSAGE_ROUTED1(FrameHostMsg_DidChangeThemeColor,
                    SkColor )

IPC_MESSAGE_ROUTED3(FrameHostMsg_TextSurroundingSelectionResponse,
                    base::string16,  
                    size_t, 
                    size_t )

IPC_MESSAGE_CONTROL4(FrameHostMsg_AddNavigationTransitionData,
                     int ,
                     std::string  ,
                     std::string  ,
                     std::string  )

IPC_MESSAGE_ROUTED1(FrameHostMsg_BeginNavigation,
                    FrameHostMsg_BeginNavigation_Params)

IPC_MESSAGE_ROUTED0(FrameHostMsg_DidFirstVisuallyNonEmptyPaint)

#if defined(OS_MACOSX) || defined(OS_ANDROID)

IPC_MESSAGE_ROUTED1(FrameHostMsg_ShowPopup,
                    FrameHostMsg_ShowPopup_Params)
IPC_MESSAGE_ROUTED0(FrameHostMsg_HidePopup)

#endif
