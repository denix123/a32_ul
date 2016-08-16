// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_GARBAGE_COLLECTOR_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_GARBAGE_COLLECTOR_H_

#include <map>
#include <string>

#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/extensions/install_observer.h"
#include "components/keyed_service/core/keyed_service.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class ExtensionGarbageCollector : public KeyedService, public InstallObserver {
 public:
  explicit ExtensionGarbageCollector(content::BrowserContext* context);
  virtual ~ExtensionGarbageCollector();

  static ExtensionGarbageCollector* Get(content::BrowserContext* context);

  
  void GarbageCollectExtensionsForTest();

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnBeginCrxInstall(const std::string& extension_id) OVERRIDE;
  virtual void OnFinishCrxInstall(const std::string& extension_id,
                                  bool success) OVERRIDE;

 protected:
  
  
  
  
  
  
  
  virtual void GarbageCollectExtensions();

  
  
  
  void GarbageCollectIsolatedStorageIfNeeded();

  static void GarbageCollectExtensionsOnFileThread(
      const base::FilePath& install_directory,
      const std::multimap<std::string, base::FilePath>& extension_paths);

  
  content::BrowserContext* context_;

  
  
  int crx_installs_in_progress_;

  
  
  base::WeakPtrFactory<ExtensionGarbageCollector> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionGarbageCollector);
};

}  

#endif  
