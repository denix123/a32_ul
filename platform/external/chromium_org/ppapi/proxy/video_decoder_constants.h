// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_VIDEO_DECODER_CONSTANTS_H_
#define PPAPI_PROXY_VIDEO_DECODER_CONSTANTS_H_

namespace ppapi {
namespace proxy {

enum {
  
  kMaximumPendingDecodes = 8,

  
  
  kMinimumBitstreamBufferSize = 100 << 10,

  
  
  kMaximumBitstreamBufferSize = 4 << 20
};

}  
}  

#endif  
