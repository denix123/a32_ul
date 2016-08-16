// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_COCOA_SYSTEM_HOTKEY_MAP_H_
#define CONTENT_BROWSER_COCOA_SYSTEM_HOTKEY_MAP_H_

#import <Cocoa/Cocoa.h>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/macros.h"
#include "content/common/content_export.h"

namespace content {

struct SystemHotkey;

class CONTENT_EXPORT SystemHotkeyMap {
 public:
  SystemHotkeyMap();
  ~SystemHotkeyMap();

  
  
  static NSDictionary* DictionaryFromData(NSData* data);

  
  
  
  
  
  bool ParseDictionary(NSDictionary* dictionary);

  
  
  bool IsEventReserved(NSEvent* event) const;

 private:
  FRIEND_TEST_ALL_PREFIXES(SystemHotkeyMapTest, Parse);
  FRIEND_TEST_ALL_PREFIXES(SystemHotkeyMapTest, ParseCustomEntries);
  FRIEND_TEST_ALL_PREFIXES(SystemHotkeyMapTest, ParseMouse);

  
  bool IsHotkeyReserved(unsigned short key_code, NSUInteger modifiers) const;

  
  
  void ReserveHotkey(unsigned short key_code,
                     NSUInteger modifiers,
                     NSString* system_effect);

  
  void ReserveHotkey(unsigned short key_code, NSUInteger modifiers);

  std::vector<SystemHotkey> system_hotkeys_;

  DISALLOW_COPY_AND_ASSIGN(SystemHotkeyMap);
};

}  

#endif  
