// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_SUSPICIOUS_EXTENSION_BUBBLE_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_SUSPICIOUS_EXTENSION_BUBBLE_CONTROLLER_H_

#include "chrome/browser/extensions/extension_message_bubble_controller.h"

class Profile;

namespace extensions {

class SuspiciousExtensionBubble;

class SuspiciousExtensionBubbleController
    : public extensions::ExtensionMessageBubbleController {
 public:
  
  
  static void ClearProfileListForTesting();

  explicit SuspiciousExtensionBubbleController(Profile* profile);
  virtual ~SuspiciousExtensionBubbleController();

  
  
  bool ShouldShow();

  
  virtual void Show(ExtensionMessageBubble* bubble) OVERRIDE;

 private:
  
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(SuspiciousExtensionBubbleController);
};

}  

#endif  
