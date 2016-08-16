// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PRECACHE_CONTENT_PRECACHE_MANAGER_H_
#define COMPONENTS_PRECACHE_CONTENT_PRECACHE_MANAGER_H_

#include <list>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/precache/core/precache_fetcher.h"
#include "url/gurl.h"

namespace base {
class Time;
}

namespace content {
class BrowserContext;
}

namespace precache {

class PrecacheDatabase;
class URLListProvider;

class PrecacheManager : public KeyedService,
                        public PrecacheFetcher::PrecacheDelegate,
                        public base::SupportsWeakPtr<PrecacheManager> {
 public:
  typedef base::Closure PrecacheCompletionCallback;

  explicit PrecacheManager(content::BrowserContext* browser_context);
  virtual ~PrecacheManager();

  
  
  static bool IsPrecachingEnabled();

  
  bool IsPrecachingAllowed();

  
  
  
  
  void StartPrecaching(
      const PrecacheCompletionCallback& precache_completion_callback,
      URLListProvider* url_list_provider);

  
  void CancelPrecaching();

  
  bool IsPrecaching() const;

  
  void RecordStatsForFetch(const GURL& url,
                           const base::Time& fetch_time,
                           int64 size,
                           bool was_cached);

 private:
  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnDone() OVERRIDE;

  void OnURLsReceived(const std::list<GURL>& urls);

  
  content::BrowserContext* browser_context_;

  
  
  scoped_ptr<PrecacheFetcher> precache_fetcher_;

  
  
  PrecacheCompletionCallback precache_completion_callback_;

  
  
  scoped_refptr<PrecacheDatabase> precache_database_;

  
  bool is_precaching_;

  DISALLOW_COPY_AND_ASSIGN(PrecacheManager);
};

}  

#endif  
