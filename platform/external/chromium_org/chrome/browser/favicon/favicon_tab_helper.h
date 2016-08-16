// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FAVICON_FAVICON_TAB_HELPER_H_
#define CHROME_BROWSER_FAVICON_FAVICON_TAB_HELPER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "components/favicon/core/browser/favicon_client.h"
#include "components/favicon/core/favicon_driver.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/browser/web_contents_user_data.h"
#include "content/public/common/favicon_url.h"

namespace gfx {
class Image;
}

namespace content {
struct FaviconStatus;
}

class GURL;
class FaviconHandler;
class Profile;
class SkBitmap;

class FaviconTabHelper : public content::WebContentsObserver,
                         public FaviconDriver,
                         public content::WebContentsUserData<FaviconTabHelper> {
 public:
  virtual ~FaviconTabHelper();

  
  void FetchFavicon(const GURL& url);

  
  
  
  
  gfx::Image GetFavicon() const;

  
  bool FaviconIsValid() const;

  
  
  virtual bool ShouldDisplayFavicon();

  
  
  const std::vector<content::FaviconURL>& favicon_urls() const {
    return favicon_urls_;
  }

  
  
  virtual void DidUpdateFaviconURL(
      const std::vector<content::FaviconURL>& candidates) OVERRIDE;

  
  void SaveFavicon();

  
  virtual int StartDownload(const GURL& url, int max_bitmap_size) OVERRIDE;
  virtual void NotifyFaviconUpdated(bool icon_url_changed) OVERRIDE;
  virtual bool IsOffTheRecord() OVERRIDE;
  virtual const gfx::Image GetActiveFaviconImage() OVERRIDE;
  virtual const GURL GetActiveFaviconURL() OVERRIDE;
  virtual bool GetActiveFaviconValidity() OVERRIDE;
  virtual const GURL GetActiveURL() OVERRIDE;
  virtual void SetActiveFaviconImage(gfx::Image image) OVERRIDE;
  virtual void SetActiveFaviconURL(GURL url) OVERRIDE;
  virtual void SetActiveFaviconValidity(bool validity) OVERRIDE;

  
  void DidDownloadFavicon(
      int id,
      int http_status_code,
      const GURL& image_url,
      const std::vector<SkBitmap>& bitmaps,
      const std::vector<gfx::Size>& original_bitmap_sizes);

 private:
  explicit FaviconTabHelper(content::WebContents* web_contents);
  friend class content::WebContentsUserData<FaviconTabHelper>;

  
  virtual void DidStartNavigationToPendingEntry(
      const GURL& url,
      content::NavigationController::ReloadType reload_type) OVERRIDE;
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;

  
  content::FaviconStatus& GetFaviconStatus();

  Profile* profile_;

  FaviconClient* client_;

  std::vector<content::FaviconURL> favicon_urls_;

  scoped_ptr<FaviconHandler> favicon_handler_;

  
  
  scoped_ptr<FaviconHandler> touch_icon_handler_;

  DISALLOW_COPY_AND_ASSIGN(FaviconTabHelper);
};

#endif  
