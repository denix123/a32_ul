// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_BANNERS_APP_BANNER_MANAGER_H_
#define CHROME_BROWSER_ANDROID_BANNERS_APP_BANNER_MANAGER_H_

#include "base/android/jni_android.h"
#include "base/android/jni_weak_ref.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/android/meta_tag_observer.h"
#include "chrome/browser/bitmap_fetcher/bitmap_fetcher.h"

namespace content {
struct FrameNavigateParams;
struct LoadCommittedDetails;
}  


namespace banners {

class AppBannerManager : public chrome::BitmapFetcherDelegate,
                         public MetaTagObserver {
 public:
  AppBannerManager(JNIEnv* env, jobject obj);
  virtual ~AppBannerManager();

  
  void Destroy(JNIEnv* env, jobject obj);

  
  void BlockBanner(JNIEnv* env, jobject obj, jstring jurl, jstring jpackage);

  
  void ReplaceWebContents(JNIEnv* env,
                          jobject obj,
                          jobject jweb_contents);

  
  
  bool FetchIcon(JNIEnv* env,
                 jobject obj,
                 jstring jimage_url);

  
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;

  
  virtual void OnFetchComplete(const GURL url, const SkBitmap* bitmap) OVERRIDE;

 private:
  
  
  virtual void HandleMetaTagContent(const std::string& tag_content,
                                    const GURL& expected_url) OVERRIDE;

  
  scoped_ptr<chrome::BitmapFetcher> fetcher_;

  
  JavaObjectWeakGlobalRef weak_java_banner_view_manager_;

  DISALLOW_COPY_AND_ASSIGN(AppBannerManager);
};  

bool RegisterAppBannerManager(JNIEnv* env);

}  

#endif  
