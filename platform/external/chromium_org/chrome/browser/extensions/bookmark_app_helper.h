// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_BOOKMARK_APP_HELPER_H_
#define CHROME_BROWSER_EXTENSIONS_BOOKMARK_APP_HELPER_H_

#include <map>
#include <set>
#include <vector>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/common/web_application_info.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class ExtensionService;
class FaviconDownloader;
class SkBitmap;

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {
class CrxInstaller;
class Extension;

class BookmarkAppHelper : public content::NotificationObserver {
 public:
  typedef base::Callback<void(const Extension*, const WebApplicationInfo&)>
      CreateBookmarkAppCallback;

  
  
  
  
  BookmarkAppHelper(ExtensionService* service,
                    WebApplicationInfo web_app_info,
                    content::WebContents* contents);
  virtual ~BookmarkAppHelper();

  
  
  
  
  static std::map<int, SkBitmap> ConstrainBitmapsToSizes(
      const std::vector<SkBitmap>& bitmaps,
      const std::set<int>& sizes);

  
  
  
  static void GenerateIcon(std::map<int, SkBitmap>* bitmaps,
                           int output_size,
                           SkColor color,
                           char letter);

  
  void Create(const CreateBookmarkAppCallback& callback);

 private:
  friend class TestBookmarkAppHelper;

  
  void OnIconsDownloaded(bool success,
                         const std::map<GURL, std::vector<SkBitmap> >& bitmaps);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  WebApplicationInfo web_app_info_;

  
  CreateBookmarkAppCallback callback_;

  
  
  scoped_ptr<FaviconDownloader> favicon_downloader_;

  
  scoped_refptr<extensions::CrxInstaller> crx_installer_;

  content::NotificationRegistrar registrar_;
};

void CreateOrUpdateBookmarkApp(ExtensionService* service,
                               WebApplicationInfo& web_app_info);

void GetWebApplicationInfoFromApp(
    content::BrowserContext* browser_context,
    const extensions::Extension* extension,
    const base::Callback<void(const WebApplicationInfo&)> callback);

bool IsValidBookmarkAppUrl(const GURL& url);

}  

#endif  
