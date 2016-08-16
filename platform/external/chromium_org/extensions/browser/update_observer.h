// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_UPDATE_OBSERVER_H_
#define EXTENSIONS_BROWSER_UPDATE_OBSERVER_H_

#include <string>

namespace extensions {
class Extension;

class UpdateObserver {
 public:
  
  virtual void OnAppUpdateAvailable(const Extension* extension) = 0;

  
  virtual void OnChromeUpdateAvailable() = 0;

 protected:
  virtual ~UpdateObserver() {}
};

}  

#endif  