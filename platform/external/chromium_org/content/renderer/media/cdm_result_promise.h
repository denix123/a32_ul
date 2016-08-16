// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_CDM_RESULT_PROMISE_H_
#define CONTENT_RENDERER_MEDIA_CDM_RESULT_PROMISE_H_

#include <map>

#include "base/basictypes.h"
#include "media/base/cdm_promise.h"
#include "third_party/WebKit/public/platform/WebContentDecryptionModuleResult.h"

namespace content {

template <typename T>
class CdmResultPromise : public media::CdmPromiseTemplate<T> {
 public:
  explicit CdmResultPromise(
      const blink::WebContentDecryptionModuleResult& result);
  CdmResultPromise(const blink::WebContentDecryptionModuleResult& result,
                   const std::string& uma_name);
  virtual ~CdmResultPromise();

 protected:
  
  virtual void OnResolve(const T& result);
  void OnReject(media::MediaKeys::Exception exception_code,
                uint32 system_code,
                const std::string& error_message);

  blink::WebContentDecryptionModuleResult web_cdm_result_;

 private:
  DISALLOW_COPY_AND_ASSIGN(CdmResultPromise);
};

template <>
class CdmResultPromise<void> : public media::CdmPromiseTemplate<void> {
 public:
  explicit CdmResultPromise(
      const blink::WebContentDecryptionModuleResult& result);
  CdmResultPromise(const blink::WebContentDecryptionModuleResult& result,
                   const std::string& uma_name);
  virtual ~CdmResultPromise();

 protected:
  virtual void OnResolve();
  void OnReject(media::MediaKeys::Exception exception_code,
                uint32 system_code,
                const std::string& error_message);

  blink::WebContentDecryptionModuleResult web_cdm_result_;

 private:
  DISALLOW_COPY_AND_ASSIGN(CdmResultPromise);
};

typedef CdmResultPromise<void> SimpleCdmResultPromise;

}  

#endif  
