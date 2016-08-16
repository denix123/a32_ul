// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_DRIVE_GDATA_WAPI_URL_GENERATOR_H_
#define GOOGLE_APIS_DRIVE_GDATA_WAPI_URL_GENERATOR_H_

#include <string>

#include "url/gurl.h"

namespace google_apis {

class GDataWapiUrlGenerator {
 public:
  GDataWapiUrlGenerator(const GURL& base_url);
  ~GDataWapiUrlGenerator();

  
  static const char kBaseUrlForProduction[];

  
  static const char kBaseDownloadUrlForProduction[];

  
  
  static GURL AddStandardUrlParams(const GURL& url);

  
  
  GURL GenerateEditUrl(const std::string& resource_id) const;

  
  
  
  
  
  
  
  GURL GenerateEditUrlWithoutParams(const std::string& resource_id) const;

  
  
  
  
  GURL GenerateEditUrlWithEmbedOrigin(const std::string& resource_id,
                                      const GURL& embed_origin) const;

 private:
  const GURL base_url_;
};

}  

#endif  
