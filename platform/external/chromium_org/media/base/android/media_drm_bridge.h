// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_DRM_BRIDGE_H_
#define MEDIA_BASE_ANDROID_MEDIA_DRM_BRIDGE_H_

#include <jni.h>
#include <string>
#include <vector>

#include "base/android/scoped_java_ref.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/browser_cdm.h"
#include "media/base/media_export.h"
#include "media/cdm/player_tracker_impl.h"
#include "url/gurl.h"

class GURL;

namespace media {

class MediaPlayerManager;

class MEDIA_EXPORT MediaDrmBridge : public BrowserCdm {
 public:
  enum SecurityLevel {
    SECURITY_LEVEL_NONE = 0,
    SECURITY_LEVEL_1 = 1,
    SECURITY_LEVEL_3 = 3,
  };

  typedef base::Callback<void(bool)> ResetCredentialsCB;

  virtual ~MediaDrmBridge();

  
  
  
  static bool IsAvailable();

  static bool IsSecurityLevelSupported(const std::string& key_system,
                                       SecurityLevel security_level);

  
  static bool IsKeySystemSupported(const std::string& key_system);

  
  
  static std::vector<std::string> GetPlatformKeySystemNames();

  
  
  static bool IsKeySystemSupportedWithType(
      const std::string& key_system,
      const std::string& container_mime_type);

  static bool IsSecureDecoderRequired(SecurityLevel security_level);

  static bool RegisterMediaDrmBridge(JNIEnv* env);

  
  
  static scoped_ptr<MediaDrmBridge> Create(
      const std::string& key_system,
      const SessionCreatedCB& session_created_cb,
      const SessionMessageCB& session_message_cb,
      const SessionReadyCB& session_ready_cb,
      const SessionClosedCB& session_closed_cb,
      const SessionErrorCB& session_error_cb);

  
  
  
  static scoped_ptr<MediaDrmBridge> CreateSessionless(
      const std::string& key_system);

  
  
  
  
  
  
  
  bool SetSecurityLevel(SecurityLevel security_level);

  
  virtual bool CreateSession(uint32 session_id,
                             const std::string& content_type,
                             const uint8* init_data,
                             int init_data_length) OVERRIDE;
  virtual void LoadSession(uint32 session_id,
                           const std::string& web_session_id) OVERRIDE;
  virtual void UpdateSession(uint32 session_id,
                             const uint8* response,
                             int response_length) OVERRIDE;
  virtual void ReleaseSession(uint32 session_id) OVERRIDE;
  virtual int RegisterPlayer(const base::Closure& new_key_cb,
                             const base::Closure& cdm_unset_cb) OVERRIDE;
  virtual void UnregisterPlayer(int registration_id) OVERRIDE;

  
  
  base::android::ScopedJavaLocalRef<jobject> GetMediaCrypto();

  
  
  void SetMediaCryptoReadyCB(const base::Closure& closure);

  
  void OnMediaCryptoReady(JNIEnv* env, jobject j_media_drm);

  
  void OnSessionCreated(JNIEnv* env,
                        jobject j_media_drm,
                        jint j_session_id,
                        jstring j_web_session_id);
  void OnSessionMessage(JNIEnv* env,
                        jobject j_media_drm,
                        jint j_session_id,
                        jbyteArray j_message,
                        jstring j_destination_url);
  void OnSessionReady(JNIEnv* env, jobject j_media_drm, jint j_session_id);
  void OnSessionClosed(JNIEnv* env, jobject j_media_drm, jint j_session_id);
  void OnSessionError(JNIEnv* env, jobject j_media_drm, jint j_session_id);

  
  void ResetDeviceCredentials(const ResetCredentialsCB& callback);

  
  void OnResetDeviceCredentialsCompleted(JNIEnv* env, jobject, bool success);

  
  
  bool IsProtectedSurfaceRequired();

 private:
  MediaDrmBridge(const std::vector<uint8>& scheme_uuid,
                 const SessionCreatedCB& session_created_cb,
                 const SessionMessageCB& session_message_cb,
                 const SessionReadyCB& session_ready_cb,
                 const SessionClosedCB& session_closed_cb,
                 const SessionErrorCB& session_error_cb);

  
  SecurityLevel GetSecurityLevel();

  
  std::vector<uint8> scheme_uuid_;

  
  base::android::ScopedJavaGlobalRef<jobject> j_media_drm_;

  
  SessionCreatedCB session_created_cb_;
  SessionMessageCB session_message_cb_;
  SessionReadyCB session_ready_cb_;
  SessionClosedCB session_closed_cb_;
  SessionErrorCB session_error_cb_;

  base::Closure media_crypto_ready_cb_;

  ResetCredentialsCB reset_credentials_cb_;

  PlayerTrackerImpl player_tracker_;

  DISALLOW_COPY_AND_ASSIGN(MediaDrmBridge);
};

}  

#endif  
