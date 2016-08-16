// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_NATIVE_PERMISSION_AW_PERMISSION_REQUEST_DELEGATE_H
#define ANDROID_WEBVIEW_NATIVE_PERMISSION_AW_PERMISSION_REQUEST_DELEGATE_H

#include "base/basictypes.h"
#include "base/macros.h"
#include "url/gurl.h"

namespace android_webview {

class AwPermissionRequestDelegate {
 public:
  AwPermissionRequestDelegate();
  virtual ~AwPermissionRequestDelegate();

  
  virtual const GURL& GetOrigin() = 0;

  
  virtual int64 GetResources() = 0;

  
  virtual void NotifyRequestResult(bool allowed) = 0;

  DISALLOW_COPY_AND_ASSIGN(AwPermissionRequestDelegate);
};

}  

#endif  
