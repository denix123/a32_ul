// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_CUSTOMIZATION_WALLPAPER_DOWNLOADER_H_
#define CHROME_BROWSER_CHROMEOS_CUSTOMIZATION_WALLPAPER_DOWNLOADER_H_

#include <string>

#include "base/bind.h"
#include "base/files/file_path.h"
#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}  

namespace chromeos {

class CustomizationWallpaperDownloader : public net::URLFetcherDelegate {
 public:
  
  
  
  
  
  
  
  
  
  CustomizationWallpaperDownloader(
      net::URLRequestContextGetter* url_context_getter,
      const GURL& wallpaper_url,
      const base::FilePath& wallpaper_dir,
      const base::FilePath& wallpaper_downloaded_file,
      base::Callback<void(bool success, const GURL&)>
          on_wallpaper_fetch_completed);

  virtual ~CustomizationWallpaperDownloader();

  
  void Start();

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

  
  void set_retry_delay_for_testing(base::TimeDelta value) {
    retry_delay_ = value;
  }

  base::TimeDelta retry_current_delay_for_testing() const {
    return retry_current_delay_;
  }

 private:
  
  void StartRequest();

  
  void Retry();

  
  void OnWallpaperDirectoryCreated(scoped_ptr<bool> success);

  
  void OnTemporaryFileRenamed(scoped_ptr<bool> success);

  
  scoped_refptr<net::URLRequestContextGetter> url_context_getter_;

  
  scoped_ptr<net::URLFetcher> url_fetcher_;

  
  const GURL wallpaper_url_;

  
  const base::FilePath wallpaper_dir_;

  
  const base::FilePath wallpaper_downloaded_file_;

  
  const base::FilePath wallpaper_temporary_file_;

  
  base::OneShotTimer<CustomizationWallpaperDownloader> request_scheduled_;

  
  size_t retries_;

  
  
  base::TimeDelta retry_delay_;

  
  base::TimeDelta retry_current_delay_;

  
  base::Callback<void(bool success, const GURL&)> on_wallpaper_fetch_completed_;

  base::WeakPtrFactory<CustomizationWallpaperDownloader> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CustomizationWallpaperDownloader);
};

}  

#endif  
