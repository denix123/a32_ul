// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_BUFFERING_STATE_H_
#define MEDIA_BASE_BUFFERING_STATE_H_

#include "base/callback_forward.h"

namespace media {

enum BufferingState {
  
  
  
  BUFFERING_HAVE_NOTHING,

  
  
  
  BUFFERING_HAVE_ENOUGH,
};

typedef base::Callback<void(BufferingState)> BufferingStateCB;

}  

#endif  
