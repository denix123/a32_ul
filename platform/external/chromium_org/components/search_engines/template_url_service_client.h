// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_CLIENT_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_SERVICE_CLIENT_H_

#include "base/strings/string16.h"
#include "components/search_engines/template_url_id.h"

class GURL;
class TemplateURL;
class TemplateURLService;

class TemplateURLServiceClient {
 public:
  virtual ~TemplateURLServiceClient() {}

  
  virtual void SetOwner(TemplateURLService* owner) = 0;

  
  virtual void DeleteAllSearchTermsForKeyword(TemplateURLID id) = 0;

  
  virtual void SetKeywordSearchTermsForURL(const GURL& url,
                                           TemplateURLID id,
                                           const base::string16& term) = 0;

  
  virtual void AddKeywordGeneratedVisit(const GURL& url) = 0;

  
  virtual void RestoreExtensionInfoIfNecessary(TemplateURL* template_url) = 0;
};

#endif  
