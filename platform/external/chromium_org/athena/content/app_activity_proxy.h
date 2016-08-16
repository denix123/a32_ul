// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_CONTENT_APP_ACTIVITY_PROXY_H_
#define ATHENA_CONTENT_APP_ACTIVITY_PROXY_H_

#include <vector>

#include "athena/activity/public/activity.h"
#include "athena/activity/public/activity_view_model.h"
#include "athena/content/content_proxy.h"
#include "base/memory/scoped_ptr.h"

namespace athena {

class AppActivity;
class AppActivityRegistry;

class AppActivityProxy : public Activity,
                         public ActivityViewModel {
 public:
  
  
  
  AppActivityProxy(AppActivity* replaced_activity,
                   AppActivityRegistry* creator);

 protected:
  virtual ~AppActivityProxy();

 
  virtual ActivityViewModel* GetActivityViewModel() OVERRIDE;
  virtual void SetCurrentState(ActivityState state) OVERRIDE;
  virtual ActivityState GetCurrentState() OVERRIDE;
  virtual bool IsVisible() OVERRIDE;
  virtual ActivityMediaState GetMediaState() OVERRIDE;
  virtual aura::Window* GetWindow() OVERRIDE;
  virtual content::WebContents* GetWebContents() OVERRIDE;

  
  virtual void Init() OVERRIDE;
  virtual SkColor GetRepresentativeColor() const OVERRIDE;
  virtual base::string16 GetTitle() const OVERRIDE;
  virtual gfx::ImageSkia GetIcon() const OVERRIDE;
  virtual bool UsesFrame() const OVERRIDE;
  virtual views::View* GetContentsView() OVERRIDE;
  virtual views::Widget* CreateWidget() OVERRIDE;
  virtual gfx::ImageSkia GetOverviewModeImage() OVERRIDE;
  virtual void PrepareContentsForOverview() OVERRIDE;
  virtual void ResetContentsView() OVERRIDE;

 private:
  
  
  AppActivityRegistry* app_activity_registry_;

  
  const base::string16 title_;
  const SkColor color_;

  
  
  
  AppActivity* replaced_activity_;

  
  views::View* view_;

  
  scoped_ptr<ContentProxy> content_proxy_;

  DISALLOW_COPY_AND_ASSIGN(AppActivityProxy);
};

}  

#endif  
