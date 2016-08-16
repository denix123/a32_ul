// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ZOOM_ZOOM_CONTROLLER_H_
#define CHROME_BROWSER_UI_ZOOM_ZOOM_CONTROLLER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_member.h"
#include "content/public/browser/host_zoom_map.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"

class ZoomObserver;

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}  

class ZoomController : public content::WebContentsObserver,
                       public content::WebContentsUserData<ZoomController> {
 public:
  
  enum ZoomMode {
    
    
    
    ZOOM_MODE_DEFAULT,
    
    
    
    ZOOM_MODE_ISOLATED,
    
    
    
    
    ZOOM_MODE_MANUAL,
    
    
    ZOOM_MODE_DISABLED,
  };

  struct ZoomChangedEventData {
    ZoomChangedEventData(content::WebContents* web_contents,
                         double old_zoom_level,
                         double new_zoom_level,
                         ZoomController::ZoomMode zoom_mode,
                         bool can_show_bubble)
        : web_contents(web_contents),
          old_zoom_level(old_zoom_level),
          new_zoom_level(new_zoom_level),
          zoom_mode(zoom_mode),
          can_show_bubble(can_show_bubble) {}
    content::WebContents* web_contents;
    double old_zoom_level;
    double new_zoom_level;
    ZoomController::ZoomMode zoom_mode;
    bool can_show_bubble;
  };

  virtual ~ZoomController();

  ZoomMode zoom_mode() const { return zoom_mode_; }

  
  
  double GetDefaultZoomLevel() const {
    
    
    return content::HostZoomMap::GetDefaultForBrowserContext(browser_context_)->
        GetDefaultZoomLevel();
  }

  
  bool IsAtDefaultZoom() const;

  
  int GetResourceForZoomLevel() const;

  const extensions::Extension* last_extension() const {
    return last_extension_.get();
  }

  void AddObserver(ZoomObserver* observer);
  void RemoveObserver(ZoomObserver* observer);

  
  
  
  void SetShowsNotificationBubble(bool can_show_bubble) {
    can_show_bubble_ = can_show_bubble;
  }

  
  
  double GetZoomLevel() const;
  
  
  
  virtual int GetZoomPercent() const;

  
  
  bool SetZoomLevel(double zoom_level);

  
  
  bool SetZoomLevelByExtension(
      double zoom_level,
      const scoped_refptr<const extensions::Extension>& extension);

  
  void SetZoomMode(ZoomMode zoom_mode);

  
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;
  virtual void WebContentsDestroyed() OVERRIDE;

 protected:
  
  explicit ZoomController(content::WebContents* web_contents);

 private:
  friend class content::WebContentsUserData<ZoomController>;
  friend class ZoomControllerTest;

  void OnZoomLevelChanged(const content::HostZoomMap::ZoomLevelChange& change);

  
  
  
  
  void UpdateState(const std::string& host);

  
  bool can_show_bubble_;

  
  ZoomMode zoom_mode_;

  
  double zoom_level_;

  scoped_ptr<ZoomChangedEventData> event_data_;

  
  
  scoped_refptr<const extensions::Extension> last_extension_;

  
  ObserverList<ZoomObserver> observers_;

  content::BrowserContext* browser_context_;

  scoped_ptr<content::HostZoomMap::Subscription> zoom_subscription_;

  DISALLOW_COPY_AND_ASSIGN(ZoomController);
};

#endif  
