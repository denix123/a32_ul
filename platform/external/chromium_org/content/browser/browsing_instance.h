// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_BROWSING_INSTANCE_H_
#define CONTENT_BROWSER_BROWSING_INSTANCE_H_

#include "base/containers/hash_tables.h"
#include "base/lazy_instance.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "content/common/content_export.h"
#include "content/public/browser/browser_context.h"

class GURL;

namespace content {
class SiteInstance;
class SiteInstanceImpl;

class CONTENT_EXPORT BrowsingInstance
    : public base::RefCounted<BrowsingInstance> {
 protected:
  
  explicit BrowsingInstance(BrowserContext* context);

  
  BrowserContext* browser_context() const { return browser_context_; }

  
  
  bool HasSiteInstance(const GURL& url);

  
  
  
  SiteInstance* GetSiteInstanceForURL(const GURL& url);

  
  
  void RegisterSiteInstance(SiteInstance* site_instance);

  
  
  
  
  void UnregisterSiteInstance(SiteInstance* site_instance);

  
  size_t active_contents_count() const { return active_contents_count_; }
  void increment_active_contents_count() { active_contents_count_++; }
  void decrement_active_contents_count() {
    DCHECK_LT(0u, active_contents_count_);
    active_contents_count_--;
  }

  friend class SiteInstanceImpl;
  friend class SiteInstance;

  friend class base::RefCounted<BrowsingInstance>;

  
  virtual ~BrowsingInstance();

 private:
  
  
  typedef base::hash_map<std::string, SiteInstance*> SiteInstanceMap;

  
  
  BrowserContext* const browser_context_;

  
  
  
  
  
  
  
  SiteInstanceMap site_instance_map_;

  
  size_t active_contents_count_;

  DISALLOW_COPY_AND_ASSIGN(BrowsingInstance);
};

}  

#endif  
