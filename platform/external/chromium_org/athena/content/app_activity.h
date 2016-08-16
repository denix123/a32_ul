// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_CONTENT_APP_ACTIVITY_H_
#define ATHENA_CONTENT_APP_ACTIVITY_H_

#include "athena/activity/public/activity.h"
#include "athena/activity/public/activity_view_model.h"
#include "athena/content/app_activity_proxy.h"
#include "base/memory/scoped_ptr.h"
#include "content/public/browser/web_contents_observer.h"

namespace extensions {
class AppWindow;
}

namespace views {
class WebView;
}

namespace athena {

class AppActivityRegistry;
class ContentProxy;

class AppActivity : public Activity,
                    public ActivityViewModel,
                    public content::WebContentsObserver {
 public:
  AppActivity(extensions::AppWindow* app_window, views::WebView* web_view);

  
  scoped_ptr<ContentProxy> GetContentProxy();

  
  virtual athena::ActivityViewModel* GetActivityViewModel() OVERRIDE;
  virtual void SetCurrentState(Activity::ActivityState state) OVERRIDE;
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
  virtual views::Widget* CreateWidget() OVERRIDE;
  virtual views::View* GetContentsView() OVERRIDE;
  virtual gfx::ImageSkia GetOverviewModeImage() OVERRIDE;
  virtual void PrepareContentsForOverview() OVERRIDE;
  virtual void ResetContentsView() OVERRIDE;

 protected:
  
  explicit AppActivity(const std::string& app_id);

  virtual ~AppActivity();

 private:
 
  virtual void TitleWasSet(content::NavigationEntry* entry,
                           bool explicit_set) OVERRIDE;
  virtual void DidUpdateFaviconURL(
      const std::vector<content::FaviconURL>& candidates) OVERRIDE;

  
  void RegisterActivity();

  
  void HideContentProxy();

  
  void ShowContentProxy();

  const std::string app_id_;

  views::WebView* web_view_;

  
  ActivityState current_state_;

  
  
  
  AppActivityRegistry* app_activity_registry_;

  
  scoped_ptr<ContentProxy> content_proxy_;

  DISALLOW_COPY_AND_ASSIGN(AppActivity);
};

}  

#endif  
