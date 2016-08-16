// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_ACTIVE_TAB_PERMISSION_GRANTER_H_
#define CHROME_BROWSER_EXTENSIONS_ACTIVE_TAB_PERMISSION_GRANTER_H_

#include <set>
#include <string>

#include "base/scoped_observer.h"
#include "content/public/browser/web_contents_observer.h"
#include "extensions/browser/extension_registry_observer.h"
#include "extensions/common/extension_set.h"
#include "extensions/common/url_pattern_set.h"

class Profile;

namespace content {
class WebContents;
}

namespace extensions {

class Extension;
class ExtensionRegistry;

class ActiveTabPermissionGranter
    : public content::WebContentsObserver,
      public extensions::ExtensionRegistryObserver {
 public:
  ActiveTabPermissionGranter(content::WebContents* web_contents,
                             int tab_id,
                             Profile* profile);
  virtual ~ActiveTabPermissionGranter();

  
  
  void GrantIfRequested(const Extension* extension);

 private:
  
  virtual void DidNavigateMainFrame(
      const content::LoadCommittedDetails& details,
      const content::FrameNavigateParams& params) OVERRIDE;
  virtual void WebContentsDestroyed() OVERRIDE;

  
  virtual void OnExtensionUnloaded(content::BrowserContext* browser_context,
                                   const Extension* extension,
                                   UnloadedExtensionInfo::Reason reason)
      OVERRIDE;

  
  
  void ClearActiveExtensionsAndNotify();

  
  int tab_id_;

  
  
  ExtensionSet granted_extensions_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver>
      extension_registry_observer_;

  DISALLOW_COPY_AND_ASSIGN(ActiveTabPermissionGranter);
};

}  

#endif  
