// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_PLAYER_TRACKER_H_
#define MEDIA_BASE_PLAYER_TRACKER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT PlayerTracker {
 public:
  virtual ~PlayerTracker();

  
  
  
  
  virtual int RegisterPlayer(const base::Closure& new_key_cb,
                             const base::Closure& cdm_unset_cb) = 0;

  
  
  
  virtual void UnregisterPlayer(int registration_id) = 0;

 protected:
  PlayerTracker();

 private:
  DISALLOW_COPY_AND_ASSIGN(PlayerTracker);
};

}  

#endif  
