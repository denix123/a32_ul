// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_DEV_MODE_BUBBLE_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_DEV_MODE_BUBBLE_CONTROLLER_H_

#include <string>

#include "chrome/browser/extensions/extension_message_bubble_controller.h"

namespace extensions {

class Extension;

class DevModeBubbleController : public ExtensionMessageBubbleController {
 public:
  
  
  static void ClearProfileListForTesting();

  
  static bool IsDevModeExtension(const Extension* extension);

  explicit DevModeBubbleController(Profile* profile);
  virtual ~DevModeBubbleController();

  
  
  bool ShouldShow();

  
  virtual void Show(ExtensionMessageBubble* bubble) OVERRIDE;

 private:
  
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(DevModeBubbleController);
};

}  

#endif  
