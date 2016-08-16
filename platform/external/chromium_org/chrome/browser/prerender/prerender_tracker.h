// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRERENDER_PRERENDER_TRACKER_H_
#define CHROME_BROWSER_PRERENDER_PRERENDER_TRACKER_H_

#include <map>
#include <set>
#include <utility>

#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "chrome/browser/prerender/prerender_cookie_store.h"
#include "content/public/browser/render_process_host_observer.h"
#include "url/gurl.h"

namespace net {
class URLRequestContextGetter;
}

namespace prerender {

class PrerenderPendingSwapThrottle;

class PrerenderTracker {
 public:
  typedef std::pair<int, int> ChildRouteIdPair;

  PrerenderTracker();
  virtual ~PrerenderTracker();

  
  
  bool IsPendingSwapRequestOnIOThread(int render_process_id,
                                      int render_frame_id,
                                      const GURL& url) const;

  
  
  
  void AddPendingSwapThrottleOnIOThread(
      int render_process_id, int render_frame_id, const GURL& url,
      const base::WeakPtr<PrerenderPendingSwapThrottle>& throttle);

  
  void AddPrerenderPendingSwap(
      const ChildRouteIdPair& render_frame_route_id_pair,
      const GURL& url);

  
  void RemovePrerenderPendingSwap(
      const ChildRouteIdPair& render_frame_route_id_pair,
      bool swap_successful);

  
  
  scoped_refptr<PrerenderCookieStore> GetPrerenderCookieStoreForRenderProcess(
      int process_id);

  
  
  
  void OnCookieChangedForURL(int process_id,
                             net::CookieMonster* cookie_monster,
                             const GURL& url);

  void AddPrerenderCookieStoreOnIOThread(
      int process_id,
      scoped_refptr<net::URLRequestContextGetter> request_context,
      const base::Closure& cookie_conflict_cb);

  void RemovePrerenderCookieStoreOnIOThread(int process_id, bool was_swapped);

 private:
  
  void AddPrerenderPendingSwapOnIOThread(
      const ChildRouteIdPair& render_frame_route_id_pair, const GURL& url);
  void RemovePrerenderPendingSwapOnIOThread(
      const ChildRouteIdPair& render_frame_route_id_pair,
      bool swap_successful);

  struct PendingSwapThrottleData {
    explicit PendingSwapThrottleData(const GURL& swap_url);
    ~PendingSwapThrottleData();
    GURL url;
    base::WeakPtr<PrerenderPendingSwapThrottle> throttle;
  };

  
  
  
  typedef std::map<ChildRouteIdPair, PendingSwapThrottleData>
      PendingSwapThrottleMap;
  PendingSwapThrottleMap pending_swap_throttle_map_;

  
  
  typedef base::hash_map<int, scoped_refptr<PrerenderCookieStore> >
      PrerenderCookieStoreMap;
  PrerenderCookieStoreMap prerender_cookie_store_map_;

  DISALLOW_COPY_AND_ASSIGN(PrerenderTracker);
};

}  

#endif  
