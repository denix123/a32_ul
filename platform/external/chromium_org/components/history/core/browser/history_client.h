// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_CLIENT_H_
#define COMPONENTS_HISTORY_CORE_BROWSER_HISTORY_CLIENT_H_

#include <vector>

#include "base/macros.h"
#include "base/strings/string16.h"
#include "components/keyed_service/core/keyed_service.h"
#include "sql/init_status.h"
#include "url/gurl.h"

namespace history {

struct URLAndTitle {
  GURL url;
  base::string16 title;
};

class HistoryClient : public KeyedService {
 public:
  HistoryClient();

  
  
  
  virtual void BlockUntilBookmarksLoaded();

  
  
  
  virtual bool IsBookmarked(const GURL& url);

  
  
  
  
  
  
  virtual void GetBookmarks(std::vector<URLAndTitle>* bookmarks);

  
  
  
  virtual void NotifyProfileError(sql::InitStatus init_status);

  
  virtual bool ShouldReportDatabaseError();

 protected:
  DISALLOW_COPY_AND_ASSIGN(HistoryClient);
};

}  

#endif  
