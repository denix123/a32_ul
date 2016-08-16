// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_TAB_ANDROID_H_
#define CHROME_BROWSER_ANDROID_TAB_ANDROID_H_

#include <jni.h>

#include "base/android/jni_weak_ref.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "chrome/browser/search/instant_service_observer.h"
#include "chrome/browser/sync/glue/synced_tab_delegate_android.h"
#include "chrome/browser/ui/search/search_tab_helper_delegate.h"
#include "chrome/browser/ui/tab_contents/core_tab_helper_delegate.h"
#include "chrome/browser/ui/toolbar/toolbar_model.h"
#include "components/sessions/session_id.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class GURL;
class Profile;
class SkBitmap;

namespace chrome {
struct NavigateParams;
}

namespace chrome {
namespace android {
class ChromeWebContentsDelegateAndroid;
}
}

namespace content {
class ContentViewCore;
class WebContents;
}

namespace prerender {
class PrerenderManager;
}

class TabAndroid : public CoreTabHelperDelegate,
                   public InstantServiceObserver,
                   public SearchTabHelperDelegate,
                   public content::NotificationObserver {
 public:
  enum TabLoadStatus {
#define DEFINE_TAB_LOAD_STATUS(name, value)  name = value,
#include "chrome/browser/android/tab_load_status.h"
#undef DEFINE_TAB_LOAD_STATUS
  };

  
  
  static TabAndroid* FromWebContents(content::WebContents* web_contents);

  
  
  static TabAndroid* GetNativeTab(JNIEnv* env, jobject obj);

  
  static void AttachTabHelpers(content::WebContents* web_contents);

  TabAndroid(JNIEnv* env, jobject obj);
  virtual ~TabAndroid();

  base::android::ScopedJavaLocalRef<jobject> GetJavaObject();

  
  content::WebContents* web_contents() const { return web_contents_.get(); }

  
  const SessionID& session_id() const { return session_tab_id_; }
  int GetAndroidId() const;
  int GetSyncId() const;

  
  base::string16 GetTitle() const;

  
  GURL GetURL() const;

  
  bool LoadIfNeeded();

  
  
  content::ContentViewCore* GetContentViewCore() const;
  Profile* GetProfile() const;
  browser_sync::SyncedTabDelegate* GetSyncedTabDelegate() const;

  void SetWindowSessionID(SessionID::id_type window_id);
  void SetSyncId(int sync_id);

  virtual void HandlePopupNavigation(chrome::NavigateParams* params);

  
  
  virtual bool ShouldWelcomePageLinkToTermsOfService();

  bool HasPrerenderedUrl(GURL gurl);

  void MakeLoadURLParams(
      chrome::NavigateParams* params,
      content::NavigationController::LoadURLParams* load_url_params);

  

  virtual void SwapTabContents(content::WebContents* old_contents,
                               content::WebContents* new_contents,
                               bool did_start_load,
                               bool did_finish_load) OVERRIDE;

  
  void DefaultSearchProviderChanged() OVERRIDE;

  
  virtual void OnWebContentsInstantSupportDisabled(
      const content::WebContents* web_contents) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  

  virtual void Destroy(JNIEnv* env, jobject obj);
  virtual void InitWebContents(JNIEnv* env,
                               jobject obj,
                               jboolean incognito,
                               jobject jcontent_view_core,
                               jobject jweb_contents_delegate,
                               jobject jcontext_menu_populator);
  virtual void DestroyWebContents(JNIEnv* env,
                                  jobject obj,
                                  jboolean delete_native);
  base::android::ScopedJavaLocalRef<jobject> GetProfileAndroid(JNIEnv* env,
                                                               jobject obj);
  virtual TabLoadStatus LoadUrl(JNIEnv* env,
                                jobject obj,
                                jstring url,
                                jstring j_extra_headers,
                                jbyteArray j_post_data,
                                jint page_transition,
                                jstring j_referrer_url,
                                jint referrer_policy,
                                jboolean is_renderer_initiated);
  ToolbarModel::SecurityLevel GetSecurityLevel(JNIEnv* env, jobject obj);
  void SetActiveNavigationEntryTitleForUrl(JNIEnv* env,
                                           jobject obj,
                                           jstring jurl,
                                           jstring jtitle);
  bool Print(JNIEnv* env, jobject obj);
  
  
  base::android::ScopedJavaLocalRef<jobject> GetFavicon(JNIEnv* env,
                                                        jobject obj);
  jboolean IsFaviconValid(JNIEnv* env, jobject jobj);

  
  static bool RegisterTabAndroid(JNIEnv* env);

 private:
  prerender::PrerenderManager* GetPrerenderManager() const;

  JavaObjectWeakGlobalRef weak_java_tab_;

  
  SessionID session_tab_id_;

  
  SessionID session_window_id_;

  content::NotificationRegistrar notification_registrar_;

  scoped_ptr<content::WebContents> web_contents_;
  scoped_ptr<chrome::android::ChromeWebContentsDelegateAndroid>
      web_contents_delegate_;

  scoped_ptr<browser_sync::SyncedTabDelegateAndroid> synced_tab_delegate_;

  DISALLOW_COPY_AND_ASSIGN(TabAndroid);
};

#endif  
