// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_SYNC_ONE_CLICK_SIGNIN_SYNC_OBSERVER_H_
#define CHROME_BROWSER_UI_SYNC_ONE_CLICK_SIGNIN_SYNC_OBSERVER_H_

#include "base/memory/weak_ptr.h"
#include "chrome/browser/sync/profile_sync_service_observer.h"
#include "content/public/browser/web_contents_observer.h"
#include "url/gurl.h"

class ProfileSyncService;

namespace content {
class WebContents;
}

class OneClickSigninSyncObserver : public content::WebContentsObserver,
                                   public ProfileSyncServiceObserver {
 public:
  
  
  
  OneClickSigninSyncObserver(content::WebContents* web_contents,
                             const GURL& continue_url);

 protected:
  
  virtual ~OneClickSigninSyncObserver();

 private:
  
  virtual void WebContentsDestroyed() OVERRIDE;

  
  virtual void OnStateChanged() OVERRIDE;

  
  void LoadContinueUrl();

  
  
  ProfileSyncService* GetSyncService(content::WebContents* web_contents);

  
  static void DeleteObserver(
      base::WeakPtr<OneClickSigninSyncObserver> observer);

  
  const GURL continue_url_;

  base::WeakPtrFactory<OneClickSigninSyncObserver> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(OneClickSigninSyncObserver);
};

#endif  
