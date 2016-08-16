// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_TOOLBAR_WRENCH_MENU_BADGE_CONTROLLER_H_
#define CHROME_BROWSER_UI_TOOLBAR_WRENCH_MENU_BADGE_CONTROLLER_H_

#include "base/macros.h"
#include "chrome/browser/ui/toolbar/wrench_icon_painter.h"
#include "content/public/browser/notification_details.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/notification_service.h"

class Profile;

class WrenchMenuBadgeController : public content::NotificationObserver {
 public:
  enum BadgeType {
    BADGE_TYPE_NONE,
    BADGE_TYPE_UPGRADE_NOTIFICATION,
    BADGE_TYPE_GLOBAL_ERROR,
    BADGE_TYPE_INCOMPATIBILITY_WARNING,
  };

  
  class Delegate {
   public:
    
    
    
    virtual void UpdateBadgeSeverity(BadgeType type,
                                     WrenchIconPainter::Severity severity,
                                     bool animate) = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  WrenchMenuBadgeController(Profile* profile, Delegate* delegate);
  virtual ~WrenchMenuBadgeController();

  
  
  
  
  void UpdateDelegate();

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  Profile* profile_;
  Delegate* delegate_;
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(WrenchMenuBadgeController);
};

#endif  
