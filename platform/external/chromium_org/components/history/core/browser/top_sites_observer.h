// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_HISTORY_CORE_BROWSER_TOP_SITES_OBSERVER_H_
#define COMPONENTS_HISTORY_CORE_BROWSER_TOP_SITES_OBSERVER_H_

namespace history {
class TopSites;

class TopSitesObserver {
 public:
  
  virtual void TopSitesLoaded(history::TopSites* top_sites) = 0;

  
  
  virtual void TopSitesChanged(history::TopSites* top_sites) = 0;
};

}  

#endif  
