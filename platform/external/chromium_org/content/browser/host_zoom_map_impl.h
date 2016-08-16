// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_HOST_ZOOM_MAP_IMPL_H_
#define CONTENT_BROWSER_HOST_ZOOM_MAP_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/sequenced_task_runner_helpers.h"
#include "base/supports_user_data.h"
#include "base/synchronization/lock.h"
#include "content/public/browser/host_zoom_map.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace content {

class WebContentsImpl;

class CONTENT_EXPORT HostZoomMapImpl : public NON_EXPORTED_BASE(HostZoomMap),
                                       public NotificationObserver,
                                       public base::SupportsUserData::Data {
 public:
  HostZoomMapImpl();
  virtual ~HostZoomMapImpl();

  
  virtual void CopyFrom(HostZoomMap* copy) OVERRIDE;
  virtual double GetZoomLevelForHostAndScheme(
      const std::string& scheme,
      const std::string& host) const OVERRIDE;
  
  virtual bool HasZoomLevel(const std::string& scheme,
                            const std::string& host) const OVERRIDE;
  virtual ZoomLevelVector GetAllZoomLevels() const OVERRIDE;
  virtual void SetZoomLevelForHost(
      const std::string& host,
      double level) OVERRIDE;
  virtual void SetZoomLevelForHostAndScheme(
      const std::string& scheme,
      const std::string& host,
      double level) OVERRIDE;
  virtual bool UsesTemporaryZoomLevel(int render_process_id,
                                      int render_view_id) const OVERRIDE;
  virtual void SetTemporaryZoomLevel(int render_process_id,
                                     int render_view_id,
                                     double level) OVERRIDE;

  virtual void ClearTemporaryZoomLevel(int render_process_id,
                                       int render_view_id) OVERRIDE;
  virtual double GetDefaultZoomLevel() const OVERRIDE;
  virtual void SetDefaultZoomLevel(double level) OVERRIDE;
  virtual scoped_ptr<Subscription> AddZoomLevelChangedCallback(
      const ZoomLevelChangedCallback& callback) OVERRIDE;

  
  
  double GetZoomLevelForWebContents(
      const WebContentsImpl& web_contents_impl) const;

  
  
  
  void SetZoomLevelForWebContents(const WebContentsImpl& web_contents_impl,
                                  double level);

  
  
  void SetZoomLevelForView(int render_process_id,
                           int render_view_id,
                           double level,
                           const std::string& host);

  
  
  
  
  
  double GetTemporaryZoomLevel(int render_process_id,
                               int render_view_id) const;

  
  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

 private:
  typedef std::map<std::string, double> HostZoomLevels;
  typedef std::map<std::string, HostZoomLevels> SchemeHostZoomLevels;

  struct RenderViewKey {
    int render_process_id;
    int render_view_id;
    RenderViewKey(int render_process_id, int render_view_id)
        : render_process_id(render_process_id),
          render_view_id(render_view_id) {}
    bool operator<(const RenderViewKey& other) const {
      return render_process_id < other.render_process_id ||
             ((render_process_id == other.render_process_id) &&
              (render_view_id < other.render_view_id));
    }
  };

  typedef std::map<RenderViewKey, double> TemporaryZoomLevels;

  double GetZoomLevelForHost(const std::string& host) const;

  
  
  
  void SendZoomLevelChange(const std::string& scheme,
                           const std::string& host,
                           double level);

  
  base::CallbackList<void(const ZoomLevelChange&)>
      zoom_level_changed_callbacks_;

  
  HostZoomLevels host_zoom_levels_;
  SchemeHostZoomLevels scheme_host_zoom_levels_;
  double default_zoom_level_;

  
  
  TemporaryZoomLevels temporary_zoom_levels_;

  
  
  mutable base::Lock lock_;

  NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(HostZoomMapImpl);
};

}  

#endif  
