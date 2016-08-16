// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_INTERCEPTED_REQUEST_DATA_H_
#define ANDROID_WEBVIEW_BROWSER_INTERCEPTED_REQUEST_DATA_H_

#include <string>

#include "base/android/jni_android.h"
#include "base/memory/scoped_ptr.h"

namespace net {
class HttpResponseHeaders;
class NetworkDelegate;
class URLRequest;
class URLRequestJob;
}

namespace android_webview {

class InputStream;

class AwWebResourceResponse {
 public:
  virtual ~AwWebResourceResponse() {}

  virtual scoped_ptr<InputStream> GetInputStream(JNIEnv* env) const = 0;
  virtual bool GetMimeType(JNIEnv* env, std::string* mime_type) const = 0;
  virtual bool GetCharset(JNIEnv* env, std::string* charset) const = 0;
  virtual bool GetStatusInfo(JNIEnv* env,
                             int* status_code,
                             std::string* reason_phrase) const = 0;
  
  
  virtual bool GetResponseHeaders(
      JNIEnv* env,
      net::HttpResponseHeaders* headers) const = 0;

  
  
  
  
  static net::URLRequestJob* CreateJobFor(
      scoped_ptr<AwWebResourceResponse> aw_web_resource_response,
      net::URLRequest* request,
      net::NetworkDelegate* network_delegate);

 protected:
  AwWebResourceResponse() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(AwWebResourceResponse);
};

} 

#endif  
