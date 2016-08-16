// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_APP_RUNTIME_APP_RUNTIME_API_H_
#define EXTENSIONS_BROWSER_API_APP_RUNTIME_APP_RUNTIME_API_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"

class GURL;

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {

class Extension;
struct GrantedFileEntry;

class AppRuntimeEventRouter {
 public:
  
  static void DispatchOnEmbedRequestedEvent(
      content::BrowserContext* context,
      scoped_ptr<base::DictionaryValue> app_embedding_request_data,
      const extensions::Extension* extension);

  
  static void DispatchOnLaunchedEvent(content::BrowserContext* context,
                                      const Extension* extension);

  
  
  static void DispatchOnRestartedEvent(content::BrowserContext* context,
                                       const Extension* extension);

  
  
  
  
  
  
  
  
  
  
  

  
  
  
  static void DispatchOnLaunchedEventWithFileEntries(
      content::BrowserContext* context,
      const Extension* extension,
      const std::string& handler_id,
      const std::vector<std::string>& mime_types,
      const std::vector<GrantedFileEntry>& file_entries);

  
  
  static void DispatchOnLaunchedEventWithUrl(content::BrowserContext* context,
                                             const Extension* extension,
                                             const std::string& handler_id,
                                             const GURL& url,
                                             const GURL& referrer_url);
};

}  

#endif  
