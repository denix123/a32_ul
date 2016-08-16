// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_HOST_ZOOM_MAP_H_
#define CONTENT_PUBLIC_BROWSER_HOST_ZOOM_MAP_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/callback_list.h"
#include "content/common/content_export.h"

namespace content {

class BrowserContext;
class ResourceContext;
class WebContents;

// Maps hostnames to custom zoom levels.  Written on the UI thread and read on

class HostZoomMap {
 public:
  
  enum ZoomLevelChangeMode {
    ZOOM_CHANGED_FOR_HOST,            
    ZOOM_CHANGED_FOR_SCHEME_AND_HOST, 
                                      
    ZOOM_CHANGED_TEMPORARY_ZOOM,      
                                      
  };

  
  
  struct ZoomLevelChange {
    ZoomLevelChangeMode mode;
    std::string host;
    std::string scheme;
    double zoom_level;
  };

  typedef std::vector<ZoomLevelChange> ZoomLevelVector;

  CONTENT_EXPORT static HostZoomMap* GetDefaultForBrowserContext(
      BrowserContext* browser_context);

  
  
  CONTENT_EXPORT static double GetZoomLevel(const WebContents* web_contents);

  
  
  CONTENT_EXPORT static void SetZoomLevel(const WebContents* web_contents,
                                          double level);

  
  
  virtual void CopyFrom(HostZoomMap* copy) = 0;

  
  
  
  
  
  
  virtual double GetZoomLevelForHostAndScheme(
      const std::string& scheme,
      const std::string& host) const = 0;

  
  
  
  
  virtual bool HasZoomLevel(const std::string& scheme,
                            const std::string& host) const = 0;

  
  virtual ZoomLevelVector GetAllZoomLevels() const = 0;

  
  
  
  
  // otherwise the new value is written out.
  
  
  
  virtual void SetZoomLevelForHost(const std::string& host, double level) = 0;

  
  
  
  
  
  
  
  virtual void SetZoomLevelForHostAndScheme(const std::string& scheme,
                                            const std::string& host,
                                            double level) = 0;

  
  
  virtual bool UsesTemporaryZoomLevel(int render_process_id,
                                      int render_view_id) const = 0;

  
  
  
  
  virtual void SetTemporaryZoomLevel(int render_process_id,
                                     int render_view_id,
                                     double level) = 0;

  
  
  
  virtual void ClearTemporaryZoomLevel(int render_process_id,
                                       int render_view_id) = 0;

  
  virtual double GetDefaultZoomLevel() const = 0;
  virtual void SetDefaultZoomLevel(double level) = 0;;

  typedef base::Callback<void(const ZoomLevelChange&)> ZoomLevelChangedCallback;
  typedef base::CallbackList<void(const ZoomLevelChange&)>::Subscription
      Subscription;
  
  virtual scoped_ptr<Subscription> AddZoomLevelChangedCallback(
      const ZoomLevelChangedCallback& callback) = 0;

 protected:
  virtual ~HostZoomMap() {}
};

}  

#endif  
