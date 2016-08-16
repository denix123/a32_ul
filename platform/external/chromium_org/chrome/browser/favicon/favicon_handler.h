// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_FAVICON_FAVICON_HANDLER_H_
#define CHROME_BROWSER_FAVICON_FAVICON_HANDLER_H_

#include <deque>
#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/task/cancelable_task_tracker.h"
#include "components/favicon/core/favicon_url.h"
#include "components/favicon_base/favicon_callback.h"
#include "ui/gfx/favicon_size.h"
#include "ui/gfx/image/image.h"
#include "url/gurl.h"

class FaviconClient;
class FaviconDriver;
class SkBitmap;

namespace base {
class RefCountedMemory;
}


class FaviconHandler {
 public:
  enum Type {
    FAVICON,
    TOUCH,
  };

  FaviconHandler(FaviconClient* client,
                 FaviconDriver* driver,
                 Type icon_type,
                 bool download_largest_icon);
  virtual ~FaviconHandler();

  
  void FetchFavicon(const GURL& url);

  
  
  void OnUpdateFaviconURL(const std::vector<favicon::FaviconURL>& candidates);

  
  
  void ProcessCurrentUrl();

  
  
  
  
  
  void OnDidDownloadFavicon(
      int id,
      const GURL& image_url,
      const std::vector<SkBitmap>& bitmaps,
      const std::vector<gfx::Size>& original_bitmap_sizes);

  
  const std::vector<favicon::FaviconURL>& image_urls() const {
    return image_urls_;
  }

 protected:
  
  

  
  virtual int DownloadFavicon(const GURL& image_url, int max_bitmap_size);

  
  virtual void UpdateFaviconMappingAndFetch(
      const GURL& page_url,
      const GURL& icon_url,
      favicon_base::IconType icon_type,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  virtual void GetFaviconFromFaviconService(
      const GURL& icon_url,
      favicon_base::IconType icon_type,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  virtual void GetFaviconForURLFromFaviconService(
      const GURL& page_url,
      int icon_types,
      const favicon_base::FaviconResultsCallback& callback,
      base::CancelableTaskTracker* tracker);

  virtual void SetHistoryFavicons(const GURL& page_url,
                                  const GURL& icon_url,
                                  favicon_base::IconType icon_type,
                                  const gfx::Image& image);

  
  virtual bool ShouldSaveFavicon(const GURL& url);

  
  
  
  virtual void NotifyFaviconUpdated(bool icon_url_changed);

 private:
  friend class TestFaviconHandler; 

  
  struct DownloadRequest {
    DownloadRequest();
    ~DownloadRequest();

    DownloadRequest(const GURL& url,
                    const GURL& image_url,
                    favicon_base::IconType icon_type);

    GURL url;
    GURL image_url;
    favicon_base::IconType icon_type;
  };

  
  struct FaviconCandidate {
    FaviconCandidate();
    ~FaviconCandidate();

    FaviconCandidate(const GURL& url,
                     const GURL& image_url,
                     const gfx::Image& image,
                     float score,
                     favicon_base::IconType icon_type);

    GURL url;
    GURL image_url;
    gfx::Image image;
    float score;
    favicon_base::IconType icon_type;
  };

  
  void OnFaviconDataForInitialURLFromFaviconService(const std::vector<
      favicon_base::FaviconRawBitmapResult>& favicon_bitmap_results);

  
  
  
  void DownloadFaviconOrAskFaviconService(const GURL& page_url,
                                          const GURL& icon_url,
                                          favicon_base::IconType icon_type);

  
  void OnFaviconData(const std::vector<favicon_base::FaviconRawBitmapResult>&
                         favicon_bitmap_results);

  
  
  int ScheduleDownload(const GURL& url,
                       const GURL& image_url,
                       favicon_base::IconType icon_type);

  
  bool UpdateFaviconCandidate(const GURL& url,
                              const GURL& image_url,
                              const gfx::Image& image,
                              float score,
                              favicon_base::IconType icon_type);

  
  void SetFavicon(const GURL& url,
                  const GURL& icon_url,
                  const gfx::Image& image,
                  favicon_base::IconType icon_type);

  
  void SetFaviconOnActivePage(const std::vector<
      favicon_base::FaviconRawBitmapResult>& favicon_bitmap_results);
  void SetFaviconOnActivePage(const GURL& icon_url, const gfx::Image& image);

  
  favicon::FaviconURL* current_candidate() {
    return (!image_urls_.empty()) ? &image_urls_.front() : NULL;
  }

  
  bool PageChangedSinceFaviconWasRequested();

  
  
  int preferred_icon_size() const {
    if (download_largest_icon_)
      return 0;
    return icon_types_ == favicon_base::FAVICON ? gfx::kFaviconSize : 0;
  }

  
  
  
  void SortAndPruneImageUrls();

  
  base::CancelableTaskTracker cancelable_task_tracker_;

  
  GURL url_;

  
  bool got_favicon_from_history_;

  
  
  
  
  bool favicon_expired_or_incomplete_;

  
  typedef std::map<int, DownloadRequest> DownloadRequests;
  DownloadRequests download_requests_;

  
  const int icon_types_;

  
  const bool download_largest_icon_;

  
  std::vector<favicon::FaviconURL> image_urls_;

  
  std::vector<favicon_base::FaviconRawBitmapResult> history_results_;

  
  FaviconClient* client_;  

  
  FaviconDriver* driver_;  

  
  
  
  
  FaviconCandidate best_favicon_candidate_;

  DISALLOW_COPY_AND_ASSIGN(FaviconHandler);
};

#endif  
