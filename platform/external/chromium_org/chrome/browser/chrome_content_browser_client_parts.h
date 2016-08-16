// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROME_CONTENT_BROWSER_CLIENT_PARTS_H_
#define CHROME_BROWSER_CHROME_CONTENT_BROWSER_CLIENT_PARTS_H_

#include <string>
#include <vector>

#include "base/memory/scoped_vector.h"
#include "storage/browser/fileapi/file_system_context.h"

namespace base {
class CommandLine;
class FilePath;
}

namespace content {
class BrowserContext;
class BrowserURLHandler;
class RenderProcessHost;
class RenderViewHost;
class SiteInstance;
struct WebPreferences;
}

namespace storage {
class FileSystemBackend;
}

class GURL;
class Profile;

class ChromeContentBrowserClientParts {
 public:
  virtual ~ChromeContentBrowserClientParts() {}

  virtual void RenderProcessWillLaunch(content::RenderProcessHost* host) {}
  virtual void SiteInstanceGotProcess(content::SiteInstance* site_instance) {}
  virtual void SiteInstanceDeleting(content::SiteInstance* site_instance) {}
  virtual void OverrideWebkitPrefs(content::RenderViewHost* rvh,
                                   const GURL& url,
                                   content::WebPreferences* web_prefs) {}
  virtual void BrowserURLHandlerCreated(content::BrowserURLHandler* handler) {}
  virtual void GetAdditionalAllowedSchemesForFileSystem(
      std::vector<std::string>* additional_allowed_schemes) {}
  virtual void GetURLRequestAutoMountHandlers(
      std::vector<storage::URLRequestAutoMountHandler>* handlers) {}
  virtual void GetAdditionalFileSystemBackends(
      content::BrowserContext* browser_context,
      const base::FilePath& storage_partition_path,
      ScopedVector<storage::FileSystemBackend>* additional_backends) {}

  
  
  virtual void AppendExtraRendererCommandLineSwitches(
      base::CommandLine* command_line,
      content::RenderProcessHost* process,
      Profile* profile) {}
};

#endif  

