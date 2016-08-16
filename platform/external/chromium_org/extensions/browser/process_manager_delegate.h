// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_PROCESS_MANAGER_DELEGATE_H_
#define EXTENSIONS_BROWSER_PROCESS_MANAGER_DELEGATE_H_

namespace content {
class BrowserContext;
};

namespace extensions {

class ProcessManagerDelegate {
 public:
  virtual ~ProcessManagerDelegate() {}

  
  
  virtual bool IsBackgroundPageAllowed(
      content::BrowserContext* context) const = 0;

  
  
  
  
  virtual bool DeferCreatingStartupBackgroundHosts(
      content::BrowserContext* context) const = 0;
};

}  

#endif  
