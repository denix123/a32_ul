// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_CHILD_WEBCRYPTO_ALGORITHM_REGISTRY_H_
#define CONTENT_CHILD_WEBCRYPTO_ALGORITHM_REGISTRY_H_

#include "third_party/WebKit/public/platform/WebCrypto.h"

namespace content {

namespace webcrypto {

class AlgorithmImplementation;
class Status;

Status GetAlgorithmImplementation(blink::WebCryptoAlgorithmId id,
                                  const AlgorithmImplementation** impl);

}  

}  

#endif  
