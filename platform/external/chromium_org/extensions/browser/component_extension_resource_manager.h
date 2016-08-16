// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_COMPONENT_EXTENSION_RESOURCE_MANAGER_H_
#define EXTENSIONS_BROWSER_COMPONENT_EXTENSION_RESOURCE_MANAGER_H_

namespace base {
class FilePath;
}

namespace extensions {

class ComponentExtensionResourceManager {
 public:
  virtual ~ComponentExtensionResourceManager() {}

  
  
  
  
  virtual bool IsComponentExtensionResource(
    const base::FilePath& extension_path,
    const base::FilePath& resource_path,
    int* resource_id) = 0;
};

}  

#endif  
