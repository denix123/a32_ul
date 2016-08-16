// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_CHROME_HISTORY_CLIENT_H_
#define CHROME_BROWSER_HISTORY_CHROME_HISTORY_CLIENT_H_

#include "base/macros.h"
#include "components/history/core/browser/history_client.h"
#include "components/history/core/browser/top_sites_observer.h"

class BookmarkModel;
class Profile;

namespace history {
class TopSites;
}

class ChromeHistoryClient : public history::HistoryClient,
                            public history::TopSitesObserver {
 public:
  explicit ChromeHistoryClient(BookmarkModel* bookmark_model,
                               Profile* profile,
                               history::TopSites* top_sites);
  virtual ~ChromeHistoryClient();

  
  virtual void BlockUntilBookmarksLoaded() OVERRIDE;
  virtual bool IsBookmarked(const GURL& url) OVERRIDE;
  virtual void GetBookmarks(
      std::vector<history::URLAndTitle>* bookmarks) OVERRIDE;
  virtual void NotifyProfileError(sql::InitStatus init_status) OVERRIDE;
  virtual bool ShouldReportDatabaseError() OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void TopSitesLoaded(history::TopSites* top_sites) OVERRIDE;
  virtual void TopSitesChanged(history::TopSites* top_sites) OVERRIDE;

 private:
  
  BookmarkModel* bookmark_model_;
  Profile* profile_;
  
  
  
  
  
  
  
  
  
  
  history::TopSites* top_sites_;

  DISALLOW_COPY_AND_ASSIGN(ChromeHistoryClient);
};

#endif  
