// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_EXTENSION_CONSTANTS_H_
#define CHROME_COMMON_EXTENSIONS_EXTENSION_CONSTANTS_H_

#include <string>

#include "base/basictypes.h"
#include "url/gurl.h"

namespace extension_urls {

GURL GetDefaultWebstoreUpdateUrl();

extern const char kWebstoreSourceField[];

extern const char kLaunchSourceAppList[];
extern const char kLaunchSourceAppListSearch[];
extern const char kLaunchSourceAppListInfoDialog[];

}  

namespace extension_misc {

extern const char kBookmarkManagerId[];

extern const char kChromeAppId[];

extern const char kCloudPrintAppId[];

extern const char kEasyUnlockAppId[];

extern const char kEnterpriseWebStoreAppId[];

extern const char kGmailAppId[];

extern const char kGoogleDocAppId[];

extern const char kGooglePlayMusicAppId[];

extern const char kGoogleSearchAppId[];

extern const char kGoogleSheetsAppId[];

extern const char kGoogleSlidesAppId[];

extern const char kHTermAppId[];

extern const char kHTermDevAppId[];

extern const char kIdentityApiUiAppId[];

extern const char kCroshBuiltinAppId[];

extern const char kHotwordAudioVerificationAppId[];

extern const char kHotwordExtensionId[];

extern const char kHotwordSharedModuleId[];

extern const char kPdfExtensionId[];

extern const char kQuickOfficeComponentExtensionId[];

extern const char kQuickOfficeInternalExtensionId[];

extern const char kQuickOfficeExtensionId[];

extern const char kSettingsAppId[];

extern const char kStreamsPrivateTestExtensionId[];

extern const char kYoutubeAppId[];

extern const char kInAppPaymentsSupportAppId[];

extern const char kAppLaunchHistogram[];

extern const char kPlatformAppLaunchHistogram[];

enum AppLaunchBucket {
  
  APP_LAUNCH_NTP_APPS_MAXIMIZED,

  
  APP_LAUNCH_NTP_APPS_COLLAPSED,

  
  APP_LAUNCH_NTP_APPS_MENU,

  
  APP_LAUNCH_NTP_MOST_VISITED,

  
  APP_LAUNCH_NTP_RECENTLY_CLOSED,

  
  APP_LAUNCH_BOOKMARK_BAR,

  
  APP_LAUNCH_CONTENT_NAVIGATION,

  
  APP_LAUNCH_SESSION_RESTORE,

  
  APP_LAUNCH_AUTOLAUNCH,

  
  APP_LAUNCH_OMNIBOX_APP,

  
  APP_LAUNCH_OMNIBOX_LOCATION,

  
  APP_LAUNCH_OMNIBOX_INSTANT,

  
  APP_LAUNCH_EXTENSION_API,

  
  
  APP_LAUNCH_CMD_LINE_APP,

  
  APP_LAUNCH_CMD_LINE_URL,

  
  APP_LAUNCH_NTP_WEBSTORE,

  
  APP_LAUNCH_NTP_APP_RE_ENABLE,

  
  
  
  APP_LAUNCH_CMD_LINE_APP_LEGACY,

  
  APP_LAUNCH_NTP_WEBSTORE_FOOTER,

  
  APP_LAUNCH_NTP_WEBSTORE_PLUS_ICON,

  
  APP_LAUNCH_APP_LIST_MAIN,

  
  APP_LAUNCH_APP_LIST_SEARCH,

  
  APP_LAUNCH_APP_LIST_MAIN_CHROME,

  
  APP_LAUNCH_APP_LIST_MAIN_WEBSTORE,

  
  APP_LAUNCH_APP_LIST_SEARCH_CHROME,

  
  APP_LAUNCH_APP_LIST_SEARCH_WEBSTORE,
  APP_LAUNCH_BUCKET_BOUNDARY,
  APP_LAUNCH_BUCKET_INVALID
};

extern const char kChromeVoxExtensionId[];

#if defined(OS_CHROMEOS)
extern const char kChromeVoxExtensionPath[];
extern const char kChromeVoxManifestFilename[];
extern const char kChromeVoxGuestManifestFilename[];
extern const char kChromeVoxNextManifestFilename[];
extern const char kChromeVoxNextGuestManifestFilename[];
extern const char kBrailleImeExtensionId[];
extern const char kBrailleImeExtensionPath[];
extern const char kBrailleImeEngineId[];
extern const char kConnectivityDiagnosticsPath[];
extern const char kConnectivityDiagnosticsKioskPath[];
extern const char kConnectivityDiagnosticsLauncherPath[];
extern const char kSpeechSynthesisExtensionPath[];
extern const char kSpeechSynthesisExtensionId[];
extern const char kWallpaperManagerId[];
extern const char kFirstRunDialogId[];
#endif

enum CrxInstallCause {
  INSTALL_CAUSE_UNSET = 0,
  INSTALL_CAUSE_USER_DOWNLOAD,
  INSTALL_CAUSE_UPDATE,
  INSTALL_CAUSE_EXTERNAL_FILE,
  INSTALL_CAUSE_AUTOMATION,
  NUM_INSTALL_CAUSES
};

extern const char kAppStateNotInstalled[];
extern const char kAppStateInstalled[];
extern const char kAppStateDisabled[];
extern const char kAppStateRunning[];
extern const char kAppStateCannotRun[];
extern const char kAppStateReadyToRun[];

extern const char kMediaFileSystemPathPart[];

extern const uint8 kWebstoreSignaturesPublicKey[];
extern const int kWebstoreSignaturesPublicKeySize;

}  

namespace extensions {

enum LaunchType {
  LAUNCH_TYPE_INVALID = -1,
  LAUNCH_TYPE_FIRST = 0,
  LAUNCH_TYPE_PINNED = LAUNCH_TYPE_FIRST,
  LAUNCH_TYPE_REGULAR = 1,
  LAUNCH_TYPE_FULLSCREEN = 2,
  LAUNCH_TYPE_WINDOW = 3,
  NUM_LAUNCH_TYPES,

  
  
  
  LAUNCH_TYPE_DEFAULT = LAUNCH_TYPE_REGULAR
};

enum LaunchContainer {
  LAUNCH_CONTAINER_WINDOW,
  LAUNCH_CONTAINER_PANEL,
  LAUNCH_CONTAINER_TAB,
  
  
  LAUNCH_CONTAINER_NONE
};

}  

#endif  
