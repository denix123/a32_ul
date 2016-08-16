// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_MOST_VISITED_SITES_H_
#define CHROME_BROWSER_ANDROID_MOST_VISITED_SITES_H_

#include <jni.h>

#include "base/android/scoped_java_ref.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/profiles/profile.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "components/history/core/browser/history_types.h"
#include "components/suggestions/proto/suggestions.pb.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace suggestions {
class SuggestionsService;
}

class MostVisitedSites : public ProfileSyncServiceObserver,
                         public content::NotificationObserver {
 public:
  typedef base::Callback<
      void(base::android::ScopedJavaGlobalRef<jobject>* bitmap,
           base::android::ScopedJavaGlobalRef<jobject>* j_callback)>
      LookupSuccessCallback;

  explicit MostVisitedSites(Profile* profile);
  void Destroy(JNIEnv* env, jobject obj);
  void OnLoadingComplete(JNIEnv* env, jobject obj);
  void SetMostVisitedURLsObserver(JNIEnv* env,
                                  jobject obj,
                                  jobject j_observer,
                                  jint num_sites);
  void GetURLThumbnail(JNIEnv* env,
                       jobject obj,
                       jstring url,
                       jobject j_callback);
  void BlacklistUrl(JNIEnv* env, jobject obj, jstring j_url);
  void RecordOpenedMostVisitedItem(JNIEnv* env, jobject obj, jint index);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnStateChanged() OVERRIDE;

  
  static bool Register(JNIEnv* env);

 private:
  virtual ~MostVisitedSites();
  void QueryMostVisitedURLs();

  
  
  void InitiateTopSitesQuery();

  
  void OnMostVisitedURLsAvailable(
      base::android::ScopedJavaGlobalRef<jobject>* j_observer,
      int num_sites,
      const history::MostVisitedURLList& visited_list);

  
  void OnSuggestionsProfileAvailable(
      base::android::ScopedJavaGlobalRef<jobject>* j_observer,
      const suggestions::SuggestionsProfile& suggestions_profile);

  
  void OnObtainedThumbnail(
      base::android::ScopedJavaGlobalRef<jobject>* bitmap,
      base::android::ScopedJavaGlobalRef<jobject>* j_callback);

  
  void GetSuggestionsThumbnailOnUIThread(
      suggestions::SuggestionsService* suggestions_service,
      const std::string& url_string,
      base::android::ScopedJavaGlobalRef<jobject>* j_callback);

  
  void OnSuggestionsThumbnailAvailable(
      base::android::ScopedJavaGlobalRef<jobject>* j_callback,
      const GURL& url,
      const SkBitmap* bitmap);

  
  void RecordUMAMetrics();

  
  Profile* profile_;

  
  base::android::ScopedJavaGlobalRef<jobject> observer_;

  
  int num_sites_;

  
  bool is_control_group_;

  

  
  int num_local_thumbs_;
  
  int num_server_thumbs_;
  
  
  int num_empty_thumbs_;

  
  suggestions::SuggestionsProfile server_suggestions_;

  
  base::WeakPtrFactory<MostVisitedSites> weak_ptr_factory_;

  content::NotificationRegistrar registrar_;

  
  enum MostVisitedSource {
    TOP_SITES,
    SUGGESTIONS_SERVICE
  };
  MostVisitedSource mv_source_;

  DISALLOW_COPY_AND_ASSIGN(MostVisitedSites);
};

#endif  
