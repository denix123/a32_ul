// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_FETCHER_H_
#define COMPONENTS_SEARCH_ENGINES_TEMPLATE_URL_FETCHER_H_

#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/strings/string16.h"
#include "components/keyed_service/core/keyed_service.h"

class GURL;
class TemplateURL;
class TemplateURLService;

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}

class TemplateURLFetcher : public KeyedService {
 public:
  typedef base::Callback<void(
      net::URLFetcher* url_fetcher)> URLFetcherCustomizeCallback;
  typedef base::Callback<void(
      scoped_ptr<TemplateURL> template_url)> ConfirmAddSearchProviderCallback;

  enum ProviderType {
    AUTODETECTED_PROVIDER,
    EXPLICIT_PROVIDER  
  };

  
  TemplateURLFetcher(TemplateURLService* template_url_service,
                     net::URLRequestContextGetter* request_context);
  virtual ~TemplateURLFetcher();

  
  
  
  
  
  
  
  
  
  
  
  
  
  void ScheduleDownload(
      const base::string16& keyword,
      const GURL& osdd_url,
      const GURL& favicon_url,
      const URLFetcherCustomizeCallback& url_fetcher_customize_callback,
      const ConfirmAddSearchProviderCallback& confirm_add_callback,
      ProviderType provider_type);

  
  int requests_count() const { return requests_.size(); }

 private:
  
  
  class RequestDelegate;
  friend class RequestDelegate;

  typedef ScopedVector<RequestDelegate> Requests;

  
  void RequestCompleted(RequestDelegate* request);

  TemplateURLService* template_url_service_;
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  
  Requests requests_;

  DISALLOW_COPY_AND_ASSIGN(TemplateURLFetcher);
};

#endif  
