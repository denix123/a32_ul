// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_TEST_ACCESSIBILITY_BROWSER_TEST_UTILS_H_
#define CONTENT_TEST_ACCESSIBILITY_BROWSER_TEST_UTILS_H_

#include "base/memory/weak_ptr.h"
#include "content/common/accessibility_mode_enums.h"
#include "ui/accessibility/ax_node_data.h"
#include "ui/accessibility/ax_tree.h"

namespace content {

class MessageLoopRunner;
class RenderFrameHostImpl;
class Shell;

class AccessibilityNotificationWaiter {
 public:
  explicit AccessibilityNotificationWaiter(Shell* shell);
  AccessibilityNotificationWaiter(
      Shell* shell,
      AccessibilityMode accessibility_mode,
      ui::AXEvent event);
  AccessibilityNotificationWaiter(
      RenderFrameHostImpl* frame_host,
       ui::AXEvent event);
  ~AccessibilityNotificationWaiter();

  
  
  
  void WaitForNotification();

  
  
  const ui::AXTree& GetAXTree() const;

  
  
  int event_target_id() { return event_target_id_; }

 private:
  
  void OnAccessibilityEvent(ui::AXEvent event, int event_target_id);

  
  
  bool IsAboutBlank();

  RenderFrameHostImpl* frame_host_;
  ui::AXEvent event_to_wait_for_;
  scoped_refptr<MessageLoopRunner> loop_runner_;
  int event_target_id_;

  base::WeakPtrFactory<AccessibilityNotificationWaiter> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AccessibilityNotificationWaiter);
};

}  

#endif  
