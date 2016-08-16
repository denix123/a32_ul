// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_URL_UTILS_H_
#define COMPONENTS_DOM_DISTILLER_CORE_URL_UTILS_H_

#include <string>

class GURL;

namespace dom_distiller {

namespace url_utils {

const GURL GetDistillerViewUrlFromEntryId(const std::string& scheme,
                                          const std::string& entry_id);

const GURL GetDistillerViewUrlFromUrl(const std::string& scheme,
                                      const GURL& view_url);

std::string GetValueForKeyInUrl(const GURL& url, const std::string& key);

std::string GetValueForKeyInUrlPathQuery(const std::string& path,
                                         const std::string& key);

bool IsUrlDistillable(const GURL& url);

bool IsDistilledPage(const GURL& url);

std::string GetIsDistillableJs();

}  

}  

#endif  
