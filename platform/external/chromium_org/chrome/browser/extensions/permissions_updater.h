// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_PERMISSIONS_UPDATER_H__
#define CHROME_BROWSER_EXTENSIONS_PERMISSIONS_UPDATER_H__

#include <string>

#include "base/memory/ref_counted.h"

namespace base {
class DictionaryValue;
}

namespace content {
class BrowserContext;
}

namespace extensions {

class Extension;
class ExtensionPrefs;
class PermissionSet;

class PermissionsUpdater {
 public:
  enum InitFlag {
    INIT_FLAG_NONE = 0,
    INIT_FLAG_TRANSIENT = 1 << 0,
  };

  explicit PermissionsUpdater(content::BrowserContext* browser_context);
  PermissionsUpdater(content::BrowserContext* browser_context,
                     InitFlag init_flag);
  ~PermissionsUpdater();

  
  
  
  void AddPermissions(const Extension* extension,
                      const PermissionSet* permissions);

  
  
  void RemovePermissions(const Extension* extension,
                         const PermissionSet* permissions);

  
  
  void GrantActivePermissions(const Extension* extension);

  
  
  
  void InitializePermissions(const Extension* extension);

  
  void GrantWithheldImpliedAllHosts(const Extension* extension);

  
  void WithholdImpliedAllHosts(const Extension* extension);

 private:
  enum EventType {
    ADDED,
    REMOVED,
  };

  
  
  
  
  void SetPermissions(const Extension* extension,
                      const scoped_refptr<const PermissionSet>& active,
                      scoped_refptr<const PermissionSet> withheld);

  
  void DispatchEvent(const std::string& extension_id,
                     const char* event_name,
                     const PermissionSet* changed_permissions);

  
  
  
  
  
  void NotifyPermissionsUpdated(EventType event_type,
                                const Extension* extension,
                                const PermissionSet* changed);

  
  content::BrowserContext* browser_context_;

  
  
  InitFlag init_flag_;
};

}  

#endif  
