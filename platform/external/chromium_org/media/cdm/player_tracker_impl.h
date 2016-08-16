// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CDM_PLAYER_TRACKER_IMPL_H_
#define MEDIA_CDM_PLAYER_TRACKER_IMPL_H_

#include <map>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/threading/thread_checker.h"
#include "media/base/media_export.h"
#include "media/base/player_tracker.h"

namespace media {

class MEDIA_EXPORT PlayerTrackerImpl : public PlayerTracker {
 public:
  PlayerTrackerImpl();
  virtual ~PlayerTrackerImpl();

  
  virtual int RegisterPlayer(const base::Closure& new_key_cb,
                             const base::Closure& cdm_unset_cb) OVERRIDE;
  virtual void UnregisterPlayer(int registration_id) OVERRIDE;

  
  void NotifyNewKey();
  void NotifyCdmUnset();

 private:
  struct PlayerCallbacks {
    PlayerCallbacks(base::Closure new_key_cb, base::Closure cdm_unset_cb);
    ~PlayerCallbacks();

    base::Closure new_key_cb;
    base::Closure cdm_unset_cb;
  };

  int next_registration_id_;
  std::map<int, PlayerCallbacks> player_callbacks_map_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(PlayerTrackerImpl);
};

}  

#endif  
