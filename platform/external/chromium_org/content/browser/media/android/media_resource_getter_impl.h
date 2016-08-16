// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_MEDIA_ANDROID_MEDIA_RESOURCE_GETTER_IMPL_H_
#define CONTENT_BROWSER_MEDIA_ANDROID_MEDIA_RESOURCE_GETTER_IMPL_H_

#include <jni.h>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "media/base/android/media_resource_getter.h"
#include "media/base/android/media_url_interceptor.h"
#include "net/base/auth.h"
#include "net/cookies/canonical_cookie.h"

namespace storage {
class FileSystemContext;
}

namespace net {
class URLRequestContextGetter;
}

namespace content {

class BrowserContext;
class ResourceContext;

class MediaResourceGetterImpl : public media::MediaResourceGetter {
 public:
  
  
  
  MediaResourceGetterImpl(BrowserContext* browser_context,
                          storage::FileSystemContext* file_system_context,
                          int render_process_id,
                          int render_frame_id);
  virtual ~MediaResourceGetterImpl();

  
  
  virtual void GetAuthCredentials(
      const GURL& url,
      const GetAuthCredentialsCB& callback) OVERRIDE;
  virtual void GetCookies(
      const GURL& url,
      const GURL& first_party_for_cookies,
      const GetCookieCB& callback) OVERRIDE;
  virtual void GetPlatformPathFromURL(
      const GURL& url,
      const GetPlatformPathCB& callback) OVERRIDE;
  virtual void ExtractMediaMetadata(
      const std::string& url,
      const std::string& cookies,
      const std::string& user_agent,
      const ExtractMediaMetadataCB& callback) OVERRIDE;
  virtual void ExtractMediaMetadata(
      const int fd,
      const int64 offset,
      const int64 size,
      const ExtractMediaMetadataCB& callback) OVERRIDE;

  static bool RegisterMediaResourceGetter(JNIEnv* env);

 private:
  
  void GetAuthCredentialsCallback(
      const GetAuthCredentialsCB& callback,
      const net::AuthCredentials& credentials);

  
  void GetCookiesCallback(
      const GetCookieCB& callback, const std::string& cookies);

  
  void GetPlatformPathCallback(
      const GetPlatformPathCB& callback, const std::string& platform_path);

  
  BrowserContext* browser_context_;

  
  storage::FileSystemContext* file_system_context_;

  
  int render_process_id_;

  
  int render_frame_id_;

  
  base::WeakPtrFactory<MediaResourceGetterImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaResourceGetterImpl);
};

}  

#endif  
