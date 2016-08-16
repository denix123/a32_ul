// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_FAVICON_DOWNLOADER_H_
#define CHROME_BROWSER_EXTENSIONS_FAVICON_DOWNLOADER_H_

#include <map>
#include <set>
#include <vector>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "content/public/browser/web_contents_observer.h"

class SkBitmap;

namespace content {
struct FaviconURL;
}

namespace gfx {
class Size;
}

class FaviconDownloader : public content::WebContentsObserver {
 public:
  typedef std::map<GURL, std::vector<SkBitmap> > FaviconMap;
  typedef base::Callback<void(
          bool,  
          
          const FaviconMap&)>
      FaviconDownloaderCallback;
  
  
  FaviconDownloader(content::WebContents* web_contents,
                    const std::vector<GURL>& extra_favicon_urls,
                    FaviconDownloaderCallback callback);
  virtual ~FaviconDownloader();

  void Start();

 private:
  friend class TestFaviconDownloader;

  
  
  virtual int DownloadImage(const GURL& url);

  
  
  virtual std::vector<content::FaviconURL> GetFaviconURLsFromWebContents();

  
  
  void FetchIcons(const std::vector<content::FaviconURL>& favicon_urls);
  void FetchIcons(const std::vector<GURL>& urls);

  
  void DidDownloadFavicon(int id,
                          int http_status_code,
                          const GURL& image_url,
                          const std::vector<SkBitmap>& bitmaps,
                          const std::vector<gfx::Size>& original_bitmap_sizes);

  
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;
  virtual void DidUpdateFaviconURL(
      const std::vector<content::FaviconURL>& candidates) OVERRIDE;

  
  bool got_favicon_urls_;

  
  
  
  std::vector<GURL> extra_favicon_urls_;

  
  FaviconMap favicon_map_;

  
  std::set<int> in_progress_requests_;

  
  
  std::set<GURL> processed_urls_;

  
  FaviconDownloaderCallback callback_;

  base::WeakPtrFactory<FaviconDownloader> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(FaviconDownloader);
};

#endif  
