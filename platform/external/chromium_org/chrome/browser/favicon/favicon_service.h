// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FAVICON_FAVICON_SERVICE_H_
#define CHROME_BROWSER_FAVICON_FAVICON_SERVICE_H_

#include <vector>

#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/favicon_base/favicon_callback.h"
#include "components/favicon_base/favicon_types.h"
#include "components/keyed_service/core/keyed_service.h"

class FaviconClient;
class GURL;
class HistoryService;
struct ImportedFaviconUsage;
class Profile;

class FaviconService : public KeyedService {
 public:
  
  
  FaviconService(Profile* profile, FaviconClient* favicon_client);

  virtual ~FaviconService();

  
  
  static void FaviconResultsCallbackRunner(
      const favicon_base::FaviconResultsCallback& callback,
      const std::vector<favicon_base::FaviconRawBitmapResult>* results);

  
  
  
  

  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetFaviconImage(
      const GURL& icon_url,
      const favicon_base::FaviconImageCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetRawFavicon(
      const GURL& icon_url,
      favicon_base::IconType icon_type,
      int desired_size_in_pixel,
      const favicon_base::FaviconRawBitmapCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetFavicon(
      const GURL& icon_url,
      favicon_base::IconType icon_type,
      int desired_size_in_dip,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  

  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetFaviconImageForPageURL(
      const GURL& page_url,
      const favicon_base::FaviconImageCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId GetRawFaviconForPageURL(
      const GURL& page_url,
      int icon_types,
      int desired_size_in_pixel,
      const favicon_base::FaviconRawBitmapCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  base::CancelableTaskTracker::TaskId GetLargestRawFaviconForPageURL(
      const GURL& page_url,
      const std::vector<int>& icon_types,
      int minimum_size_in_pixels,
      const favicon_base::FaviconRawBitmapCallback& callback,
      base::CancelableTaskTracker* tracker);

  base::CancelableTaskTracker::TaskId GetFaviconForPageURL(
      const GURL& page_url,
      int icon_types,
      int desired_size_in_dip,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  base::CancelableTaskTracker::TaskId UpdateFaviconMappingsAndFetch(
      const GURL& page_url,
      const std::vector<GURL>& icon_urls,
      int icon_types,
      int desired_size_in_dip,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  base::CancelableTaskTracker::TaskId GetLargestRawFaviconForID(
      favicon_base::FaviconID favicon_id,
      const favicon_base::FaviconRawBitmapCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  void SetFaviconOutOfDateForPage(const GURL& page_url);

  
  
  
  
  
  void CloneFavicon(const GURL& old_page_url, const GURL& new_page_url);

  
  
  // favicons will not be overwritten.
  void SetImportedFavicons(
      const std::vector<ImportedFaviconUsage>& favicon_usage);

  
  
  
  
  
  void MergeFavicon(const GURL& page_url,
                    const GURL& icon_url,
                    favicon_base::IconType icon_type,
                    scoped_refptr<base::RefCountedMemory> bitmap_data,
                    const gfx::Size& pixel_size);

  
  
  
  
  
  
  
  
  
  
  void SetFavicons(const GURL& page_url,
                   const GURL& icon_url,
                   favicon_base::IconType icon_type,
                   const gfx::Image& image);

  
  void UnableToDownloadFavicon(const GURL& icon_url);
  bool WasUnableToDownloadFavicon(const GURL& icon_url) const;
  void ClearUnableToDownloadFavicons();

 private:
  typedef uint32 MissingFaviconURLHash;
  base::hash_set<MissingFaviconURLHash> missing_favicon_urls_;
  HistoryService* history_service_;
  Profile* profile_;
  FaviconClient* favicon_client_;

  
  
  base::CancelableTaskTracker::TaskId GetFaviconForPageURLImpl(
      const GURL& page_url,
      int icon_types,
      const std::vector<int>& desired_sizes_in_pixel,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  
  
  
  
  void RunFaviconImageCallbackWithBitmapResults(
      const favicon_base::FaviconImageCallback& callback,
      int desired_size_in_dip,
      const std::vector<favicon_base::FaviconRawBitmapResult>&
          favicon_bitmap_results);

  
  
  
  
  void RunFaviconRawBitmapCallbackWithBitmapResults(
      const favicon_base::FaviconRawBitmapCallback& callback,
      int desired_size_in_pixel,
      const std::vector<favicon_base::FaviconRawBitmapResult>&
          favicon_bitmap_results);

  DISALLOW_COPY_AND_ASSIGN(FaviconService);
};

#endif  
