// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CDM_BROWSER_CDM_MESSAGE_FILTER_ANDROID_H_
#define COMPONENTS_CDM_BROWSER_CDM_MESSAGE_FILTER_ANDROID_H_

#include "base/basictypes.h"
#include "content/public/browser/browser_message_filter.h"

struct SupportedKeySystemRequest;
struct SupportedKeySystemResponse;

namespace cdm {

class CdmMessageFilterAndroid
    : public content::BrowserMessageFilter {
 public:
  CdmMessageFilterAndroid();

 private:
  virtual ~CdmMessageFilterAndroid();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OverrideThreadForMessage(
      const IPC::Message& message,
      content::BrowserThread::ID* thread) OVERRIDE;

  
  void OnQueryKeySystemSupport(const SupportedKeySystemRequest& request,
                               SupportedKeySystemResponse* response);

  void OnGetPlatformKeySystemNames(std::vector<std::string>* key_systems);

  DISALLOW_COPY_AND_ASSIGN(CdmMessageFilterAndroid);
};

}  

#endif  
