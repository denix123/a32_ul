// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COCOA_SYSTEM_HOTKEY_HELPER_MAC_H_
#define CONTENT_BROWSER_COCOA_SYSTEM_HOTKEY_HELPER_MAC_H_

#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"

#ifdef __OBJC__
@class NSDictionary;
#else
class NSDictionary;
#endif

namespace content {

class SystemHotkeyMap;

class SystemHotkeyHelperMac {
 public:
  
  static SystemHotkeyHelperMac* GetInstance();

  
  
  void DeferredLoadSystemHotkeys();

  
  SystemHotkeyMap* map() { return map_.get(); }

 private:
  friend struct DefaultSingletonTraits<SystemHotkeyHelperMac>;

  SystemHotkeyHelperMac();
  ~SystemHotkeyHelperMac();

  
  
  
  void LoadSystemHotkeys();

  
  
  void FileDidLoad(NSDictionary* dictionary);

  scoped_ptr<SystemHotkeyMap> map_;

  DISALLOW_COPY_AND_ASSIGN(SystemHotkeyHelperMac);
};

}  

#endif  
