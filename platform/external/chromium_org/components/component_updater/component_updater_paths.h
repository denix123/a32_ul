// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_PATHS_H_
#define COMPONENTS_COMPONENT_UPDATER_COMPONENT_UPDATER_PATHS_H_

#include "base/files/file_path.h"

namespace component_updater {

enum {
  PATH_START = 10000,
  DIR_COMPONENT_CLD2 = PATH_START,  
                                    
  DIR_RECOVERY_BASE,                
                                    
  DIR_SWIFT_SHADER,                 
  DIR_SW_REPORTER,                  
  DIR_COMPONENT_EV_WHITELIST,       
  PATH_END
};

void RegisterPathProvider(int components_root_key);

}  

#endif  
