// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdint.h>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/shared_memory.h"
#include "base/process/process.h"
#include "base/strings/string16.h"
#include "base/strings/stringprintf.h"
#include "base/values.h"
#include "build/build_config.h"
#include "chrome/common/common_param_traits.h"
#include "chrome/common/instant_types.h"
#include "chrome/common/ntp_logging_events.h"
#include "chrome/common/omnibox_focus_state.h"
#include "chrome/common/search_provider.h"
#include "chrome/common/web_application_info.h"
#include "components/content_settings/core/common/content_settings.h"
#include "components/content_settings/core/common/content_settings_pattern.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/nacl/common/nacl_types.h"
#include "content/public/common/common_param_traits.h"
#include "content/public/common/referrer.h"
#include "content/public/common/top_controls_state.h"
#include "ipc/ipc_channel_handle.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"
#include "third_party/WebKit/public/web/WebCache.h"
#include "third_party/WebKit/public/web/WebConsoleMessage.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/base/window_open_disposition.h"
#include "ui/gfx/ipc/gfx_param_traits.h"
#include "ui/gfx/rect.h"

#ifndef CHROME_COMMON_RENDER_MESSAGES_H_
#define CHROME_COMMON_RENDER_MESSAGES_H_

struct ChromeViewHostMsg_GetPluginInfo_Status {
  enum Value {
    kAllowed,
    kBlocked,
    kBlockedByPolicy,
    kClickToPlay,
    kDisabled,
    kNotFound,
    kNPAPINotSupported,
    kOutdatedBlocked,
    kOutdatedDisallowed,
    kUnauthorized,
  };

  ChromeViewHostMsg_GetPluginInfo_Status() : value(kAllowed) {}

  Value value;
};

namespace IPC {

template <>
struct ParamTraits<ContentSettingsPattern> {
  typedef ContentSettingsPattern param_type;
  static void Write(Message* m, const param_type& p);
  static bool Read(const Message* m, PickleIterator* iter, param_type* r);
  static void Log(const param_type& p, std::string* l);
};

}  

#endif  

#define IPC_MESSAGE_START ChromeMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(ChromeViewHostMsg_GetPluginInfo_Status::Value,
                          ChromeViewHostMsg_GetPluginInfo_Status::kUnauthorized)
IPC_ENUM_TRAITS(OmniboxFocusChangeReason)
IPC_ENUM_TRAITS(OmniboxFocusState)
IPC_ENUM_TRAITS(search_provider::OSDDType)
IPC_ENUM_TRAITS(search_provider::InstallState)
IPC_ENUM_TRAITS(ThemeBackgroundImageAlignment)
IPC_ENUM_TRAITS(ThemeBackgroundImageTiling)
IPC_ENUM_TRAITS(blink::WebConsoleMessage::Level)
IPC_ENUM_TRAITS(content::TopControlsState)

IPC_STRUCT_TRAITS_BEGIN(ChromeViewHostMsg_GetPluginInfo_Status)
IPC_STRUCT_TRAITS_MEMBER(value)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_BEGIN(ChromeViewHostMsg_GetPluginInfo_Output)
  IPC_STRUCT_MEMBER(ChromeViewHostMsg_GetPluginInfo_Status, status)
  IPC_STRUCT_MEMBER(content::WebPluginInfo, plugin)
  IPC_STRUCT_MEMBER(std::string, actual_mime_type)
  IPC_STRUCT_MEMBER(std::string, group_identifier)
  IPC_STRUCT_MEMBER(base::string16, group_name)
IPC_STRUCT_END()

IPC_STRUCT_TRAITS_BEGIN(ContentSettingsPattern::PatternParts)
  IPC_STRUCT_TRAITS_MEMBER(scheme)
  IPC_STRUCT_TRAITS_MEMBER(is_scheme_wildcard)
  IPC_STRUCT_TRAITS_MEMBER(host)
  IPC_STRUCT_TRAITS_MEMBER(has_domain_wildcard)
  IPC_STRUCT_TRAITS_MEMBER(port)
  IPC_STRUCT_TRAITS_MEMBER(is_port_wildcard)
  IPC_STRUCT_TRAITS_MEMBER(path)
  IPC_STRUCT_TRAITS_MEMBER(is_path_wildcard)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(ContentSettingPatternSource)
  IPC_STRUCT_TRAITS_MEMBER(primary_pattern)
  IPC_STRUCT_TRAITS_MEMBER(secondary_pattern)
  IPC_STRUCT_TRAITS_MEMBER(setting)
  IPC_STRUCT_TRAITS_MEMBER(source)
  IPC_STRUCT_TRAITS_MEMBER(incognito)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(InstantSuggestion)
  IPC_STRUCT_TRAITS_MEMBER(text)
  IPC_STRUCT_TRAITS_MEMBER(metadata)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(InstantMostVisitedItem)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(title)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(RendererContentSettingRules)
  IPC_STRUCT_TRAITS_MEMBER(image_rules)
  IPC_STRUCT_TRAITS_MEMBER(script_rules)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(RGBAColor)
  IPC_STRUCT_TRAITS_MEMBER(r)
  IPC_STRUCT_TRAITS_MEMBER(g)
  IPC_STRUCT_TRAITS_MEMBER(b)
  IPC_STRUCT_TRAITS_MEMBER(a)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(ThemeBackgroundInfo)
  IPC_STRUCT_TRAITS_MEMBER(using_default_theme)
  IPC_STRUCT_TRAITS_MEMBER(background_color)
  IPC_STRUCT_TRAITS_MEMBER(text_color)
  IPC_STRUCT_TRAITS_MEMBER(link_color)
  IPC_STRUCT_TRAITS_MEMBER(text_color_light)
  IPC_STRUCT_TRAITS_MEMBER(header_color)
  IPC_STRUCT_TRAITS_MEMBER(section_border_color)
  IPC_STRUCT_TRAITS_MEMBER(theme_id)
  IPC_STRUCT_TRAITS_MEMBER(image_horizontal_alignment)
  IPC_STRUCT_TRAITS_MEMBER(image_vertical_alignment)
  IPC_STRUCT_TRAITS_MEMBER(image_tiling)
  IPC_STRUCT_TRAITS_MEMBER(image_height)
  IPC_STRUCT_TRAITS_MEMBER(has_attribution)
  IPC_STRUCT_TRAITS_MEMBER(logo_alternate)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(blink::WebCache::ResourceTypeStat)
  IPC_STRUCT_TRAITS_MEMBER(count)
  IPC_STRUCT_TRAITS_MEMBER(size)
  IPC_STRUCT_TRAITS_MEMBER(liveSize)
  IPC_STRUCT_TRAITS_MEMBER(decodedSize)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(blink::WebCache::ResourceTypeStats)
  IPC_STRUCT_TRAITS_MEMBER(images)
  IPC_STRUCT_TRAITS_MEMBER(cssStyleSheets)
  IPC_STRUCT_TRAITS_MEMBER(scripts)
  IPC_STRUCT_TRAITS_MEMBER(xslStyleSheets)
  IPC_STRUCT_TRAITS_MEMBER(fonts)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(blink::WebCache::UsageStats)
  IPC_STRUCT_TRAITS_MEMBER(minDeadCapacity)
  IPC_STRUCT_TRAITS_MEMBER(maxDeadCapacity)
  IPC_STRUCT_TRAITS_MEMBER(capacity)
  IPC_STRUCT_TRAITS_MEMBER(liveSize)
  IPC_STRUCT_TRAITS_MEMBER(deadSize)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS_MAX_VALUE(NTPLoggingEventType,
                          NTP_NUM_EVENT_TYPES)

IPC_ENUM_TRAITS_MAX_VALUE(WebApplicationInfo::MobileCapable,
                          WebApplicationInfo::MOBILE_CAPABLE_APPLE)

IPC_STRUCT_TRAITS_BEGIN(WebApplicationInfo::IconInfo)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(width)
  IPC_STRUCT_TRAITS_MEMBER(height)
  IPC_STRUCT_TRAITS_MEMBER(data)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(WebApplicationInfo)
  IPC_STRUCT_TRAITS_MEMBER(title)
  IPC_STRUCT_TRAITS_MEMBER(description)
  IPC_STRUCT_TRAITS_MEMBER(app_url)
  IPC_STRUCT_TRAITS_MEMBER(icons)
  IPC_STRUCT_TRAITS_MEMBER(mobile_capable)
IPC_STRUCT_TRAITS_END()


#if !defined(OS_ANDROID) && !defined(OS_IOS)
IPC_MESSAGE_ROUTED1(ChromeViewMsg_WebUIJavaScript,
                    base::string16  )
#endif

IPC_MESSAGE_CONTROL1(ChromeViewMsg_SetContentSettingRules,
                     RendererContentSettingRules )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_LoadBlockedPlugins,
                    std::string )

IPC_MESSAGE_CONTROL0(ChromeViewMsg_GetCacheResourceStats)

IPC_MESSAGE_CONTROL2(ChromeViewMsg_SetFieldTrialGroup,
                     std::string ,
                     std::string )

IPC_MESSAGE_CONTROL0(ChromeViewMsg_GetV8HeapStats)

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SetPageSequenceNumber,
                    int )

IPC_MESSAGE_ROUTED0(ChromeViewMsg_DetermineIfPageSupportsInstant)

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxSetDisplayInstantResults,
                    bool )

IPC_MESSAGE_ROUTED2(ChromeViewMsg_SearchBoxFocusChanged,
                    OmniboxFocusState ,
                    OmniboxFocusChangeReason )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxMarginChange, int )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxMostVisitedItemsChanged,
                    std::vector<InstantMostVisitedItem> )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxPromoInformation,
                    bool )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxSetInputInProgress,
                    bool )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxSetSuggestionToPrefetch,
                    InstantSuggestion )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxSubmit,
                    base::string16 )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SearchBoxThemeChanged,
                    ThemeBackgroundInfo )

IPC_MESSAGE_ROUTED2(ChromeViewMsg_ChromeIdentityCheckResult,
                    base::string16 ,
                    bool )

IPC_MESSAGE_ROUTED0(ChromeViewMsg_SearchBoxToggleVoiceSearch)

IPC_MESSAGE_CONTROL1(ChromeViewMsg_SetIsIncognitoProcess,
                     bool )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SetAllowDisplayingInsecureContent,
                    bool )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SetAllowRunningInsecureContent,
                    bool )

IPC_MESSAGE_ROUTED0(ChromeViewMsg_ReloadFrame)

IPC_MESSAGE_ROUTED2(ChromeViewMsg_RequestFileSystemAccessAsyncResponse,
                    int  ,
                    bool )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_SetClientSidePhishingDetection,
                    bool )

IPC_MESSAGE_ROUTED2(ChromeViewMsg_RequestThumbnailForContextNode,
                    int ,
                    gfx::Size )

IPC_MESSAGE_ROUTED3(ChromeViewMsg_UpdateTopControlsState,
                    content::TopControlsState ,
                    content::TopControlsState ,
                    bool )


IPC_MESSAGE_ROUTED1(ChromeViewMsg_SetWindowFeatures,
                    blink::WebWindowFeatures )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_RequestThumbnailForContextNode_ACK,
                    SkBitmap ,
                    gfx::Size )

IPC_MESSAGE_ROUTED0(ChromeViewMsg_GetWebApplicationInfo)

#if defined(OS_ANDROID)
IPC_MESSAGE_ROUTED2(ChromeViewMsg_RetrieveMetaTagContent,
                    GURL ,
                    std::string  )
#endif  


IPC_SYNC_MESSAGE_CONTROL1_1(ChromeViewHostMsg_GetManagedAccounts,
                            GURL ,
                            std::vector<std::string> )

IPC_MESSAGE_CONTROL0(ChromeViewHostMsg_ShowBrowserAccountManagementUI)


IPC_MESSAGE_ROUTED0(ChromeViewMsg_SetAsInterstitial)

IPC_MESSAGE_ROUTED1(ChromeViewMsg_NetErrorInfo,
                    int )

IPC_MESSAGE_ROUTED5(ChromeViewMsg_SetNavigationCorrectionInfo,
                    GURL ,
                    std::string ,
                    std::string ,
                    std::string ,
                    GURL )


IPC_MESSAGE_CONTROL1(ChromeViewHostMsg_UpdatedCacheStats,
                     blink::WebCache::UsageStats )

IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_ContentBlocked,
                    ContentSettingsType )

IPC_SYNC_MESSAGE_CONTROL5_1(ChromeViewHostMsg_AllowDatabase,
                            int ,
                            GURL ,
                            GURL ,
                            base::string16 ,
                            base::string16 ,
                            bool )

IPC_SYNC_MESSAGE_CONTROL4_1(ChromeViewHostMsg_AllowDOMStorage,
                            int ,
                            GURL ,
                            GURL ,
                            bool ,
                            bool )

IPC_SYNC_MESSAGE_CONTROL3_1(ChromeViewHostMsg_RequestFileSystemAccessSync,
                            int ,
                            GURL ,
                            GURL ,
                            bool )

IPC_MESSAGE_CONTROL4(ChromeViewHostMsg_RequestFileSystemAccessAsync,
                    int ,
                    int ,
                    GURL ,
                    GURL )

IPC_SYNC_MESSAGE_CONTROL4_1(ChromeViewHostMsg_AllowIndexedDB,
                            int ,
                            GURL ,
                            GURL ,
                            base::string16 ,
                            bool )

IPC_SYNC_MESSAGE_CONTROL4_1(ChromeViewHostMsg_GetPluginInfo,
                            int ,
                            GURL ,
                            GURL ,
                            std::string ,
                            ChromeViewHostMsg_GetPluginInfo_Output )

#if defined(ENABLE_PEPPER_CDMS)
IPC_SYNC_MESSAGE_CONTROL1_3(
    ChromeViewHostMsg_IsInternalPluginAvailableForMimeType,
    std::string ,
    bool ,
    std::vector<base::string16> ,
    std::vector<base::string16> )
#endif

#if defined(ENABLE_PLUGIN_INSTALLATION)
IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_FindMissingPlugin,
                    int ,
                    std::string )

IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_RemovePluginPlaceholderHost,
                    int )

IPC_MESSAGE_ROUTED1(ChromeViewMsg_FoundMissingPlugin,
                    base::string16 )

IPC_MESSAGE_ROUTED0(ChromeViewMsg_DidNotFindMissingPlugin)

IPC_MESSAGE_ROUTED0(ChromeViewMsg_StartedDownloadingPlugin)

IPC_MESSAGE_ROUTED0(ChromeViewMsg_FinishedDownloadingPlugin)

IPC_MESSAGE_ROUTED1(ChromeViewMsg_ErrorDownloadingPlugin,
                    std::string )
#endif  

IPC_MESSAGE_ROUTED0(ChromeViewMsg_CancelledDownloadingPlugin)

IPC_MESSAGE_ROUTED0(ChromeViewHostMsg_OpenAboutPlugins)

IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_CouldNotLoadPlugin,
                    base::FilePath )

IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_NPAPINotSupported,
                    std::string )

IPC_MESSAGE_ROUTED0(ChromeViewMsg_NPAPINotSupported)

IPC_MESSAGE_ROUTED3(ChromeViewHostMsg_PageHasOSDD,
                    GURL ,
                    GURL ,
                    search_provider::OSDDType)

IPC_SYNC_MESSAGE_ROUTED2_1(ChromeViewHostMsg_GetSearchProviderInstallState,
                           GURL ,
                           GURL ,
                           search_provider::InstallState )

IPC_MESSAGE_CONTROL2(ChromeViewHostMsg_V8HeapStats,
                     int ,
                     int )

IPC_MESSAGE_CONTROL1(ChromeViewHostMsg_DnsPrefetch,
                     std::vector<std::string> )

IPC_MESSAGE_CONTROL1(ChromeViewHostMsg_Preconnect,
                     GURL )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_BlockedOutdatedPlugin,
                    int ,
                    std::string )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_BlockedUnauthorizedPlugin,
                    base::string16 ,
                    std::string )

IPC_MESSAGE_CONTROL1(ChromeViewHostMsg_ResourceTypeStats,
                     blink::WebCache::ResourceTypeStats)

IPC_MESSAGE_ROUTED0(ChromeViewHostMsg_CancelPrerenderForPrinting)

IPC_MESSAGE_ROUTED0(ChromeViewHostMsg_DidBlockDisplayingInsecureContent)

IPC_MESSAGE_ROUTED0(ChromeViewHostMsg_DidBlockRunningInsecureContent)

IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_DidGetWebApplicationInfo,
                    WebApplicationInfo)

#if defined(OS_ANDROID)
IPC_MESSAGE_ROUTED4(ChromeViewHostMsg_DidRetrieveMetaTagContent,
                    bool ,
                    std::string ,
                    std::string ,
                    GURL )
#endif  

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_LogEvent,
                    int ,
                    NTPLoggingEventType )

IPC_MESSAGE_ROUTED3(ChromeViewHostMsg_LogMostVisitedImpression,
                    int ,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED3(ChromeViewHostMsg_LogMostVisitedNavigation,
                    int ,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_ChromeIdentityCheck,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_FocusOmnibox,
                    int ,
                    OmniboxFocusState )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_PasteAndOpenDropdown,
                    int ,
                    base::string16 )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_InstantSupportDetermined,
                    int ,
                    bool )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_SearchBoxDeleteMostVisitedItem,
                    int ,
                    GURL )

IPC_MESSAGE_ROUTED4(ChromeViewHostMsg_SearchBoxNavigate,
                    int ,
                    GURL ,
                    WindowOpenDisposition ,
                    bool )

IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_SearchBoxUndoAllMostVisitedDeletions,
                    int )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_SearchBoxUndoMostVisitedDeletion,
                    int ,
                    GURL )

IPC_MESSAGE_ROUTED2(ChromeViewHostMsg_SetVoiceSearchSupported,
                    int ,
                    bool )

IPC_MESSAGE_CONTROL2(ChromeViewMsg_SetSearchURLs,
                     std::vector<GURL> ,
                     GURL )

#if defined(ENABLE_PLUGINS)
IPC_SYNC_MESSAGE_CONTROL0_1(ChromeViewHostMsg_IsCrashReportingEnabled,
                            bool )
#endif
