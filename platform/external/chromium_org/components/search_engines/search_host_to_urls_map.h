// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_SEARCH_HOST_TO_URLS_MAP_H_
#define COMPONENTS_SEARCH_ENGINES_SEARCH_HOST_TO_URLS_MAP_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "components/search_engines/template_url_service.h"

class SearchHostToURLsMap {
 public:
  typedef std::set<TemplateURL*> TemplateURLSet;

  SearchHostToURLsMap();
  ~SearchHostToURLsMap();

  
  void Init(const TemplateURLService::TemplateURLVector& template_urls,
            const SearchTermsData& search_terms_data);

  
  
  void Add(TemplateURL* template_url,
           const SearchTermsData& search_terms_data);

  
  void Remove(TemplateURL* template_url);

  
  
  TemplateURL* GetTemplateURLForHost(const std::string& host);

  
  
  TemplateURLSet* GetURLsForHost(const std::string& host);

 private:
  friend class SearchHostToURLsMapTest;

  typedef std::map<std::string, TemplateURLSet> HostToURLsMap;

  
  void Add(const TemplateURLService::TemplateURLVector& template_urls,
           const SearchTermsData& search_terms_data);

  
  HostToURLsMap host_to_urls_map_;

  
  std::string default_search_origin_;

  
  bool initialized_;

  DISALLOW_COPY_AND_ASSIGN(SearchHostToURLsMap);
};

#endif  
