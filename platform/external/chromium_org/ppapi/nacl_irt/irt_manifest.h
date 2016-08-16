// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_NACL_IRT_IRT_MANIFEST_H_
#define PPAPI_NACL_IRT_IRT_MANIFEST_H_

#include "ppapi/proxy/ppapi_proxy_export.h"

namespace ppapi {

PPAPI_PROXY_EXPORT int IrtOpenResource(const char* file, int* fd);

}  

#endif  
