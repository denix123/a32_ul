// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_DATA_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_DATA_H_

#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "base/time/time.h"
#include "components/search_engines/template_url_id.h"
#include "url/gurl.h"

struct TemplateURLData {
  TemplateURLData();
  ~TemplateURLData();

  
  
  
  base::string16 short_name;

  
  void SetKeyword(const base::string16& keyword);
  const base::string16& keyword() const { return keyword_; }

  
  
  void SetURL(const std::string& url);
  const std::string& url() const { return url_; }

  
  std::string suggestions_url;
  std::string instant_url;
  std::string image_url;
  std::string new_tab_url;
  std::string contextual_search_url;

  
  
  std::string search_url_post_params;
  std::string suggestions_url_post_params;
  std::string instant_url_post_params;
  std::string image_url_post_params;

  
  GURL favicon_url;

  
  GURL originating_url;

  
  
  
  
  bool show_in_default_list;

  
  
  
  
  
  bool safe_for_autoreplace;

  
  
  std::vector<std::string> input_encodings;

  
  
  TemplateURLID id;

  
  
  
  
  base::Time date_created;

  
  
  
  base::Time last_modified;

  
  
  bool created_by_policy;

  
  
  
  
  
  int usage_count;

  
  int prepopulate_id;

  
  
  std::string sync_guid;

  
  
  std::vector<std::string> alternate_urls;

  
  
  std::string search_terms_replacement_key;

 private:
  
  
  base::string16 keyword_;
  std::string url_;
};

#endif  
