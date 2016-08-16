// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_ANDROID_UI_RESOURCE_CLIENT_ANDROID_H_
#define CONTENT_PUBLIC_BROWSER_ANDROID_UI_RESOURCE_CLIENT_ANDROID_H_

#include "cc/resources/ui_resource_client.h"
#include "content/common/content_export.h"

namespace content {

class UIResourceProvider;

class CONTENT_EXPORT UIResourceClientAndroid : public cc::UIResourceClient {
 public:
  
  
  
  virtual void UIResourceIsInvalid() = 0;
};

}  

#endif  
