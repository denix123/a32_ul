// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ANDROID_TAB_MODEL_TAB_MODEL_H_
#define CHROME_BROWSER_UI_ANDROID_TAB_MODEL_TAB_MODEL_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/sync/glue/synced_window_delegate.h"
#include "chrome/browser/ui/toolbar/toolbar_model.h"
#include "chrome/browser/ui/toolbar/toolbar_model_delegate.h"
#include "components/sessions/session_id.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace browser_sync {
class SyncedWindowDelegate;
class SyncedWindowDelegateAndroid;
}

namespace content {
class WebContents;
}

class Profile;
class TabAndroid;

class TabModel : public content::NotificationObserver {
 public:
  virtual Profile* GetProfile() const;
  virtual bool IsOffTheRecord() const;
  virtual browser_sync::SyncedWindowDelegate* GetSyncedWindowDelegate() const;
  virtual SessionID::id_type GetSessionId() const;

  virtual int GetTabCount() const = 0;
  virtual int GetActiveIndex() const = 0;
  virtual content::WebContents* GetWebContentsAt(int index) const = 0;
  
  virtual TabAndroid* GetTabAt(int index) const = 0;

  virtual void SetActiveIndex(int index) = 0;
  virtual void CloseTabAt(int index) = 0;

  
  virtual void CreateTab(content::WebContents* web_contents,
                         int parent_tab_id) = 0;

  
  
  virtual content::WebContents* CreateNewTabForDevTools(const GURL& url) = 0;

  
  virtual bool IsSessionRestoreInProgress() const = 0;

 protected:
  explicit TabModel(Profile* profile);
  virtual ~TabModel();

  
  
  void BroadcastSessionRestoreComplete();

  ToolbarModel* GetToolbarModel();

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  Profile* profile_;

  
  bool is_off_the_record_;

  
  scoped_ptr<browser_sync::SyncedWindowDelegateAndroid> synced_window_delegate_;

  
  
  
  SessionID session_id_;

  
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(TabModel);
};

#endif  
