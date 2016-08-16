// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_RUNTIME_DATA_H_
#define EXTENSIONS_BROWSER_RUNTIME_DATA_H_

#include <map>
#include <string>

#include "base/compiler_specific.h"
#include "extensions/browser/extension_registry_observer.h"

namespace extensions {

class Extension;
class ExtensionRegistry;

class RuntimeData : public ExtensionRegistryObserver {
 public:
  
  
  explicit RuntimeData(ExtensionRegistry* registry);
  virtual ~RuntimeData();

  
  
  
  bool IsBackgroundPageReady(const Extension* extension) const;
  void SetBackgroundPageReady(const Extension* extension, bool value);

  
  
  bool IsBeingUpgraded(const Extension* extension) const;
  void SetBeingUpgraded(const Extension* extension, bool value);

  
  
  bool HasUsedWebRequest(const Extension* extension) const;
  void SetHasUsedWebRequest(const Extension* extension, bool value);

  
  bool HasExtensionForTesting(const Extension* extension) const;

  
  
  void ClearAll();

  
  virtual void OnExtensionUnloaded(content::BrowserContext* browser_context,
                                   const Extension* extension,
                                   UnloadedExtensionInfo::Reason reason)
      OVERRIDE;

 private:
  
  enum RuntimeFlag {
    
    BACKGROUND_PAGE_READY = 1 << 0,
    
    BEING_UPGRADED        = 1 << 1,
    
    HAS_USED_WEBREQUEST   = 1 << 2,
  };

  
  bool HasFlag(const Extension* extension, RuntimeFlag flag) const;

  
  
  void SetFlag(const Extension* extension, RuntimeFlag flag, bool value);

  
  typedef std::map<std::string, int> ExtensionFlagsMap;
  ExtensionFlagsMap extension_flags_;

  ExtensionRegistry* registry_;  
};

}  

#endif  
