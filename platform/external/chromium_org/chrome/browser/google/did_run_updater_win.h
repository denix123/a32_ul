// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GOOGLE_DID_RUN_UPDATER_WIN_H_
#define CHROME_BROWSER_GOOGLE_DID_RUN_UPDATER_WIN_H_

#include "base/macros.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class DidRunUpdater : public content::NotificationObserver {
 public:
  DidRunUpdater();
  ~DidRunUpdater() override;

 private:
  
  void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) override;

  
  bool system_level_;
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(DidRunUpdater);
};

#endif  
