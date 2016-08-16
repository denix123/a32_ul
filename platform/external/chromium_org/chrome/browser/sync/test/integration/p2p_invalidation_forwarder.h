// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_TEST_INTEGRATION_P2P_INVALIDATION_FORWARDER_H_
#define CHROME_BROWSER_SYNC_TEST_INTEGRATION_P2P_INVALIDATION_FORWARDER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"

class ProfileSyncService;

namespace invalidation {
class P2PInvalidationService;
};

class P2PInvalidationForwarder : public ProfileSyncServiceObserver {
 public:
  P2PInvalidationForwarder(
      ProfileSyncService* sync_service,
      invalidation::P2PInvalidationService* invalidation_service);
  virtual ~P2PInvalidationForwarder();

  
  virtual void OnStateChanged() OVERRIDE;
  virtual void OnSyncCycleCompleted() OVERRIDE;

 private:
  ProfileSyncService* sync_service_;
  invalidation::P2PInvalidationService* invalidation_service_;

  DISALLOW_COPY_AND_ASSIGN(P2PInvalidationForwarder);
};

#endif  
