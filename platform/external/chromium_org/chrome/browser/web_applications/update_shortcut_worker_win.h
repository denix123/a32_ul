// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_WEB_APPLICATIONS_UPDATE_SHORTCUT_WORKER_WIN_H_
#define CHROME_BROWSER_WEB_APPLICATIONS_UPDATE_SHORTCUT_WORKER_WIN_H_

#include "chrome/browser/shell_integration.h"
#include "chrome/browser/web_applications/web_app.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace content {
class NotificationDetails;
class NotificationSource;
class WebContents;
}

namespace web_app {

class UpdateShortcutWorker : public content::NotificationObserver {
 public:
  explicit UpdateShortcutWorker(content::WebContents* web_contents);

  void Run();

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details);

  
  void DownloadIcon();

  
  void DidDownloadFavicon(
      int requested_size,
      int id,
      int http_status_code,
      const GURL& image_url,
      const std::vector<SkBitmap>& bitmaps,
      const std::vector<gfx::Size>& original_bitmap_sizes);

  
  void CheckExistingShortcuts();

  
  void UpdateShortcuts();
  void UpdateShortcutsOnFileThread();

  
  void OnShortcutsUpdated(bool);

  
  void DeleteMe();
  void DeleteMeOnUIThread();

  content::NotificationRegistrar registrar_;

  
  content::WebContents* web_contents_;

  
  web_app::IconInfoList unprocessed_icons_;

  
  web_app::ShortcutInfo shortcut_info_;

  
  base::FilePath profile_path_;

  
  base::FilePath file_name_;

  
  std::vector<base::FilePath> shortcut_files_;

  DISALLOW_COPY_AND_ASSIGN(UpdateShortcutWorker);
};

}  

#endif  
