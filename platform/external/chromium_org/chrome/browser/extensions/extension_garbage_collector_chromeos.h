// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_GARBAGE_COLLECTOR_CHROMEOS_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_GARBAGE_COLLECTOR_CHROMEOS_H_

#include "chrome/browser/extensions/extension_garbage_collector.h"

namespace extensions {

class ExtensionGarbageCollectorChromeOS : public ExtensionGarbageCollector {
 public:
  explicit ExtensionGarbageCollectorChromeOS(content::BrowserContext* context);
  virtual ~ExtensionGarbageCollectorChromeOS();

  static ExtensionGarbageCollectorChromeOS* Get(
      content::BrowserContext* context);

  
  void disable_garbage_collection() { disable_garbage_collection_ = true; }
  void enable_garbage_collection() { disable_garbage_collection_ = false; }

  
  
  static void ClearGarbageCollectedForTesting();

 private:
  
  virtual void GarbageCollectExtensions() OVERRIDE;

  
  bool CanGarbageCollectSharedExtensions();

  
  void GarbageCollectSharedExtensions();

  
  
  
  
  bool disable_garbage_collection_;

  
  
  
  static bool shared_extensions_garbage_collected_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionGarbageCollectorChromeOS);
};

}  

#endif  
