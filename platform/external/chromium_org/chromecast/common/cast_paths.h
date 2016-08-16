// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_COMMON_CAST_PATHS_H_
#define CHROMECAST_COMMON_CAST_PATHS_H_

#include "build/build_config.h"


namespace chromecast {

enum {
  PATH_START = 8000,

  DIR_CAST_HOME,    
                    

#if defined(OS_ANDROID)
  FILE_CAST_ANDROID_LOG, 
#endif  
  FILE_CAST_CONFIG, 
  FILE_CAST_PAK,    
  PATH_END
};

void RegisterPathProvider();

}  

#endif  
