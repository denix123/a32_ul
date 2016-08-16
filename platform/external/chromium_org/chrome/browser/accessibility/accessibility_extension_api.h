// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ACCESSIBILITY_ACCESSIBILITY_EXTENSION_API_H_
#define CHROME_BROWSER_ACCESSIBILITY_ACCESSIBILITY_EXTENSION_API_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/memory/singleton.h"
#include "base/values.h"
#include "chrome/browser/accessibility/accessibility_events.h"
#include "chrome/browser/extensions/chrome_extension_function.h"
#include "ui/accessibility/ax_enums.h"

namespace extensions {
class ExtensionHost;
} 

class ExtensionAccessibilityEventRouter {
 public:
  typedef base::Callback<void(ui::AXEvent,
                              const AccessibilityControlInfo*)>
      ControlEventCallback;
  
  static ExtensionAccessibilityEventRouter* GetInstance();

  
  
  base::DictionaryValue* last_focused_control_dict() {
    return &last_focused_control_dict_;
  }

  
  
  
  
  void SetAccessibilityEnabled(bool enabled);
  bool IsAccessibilityEnabled() const;

  
  
  void SetControlEventCallbackForTesting(ControlEventCallback callback);
  void ClearControlEventCallback();

  
  void HandleWindowEvent(ui::AXEvent event,
                         const AccessibilityWindowInfo* info);

  
  void HandleMenuEvent(ui::AXEvent event,
                       const AccessibilityMenuInfo* info);

  
  void HandleControlEvent(ui::AXEvent event,
                          const AccessibilityControlInfo* info);

  void OnChromeVoxLoadStateChanged(
      Profile* profile,
      bool loading,
      bool make_announcements);

  static void DispatchEventToChromeVox(
      Profile* profile,
      const char* event_name,
      scoped_ptr<base::ListValue> event_args);

 private:
  friend struct DefaultSingletonTraits<ExtensionAccessibilityEventRouter>;

  ExtensionAccessibilityEventRouter();
  virtual ~ExtensionAccessibilityEventRouter();

  void OnWindowOpened(const AccessibilityWindowInfo* details);
  void OnControlFocused(const AccessibilityControlInfo* details);
  void OnControlAction(const AccessibilityControlInfo* details);
  void OnControlHover(const AccessibilityControlInfo* details);
  void OnTextChanged(const AccessibilityControlInfo* details);
  void OnMenuOpened(const AccessibilityMenuInfo* details);
  void OnMenuClosed(const AccessibilityMenuInfo* details);

  void DispatchEvent(Profile* profile,
                     const char* event_name,
                     scoped_ptr<base::ListValue> event_args);

  base::DictionaryValue last_focused_control_dict_;

  bool enabled_;

  
  ControlEventCallback control_event_callback_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionAccessibilityEventRouter);
};

class AccessibilityPrivateSetAccessibilityEnabledFunction
    : public ChromeSyncExtensionFunction {
  virtual ~AccessibilityPrivateSetAccessibilityEnabledFunction() {}
  virtual bool RunSync() OVERRIDE;
  DECLARE_EXTENSION_FUNCTION("accessibilityPrivate.setAccessibilityEnabled",
                             ACCESSIBILITY_PRIVATE_SETACCESSIBILITYENABLED)
};

class AccessibilityPrivateSetNativeAccessibilityEnabledFunction
    : public ChromeSyncExtensionFunction {
  virtual ~AccessibilityPrivateSetNativeAccessibilityEnabledFunction() {}
  virtual bool RunSync() OVERRIDE;
  DECLARE_EXTENSION_FUNCTION(
      "accessibilityPrivate.setNativeAccessibilityEnabled",
      ACCESSIBILITY_PRIVATE_SETNATIVEACCESSIBILITYENABLED)
};

class AccessibilityPrivateGetFocusedControlFunction
    : public ChromeSyncExtensionFunction {
  virtual ~AccessibilityPrivateGetFocusedControlFunction() {}
  virtual bool RunSync() OVERRIDE;
  DECLARE_EXTENSION_FUNCTION("accessibilityPrivate.getFocusedControl",
                             ACCESSIBILITY_PRIVATE_GETFOCUSEDCONTROL)
};

class AccessibilityPrivateGetAlertsForTabFunction
    : public ChromeSyncExtensionFunction {
  virtual ~AccessibilityPrivateGetAlertsForTabFunction() {}
  virtual bool RunSync() OVERRIDE;
  DECLARE_EXTENSION_FUNCTION("accessibilityPrivate.getAlertsForTab",
                             ACCESSIBILITY_PRIVATE_GETALERTSFORTAB)
};

class AccessibilityPrivateSetFocusRingFunction
    : public ChromeSyncExtensionFunction {
  virtual ~AccessibilityPrivateSetFocusRingFunction() {}
  virtual bool RunSync() OVERRIDE;
  DECLARE_EXTENSION_FUNCTION("accessibilityPrivate.setFocusRing",
                             ACCESSIBILITY_PRIVATE_SETFOCUSRING)
};

#endif  
