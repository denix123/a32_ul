// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_CRONET_URL_REQUEST_CONTEXT_CONFIG_H_
#define COMPONENTS_CRONET_URL_REQUEST_CONTEXT_CONFIG_H_

#include <string>

#include "base/json/json_value_converter.h"
#include "base/macros.h"
#include "base/memory/scoped_vector.h"

namespace net {
class URLRequestContextBuilder;
}  

namespace cronet {

struct URLRequestContextConfig {
  
  struct QuicHint {
    QuicHint();
    ~QuicHint();

    
    static void RegisterJSONConverter(
        base::JSONValueConverter<QuicHint>* converter);

    
    std::string host;
    
    int port;
    
    int alternate_port;

   private:
    DISALLOW_COPY_AND_ASSIGN(QuicHint);
  };

  URLRequestContextConfig();
  ~URLRequestContextConfig();

  
  void ConfigureURLRequestContextBuilder(
      net::URLRequestContextBuilder* context_builder);

  
  static void RegisterJSONConverter(
      base::JSONValueConverter<URLRequestContextConfig>* converter);

  
  bool enable_quic;
  
  bool enable_spdy;
  
  
  std::string http_cache;
  
  int http_cache_max_size;
  
  std::string storage_path;
  
  ScopedVector<QuicHint> quic_hints;

 private:
  DISALLOW_COPY_AND_ASSIGN(URLRequestContextConfig);
};

}  

#endif  
