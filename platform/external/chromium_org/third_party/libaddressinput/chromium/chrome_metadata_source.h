// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_CHROME_METADATA_SOURCE_H_
#define THIRD_PARTY_LIBADDRESSINPUT_CHROMIUM_CHROME_METADATA_SOURCE_H_

#include <map>
#include <string>

#include "base/memory/scoped_vector.h"
#include "net/url_request/url_fetcher_delegate.h"
#include "third_party/libaddressinput/src/cpp/include/libaddressinput/source.h"

namespace net {
class URLFetcher;
class URLRequestContextGetter;
}

namespace autofill {

class ChromeMetadataSource : public ::i18n::addressinput::Source,
                             public net::URLFetcherDelegate {
 public:
  ChromeMetadataSource(const std::string& validation_data_url,
                       net::URLRequestContextGetter* getter);
  virtual ~ChromeMetadataSource();

  
  virtual void Get(const std::string& key,
                   const Callback& downloaded) const OVERRIDE;

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

 private:
  struct Request {
    Request(const std::string& key,
            scoped_ptr<net::URLFetcher> fetcher,
            const Callback& callback);

    std::string key;
    
    std::string data;
    
    scoped_ptr<net::URLFetcher> fetcher;
    const Callback& callback;
  };

  
  void Download(const std::string& key, const Callback& downloaded);

  const std::string validation_data_url_;
  net::URLRequestContextGetter* const getter_;  

  
  std::map<const net::URLFetcher*, Request*> requests_;

  DISALLOW_COPY_AND_ASSIGN(ChromeMetadataSource);
};

}  

#endif  
