// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_SHORTCUT_HELPER_H_
#define CHROME_BROWSER_ANDROID_SHORTCUT_HELPER_H_

#include "base/android/jni_android.h"
#include "base/android/jni_weak_ref.h"
#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "base/task/cancelable_task_tracker.h"
#include "chrome/common/web_application_info.h"
#include "components/favicon_base/favicon_types.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/common/manifest.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationLockType.h"

namespace content {
class WebContents;
}  

namespace IPC {
class Message;
}

class GURL;

class ShortcutHelper : public content::WebContentsObserver {
 public:
  ShortcutHelper(JNIEnv* env,
                 jobject obj,
                 content::WebContents* web_contents);

  
  
  
  void Initialize();

  
  
  void TearDown(JNIEnv* env, jobject obj);

  
  void OnDidGetWebApplicationInfo(const WebApplicationInfo& web_app_info);

  
  void OnDidGetManifest(const content::Manifest& manifest);

  
  void AddShortcut(JNIEnv* env,
                   jobject obj,
                   jstring title,
                   jint launcher_large_icon_size);

  
  void OnDidDownloadIcon(int id,
                         int http_status_code,
                         const GURL& url,
                         const std::vector<SkBitmap>& bitmaps,
                         const std::vector<gfx::Size>& sizes);

  
  
  void AddShortcutUsingManifestIcon();

  
  
  
  void AddShortcutUsingFavicon();

  
  void OnDidGetFavicon(
      const favicon_base::FaviconRawBitmapResult& bitmap_result);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void WebContentsDestroyed() OVERRIDE;

  
  
  static void AddShortcutInBackgroundWithRawBitmap(
      const GURL& url,
      const base::string16& title,
      content::Manifest::DisplayMode display,
      const favicon_base::FaviconRawBitmapResult& bitmap_result,
      blink::WebScreenOrientationLockType orientation);

  
  
  static void AddShortcutInBackgroundWithSkBitmap(
      const GURL& url,
      const base::string16& title,
      content::Manifest::DisplayMode display,
      const SkBitmap& icon_bitmap,
      blink::WebScreenOrientationLockType orientation);

  
  static bool RegisterShortcutHelper(JNIEnv* env);

 private:
  enum ManifestIconStatus {
    MANIFEST_ICON_STATUS_NONE,
    MANIFEST_ICON_STATUS_FETCHING,
    MANIFEST_ICON_STATUS_DONE
  };

  virtual ~ShortcutHelper();

  void Destroy();

  
  
  
  GURL FindBestMatchingIcon(
      const std::vector<content::Manifest::Icon>& icons) const;

  
  
  
  
  GURL FindBestMatchingIcon(const std::vector<content::Manifest::Icon>& icons,
                            float density) const;

  
  
  static std::vector<content::Manifest::Icon> FilterIconsByType(
      const std::vector<content::Manifest::Icon>& icons);

  
  bool IconSizesContainsPreferredSize(
      const std::vector<gfx::Size>& sizes) const;

  
  bool IconSizesContainsAny(const std::vector<gfx::Size>& sizes) const;

  JavaObjectWeakGlobalRef java_ref_;

  GURL url_;
  base::string16 title_;
  content::Manifest::DisplayMode display_;
  SkBitmap manifest_icon_;
  base::CancelableTaskTracker cancelable_task_tracker_;
  blink::WebScreenOrientationLockType orientation_;

  bool add_shortcut_requested_;

  ManifestIconStatus manifest_icon_status_;
  const int preferred_icon_size_in_px_;
  static const int kPreferredIconSizeInDp;

  base::WeakPtrFactory<ShortcutHelper> weak_ptr_factory_;

  friend class ShortcutHelperTest;
  DISALLOW_COPY_AND_ASSIGN(ShortcutHelper);
};

#endif  
