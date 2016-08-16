// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_CRYPTO_PEPPER_CDM_WRAPPER_H_
#define CONTENT_RENDERER_MEDIA_CRYPTO_PEPPER_CDM_WRAPPER_H_

#if !defined(ENABLE_PEPPER_CDMS)
#error This file should only be included when ENABLE_PEPPER_CDMS is defined
#endif

#include <string>

#include "base/callback.h"

class GURL;

namespace content {
class ContentDecryptorDelegate;

class PepperCdmWrapper {
 public:
  virtual ~PepperCdmWrapper() {}

  
  virtual ContentDecryptorDelegate* GetCdmDelegate() = 0;

 protected:
  PepperCdmWrapper() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(PepperCdmWrapper);
};

typedef base::Callback<scoped_ptr<PepperCdmWrapper>(
    const std::string& pluginType,
    const GURL& security_origin)> CreatePepperCdmCB;

}  

#endif  
