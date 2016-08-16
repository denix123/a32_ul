// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SEARCH_ENGINES_SEARCH_PROVIDER_INSTALL_DATA_H_
#define CHROME_BROWSER_SEARCH_ENGINES_SEARCH_PROVIDER_INSTALL_DATA_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"

class GURL;
class GoogleURLTracker;
class SearchHostToURLsMap;
class TemplateURL;
class TemplateURLService;

namespace content {
class RenderProcessHost;
}

class SearchProviderInstallData {
 public:
  enum State {
    
    NOT_INSTALLED = 0,

    
    INSTALLED_BUT_NOT_DEFAULT = 1,

    
    INSTALLED_AS_DEFAULT = 2
  };

  
  
  
  
  SearchProviderInstallData(TemplateURLService* template_url_service,
                            const std::string& google_base_url,
                            GoogleURLTracker* google_url_tracker,
                            content::RenderProcessHost* host);
  virtual ~SearchProviderInstallData();

  
  
  
  
  void CallWhenLoaded(const base::Closure& closure);

  
  
  State GetInstallState(const GURL& requested_origin);

  
  void OnGoogleURLChange(const std::string& google_base_url);

 private:
  
  void OnTemplateURLsLoaded(ScopedVector<TemplateURL> template_urls,
                            TemplateURL* default_provider);

  
  void SetDefault(const TemplateURL* template_url);

  
  
  void OnLoadFailed();

  
  
  void NotifyLoaded();

  
  TemplateURLService* template_url_service_;

  
  
  std::vector<base::Closure> closure_queue_;

  
  scoped_ptr<SearchHostToURLsMap> provider_map_;

  
  ScopedVector<TemplateURL> template_urls_;

  
  std::string default_search_origin_;

  
  std::string google_base_url_;

  base::WeakPtrFactory<SearchProviderInstallData> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SearchProviderInstallData);
};

#endif  
