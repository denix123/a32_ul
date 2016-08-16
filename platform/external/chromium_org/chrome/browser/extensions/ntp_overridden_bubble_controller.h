// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_NTP_OVERRIDDEN_BUBBLE_CONTROLLER_H_
#define CHROME_BROWSER_EXTENSIONS_NTP_OVERRIDDEN_BUBBLE_CONTROLLER_H_

#include <string>
#include "chrome/browser/extensions/extension_message_bubble_controller.h"

namespace extensions {

class NtpOverriddenBubbleController : public ExtensionMessageBubbleController {
 public:
  explicit NtpOverriddenBubbleController(Profile* profile);
  virtual ~NtpOverriddenBubbleController();

  
  
  bool ShouldShow(const std::string& extension_id);

  
  virtual bool CloseOnDeactivate() OVERRIDE;

 private:
  
  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(NtpOverriddenBubbleController);
};

}  

#endif  
