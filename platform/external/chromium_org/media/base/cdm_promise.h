// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_CDM_PROMISE_H_
#define MEDIA_BASE_CDM_PROMISE_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "media/base/media_export.h"
#include "media/base/media_keys.h"

namespace media {

class MEDIA_EXPORT CdmPromise {
 public:
  
  enum ResultCodeForUMA {
    SUCCESS,
    NOT_SUPPORTED_ERROR,
    INVALID_STATE_ERROR,
    INVALID_ACCESS_ERROR,
    QUOTA_EXCEEDED_ERROR,
    UNKNOWN_ERROR,
    CLIENT_ERROR,
    OUTPUT_ERROR,
    NUM_RESULT_CODES
  };

  enum ResolveParameterType {
    VOID_TYPE,
    STRING_TYPE,
    KEY_IDS_VECTOR_TYPE
  };

  typedef base::Callback<void(MediaKeys::Exception exception_code,
                              uint32 system_code,
                              const std::string& error_message)>
      PromiseRejectedCB;

  virtual ~CdmPromise();

  
  
  
  
  virtual void reject(MediaKeys::Exception exception_code,
                      uint32 system_code,
                      const std::string& error_message);

  ResolveParameterType GetResolveParameterType() const {
    return parameter_type_;
  }

 protected:
  explicit CdmPromise(ResolveParameterType parameter_type);
  CdmPromise(ResolveParameterType parameter_type, PromiseRejectedCB reject_cb);

  
  
  
  CdmPromise(ResolveParameterType parameter_type,
             PromiseRejectedCB reject_cb,
             const std::string& uma_name);

  
  
  void ReportResultToUMA(ResultCodeForUMA result);

  const ResolveParameterType parameter_type_;
  PromiseRejectedCB reject_cb_;

  
  bool is_pending_;

  
  std::string uma_name_;

  DISALLOW_COPY_AND_ASSIGN(CdmPromise);
};

template <typename T>
class MEDIA_EXPORT CdmPromiseTemplate : public CdmPromise {
 public:
  CdmPromiseTemplate(base::Callback<void(const T&)> resolve_cb,
                     PromiseRejectedCB rejected_cb);
  CdmPromiseTemplate(base::Callback<void(const T&)> resolve_cb,
                     PromiseRejectedCB rejected_cb,
                     const std::string& uma_name);
  virtual void resolve(const T& result);

 protected:
  
  CdmPromiseTemplate();

 private:
  base::Callback<void(const T&)> resolve_cb_;

  DISALLOW_COPY_AND_ASSIGN(CdmPromiseTemplate);
};

template <>
class MEDIA_EXPORT CdmPromiseTemplate<void> : public CdmPromise {
 public:
  CdmPromiseTemplate(base::Callback<void(void)> resolve_cb,
                     PromiseRejectedCB rejected_cb);
  CdmPromiseTemplate(base::Callback<void(void)> resolve_cb,
                     PromiseRejectedCB rejected_cb,
                     const std::string& uma_name);
  virtual void resolve();

 protected:
  
  CdmPromiseTemplate();

 private:
  base::Callback<void(void)> resolve_cb_;

  DISALLOW_COPY_AND_ASSIGN(CdmPromiseTemplate);
};

}  

#endif  
