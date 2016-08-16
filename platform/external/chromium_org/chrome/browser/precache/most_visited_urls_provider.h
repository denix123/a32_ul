// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRECACHE_MOST_VISITED_URLS_PROVIDER_H_
#define CHROME_BROWSER_PRECACHE_MOST_VISITED_URLS_PROVIDER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "components/precache/core/url_list_provider.h"

namespace history {
class TopSites;
}

namespace precache {

class MostVisitedURLsProvider : public URLListProvider {
 public:
  explicit MostVisitedURLsProvider(history::TopSites* top_sites);
  ~MostVisitedURLsProvider();

  
  
  
  virtual void GetURLs(const GetURLsCallback& callback) OVERRIDE;

 private:
  scoped_refptr<history::TopSites> top_sites_;

  DISALLOW_COPY_AND_ASSIGN(MostVisitedURLsProvider);
};

}  

#endif  
