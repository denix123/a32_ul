// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_GLOBAL_SHORTCUT_LISTENER_MAC_H_
#define CHROME_BROWSER_EXTENSIONS_GLOBAL_SHORTCUT_LISTENER_MAC_H_

#include "chrome/browser/extensions/global_shortcut_listener.h"

#include <Carbon/Carbon.h>
#include <CoreFoundation/CoreFoundation.h>

#include <map>

#include "base/mac/scoped_nsobject.h"

namespace extensions {

class GlobalShortcutListenerMac : public GlobalShortcutListener {
 public:
  GlobalShortcutListenerMac();
  virtual ~GlobalShortcutListenerMac();

 private:
  typedef int KeyId;
  typedef std::map<ui::Accelerator, KeyId> AcceleratorIdMap;
  typedef std::map<KeyId, ui::Accelerator> IdAcceleratorMap;
  typedef std::map<KeyId, EventHotKeyRef> IdHotKeyRefMap;

  
  void OnHotKeyEvent(EventHotKeyID hot_key_id);
  bool OnMediaKeyEvent(int key_code);

  
  virtual void StartListening() OVERRIDE;
  virtual void StopListening() OVERRIDE;
  virtual bool RegisterAcceleratorImpl(
      const ui::Accelerator& accelerator) OVERRIDE;
  virtual void UnregisterAcceleratorImpl(
      const ui::Accelerator& accelerator) OVERRIDE;

  
  bool RegisterHotKey(const ui::Accelerator& accelerator, KeyId hot_key_id);
  void UnregisterHotKey(const ui::Accelerator& accelerator);

  
  void StartWatchingMediaKeys();
  void StopWatchingMediaKeys();

  
  void StartWatchingHotKeys();
  void StopWatchingHotKeys();

  
  bool IsAnyMediaKeyRegistered();

  
  bool IsAnyHotKeyRegistered();

  
  static CGEventRef EventTapCallback(
      CGEventTapProxy proxy, CGEventType type, CGEventRef event, void* refcon);

  
  static OSStatus HotKeyHandler(
      EventHandlerCallRef next_handler, EventRef event, void* user_data);

  
  bool is_listening_;

  
  KeyId hot_key_id_;

  
  
  
  AcceleratorIdMap accelerator_ids_;

  
  IdAcceleratorMap id_accelerators_;

  
  IdHotKeyRefMap id_hot_key_refs_;

  
  CFMachPortRef event_tap_;
  CFRunLoopSourceRef event_tap_source_;

  
  EventHandlerRef event_handler_;

  DISALLOW_COPY_AND_ASSIGN(GlobalShortcutListenerMac);
};

}  

#endif  
