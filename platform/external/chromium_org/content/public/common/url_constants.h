// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_COMMON_URL_CONSTANTS_H_
#define CONTENT_PUBLIC_COMMON_URL_CONSTANTS_H_

#include "content/common/content_export.h"
#include "url/url_constants.h"


namespace content {

CONTENT_EXPORT extern const char kChromeDevToolsScheme[];
CONTENT_EXPORT extern const char kChromeUIScheme[];  
CONTENT_EXPORT extern const char kGuestScheme[];
CONTENT_EXPORT extern const char kMetadataScheme[];
CONTENT_EXPORT extern const char kSwappedOutScheme[];
CONTENT_EXPORT extern const char kViewSourceScheme[];

CONTENT_EXPORT extern const char kAboutSrcDocURL[];

CONTENT_EXPORT extern const char kChromeUIAccessibilityHost[];
CONTENT_EXPORT extern const char kChromeUIAppCacheInternalsHost[];
CONTENT_EXPORT extern const char kChromeUIBlobInternalsHost[];
CONTENT_EXPORT extern const char kChromeUIBrowserCrashHost[];
CONTENT_EXPORT extern const char kChromeUIGpuHost[];
CONTENT_EXPORT extern const char kChromeUIHistogramHost[];
CONTENT_EXPORT extern const char kChromeUIIndexedDBInternalsHost[];
CONTENT_EXPORT extern const char kChromeUIMediaInternalsHost[];
CONTENT_EXPORT extern const char kChromeUINetworkViewCacheHost[];
CONTENT_EXPORT extern const char kChromeUIResourcesHost[];
CONTENT_EXPORT extern const char kChromeUIServiceWorkerInternalsHost[];
CONTENT_EXPORT extern const char kChromeUITcmallocHost[];
CONTENT_EXPORT extern const char kChromeUITracingHost[];
CONTENT_EXPORT extern const char kChromeUIWebRTCInternalsHost[];

CONTENT_EXPORT extern const char kChromeUIBrowserCrashURL[];
CONTENT_EXPORT extern const char kChromeUICrashURL[];
CONTENT_EXPORT extern const char kChromeUIDumpURL[];
CONTENT_EXPORT extern const char kChromeUIGpuCleanURL[];
CONTENT_EXPORT extern const char kChromeUIGpuCrashURL[];
CONTENT_EXPORT extern const char kChromeUIGpuHangURL[];
CONTENT_EXPORT extern const char kChromeUIHangURL[];
CONTENT_EXPORT extern const char kChromeUIKillURL[];
CONTENT_EXPORT extern const char kChromeUIPpapiFlashCrashURL[];
CONTENT_EXPORT extern const char kChromeUIPpapiFlashHangURL[];
CONTENT_EXPORT extern const char kChromeUIServiceWorkerInternalsURL[];

CONTENT_EXPORT extern const char kUnreachableWebDataURL[];

CONTENT_EXPORT extern const char kChromeUINetworkViewCacheURL[];
CONTENT_EXPORT extern const char kChromeUIShorthangURL[];

CONTENT_EXPORT extern const char kSwappedOutURL[];

}  

#endif  