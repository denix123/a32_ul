// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_SIGNIN_SIGNIN_MANAGER_ANDROID_H_
#define CHROME_BROWSER_ANDROID_SIGNIN_SIGNIN_MANAGER_ANDROID_H_

#include <jni.h>

#include <string>

#include "base/android/scoped_java_ref.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "google_apis/gaia/merge_session_helper.h"

class GoogleServiceAuthError;
class Profile;

namespace policy {
class CloudPolicyClient;
}

class SigninManagerAndroid : public MergeSessionHelper::Observer {
 public:
  SigninManagerAndroid(JNIEnv* env, jobject obj);

  
  static bool Register(JNIEnv* env);

  void CheckPolicyBeforeSignIn(JNIEnv* env, jobject obj, jstring username);

  void FetchPolicyBeforeSignIn(JNIEnv* env, jobject obj);

  void OnSignInCompleted(JNIEnv* env, jobject obj, jstring username);

  void SignOut(JNIEnv* env, jobject obj);

  base::android::ScopedJavaLocalRef<jstring> GetManagementDomain(JNIEnv* env,
                                                                 jobject obj);

  void WipeProfileData(JNIEnv* env, jobject obj);

  void LogInSignedInUser(JNIEnv* env, jobject obj);

  void ClearLastSignedInUser(JNIEnv* env, jobject obj);

  jboolean IsSigninAllowedByPolicy(JNIEnv* env, jobject obj);

 private:
  virtual ~SigninManagerAndroid();

#if defined(ENABLE_CONFIGURATION_POLICY)
  void OnPolicyRegisterDone(const std::string& dm_token,
                            const std::string& client_id);
  void OnPolicyFetchDone(bool success);
#endif

  void OnBrowsingDataRemoverDone();

  void ClearLastSignedInUser();

  void OnSigninAllowedPrefChanged();

  
  virtual void MergeSessionCompleted(
      const std::string& account_id,
      const GoogleServiceAuthError& error) OVERRIDE;

  Profile* profile_;

  
  base::android::ScopedJavaGlobalRef<jobject> java_signin_manager_;

#if defined(ENABLE_CONFIGURATION_POLICY)
  
  
  std::string dm_token_;
  std::string client_id_;

  
  
  std::string username_;
#endif

  
  scoped_ptr<MergeSessionHelper> merge_session_helper_;

  PrefChangeRegistrar pref_change_registrar_;

  base::WeakPtrFactory<SigninManagerAndroid> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SigninManagerAndroid);
};

#endif  
