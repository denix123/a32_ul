// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_DOM_DISTILLER_FEEDBACK_REPORTER_ANDROID_H_
#define CHROME_BROWSER_ANDROID_DOM_DISTILLER_FEEDBACK_REPORTER_ANDROID_H_

#include <jni.h>

#include "base/android/jni_weak_ref.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"

namespace content {
struct FrameNavigateParams;
struct LoadCommittedDetails;
}  

namespace dom_distiller {

namespace android {

class FeedbackReporterAndroid : content::WebContentsObserver {
 public:
  FeedbackReporterAndroid(JNIEnv* env, jobject obj);
  virtual ~FeedbackReporterAndroid();

  
  void Destroy(JNIEnv* env, jobject obj);

  
  void ReplaceWebContents(JNIEnv* env, jobject obj, jobject jweb_contents);

  
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;

 private:
  
  JavaObjectWeakGlobalRef weak_java_feedback_reporter_;

  DISALLOW_COPY_AND_ASSIGN(FeedbackReporterAndroid);
};

bool RegisterFeedbackReporter(JNIEnv* env);

}  

}  

#endif  
