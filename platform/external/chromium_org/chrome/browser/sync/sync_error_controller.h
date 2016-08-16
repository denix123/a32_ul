// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_SYNC_ERROR_CONTROLLER_H_
#define CHROME_BROWSER_SYNC_SYNC_ERROR_CONTROLLER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"

class Profile;
class ProfileSyncService;

class SyncErrorController : public ProfileSyncServiceObserver {
 public:
  
  
  class Observer {
   public:
    virtual ~Observer() {}
    virtual void OnErrorChanged() = 0;
  };

  explicit SyncErrorController(ProfileSyncService* service);
  virtual ~SyncErrorController();

  
  bool HasError();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  virtual void OnStateChanged() OVERRIDE;

 private:
  ProfileSyncService* service_;
  ObserverList<Observer, true> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(SyncErrorController);
};

#endif  
