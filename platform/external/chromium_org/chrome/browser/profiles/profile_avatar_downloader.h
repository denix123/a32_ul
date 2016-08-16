// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef CHROME_BROWSER_PROFILES_PROFILE_AVATAR_DOWNLOADER_H_
#define CHROME_BROWSER_PROFILES_PROFILE_AVATAR_DOWNLOADER_H_

#include "base/files/file_path.h"
#include "chrome/browser/bitmap_fetcher/bitmap_fetcher.h"

class ProfileInfoCache;

class ProfileAvatarDownloader : public chrome::BitmapFetcherDelegate {
 public:
  ProfileAvatarDownloader(size_t icon_index,
                          const base::FilePath& profile_path,
                          ProfileInfoCache* cache);
  virtual ~ProfileAvatarDownloader();

  void Start();

  
  virtual void OnFetchComplete(const GURL url, const SkBitmap* bitmap) OVERRIDE;

 private:
  
  scoped_ptr<chrome::BitmapFetcher> fetcher_;

  
  size_t icon_index_;

  
  base::FilePath profile_path_;

  ProfileInfoCache* cache_;  
};

#endif  
