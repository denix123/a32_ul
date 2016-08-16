// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_UTILS_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_UTILS_H_

#include <string>

struct CrxComponent;
class GURL;

namespace base {
class FilePath;
}

namespace net {
class URLFetcher;
class URLFetcherDelegate;
class URLRequestContextGetter;
}

namespace component_updater {

class Configurator;
struct CrxUpdateItem;


std::string BuildProtocolRequest(const std::string& browser_version,
                                 const std::string& channel,
                                 const std::string& lang,
                                 const std::string& os_long_name,
                                 const std::string& request_body,
                                 const std::string& additional_attributes);

net::URLFetcher* SendProtocolRequest(
    const GURL& url,
    const std::string& protocol_request,
    net::URLFetcherDelegate* url_fetcher_delegate,
    net::URLRequestContextGetter* url_request_context_getter);

bool FetchSuccess(const net::URLFetcher& fetcher);

int GetFetchError(const net::URLFetcher& fetcher);

bool HasDiffUpdate(const CrxUpdateItem* update_item);

bool IsHttpServerError(int status_code);

bool DeleteFileAndEmptyParentDirectory(const base::FilePath& filepath);

std::string GetCrxComponentID(const CrxComponent& component);

}  

#endif  
