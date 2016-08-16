// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_UI_BASE_PATHS_H_
#define UI_BASE_UI_BASE_PATHS_H_

#include "build/build_config.h"
#include "ui/base/ui_base_export.h"


namespace ui {

enum {
  PATH_START = 3000,

  DIR_LOCALES,              

  
  UI_DIR_TEST_DATA,            

#if defined(OS_ANDROID)
  DIR_RESOURCE_PAKS_ANDROID,
#endif

  UI_TEST_PAK,

  PATH_END
};

UI_BASE_EXPORT void RegisterPathProvider();

}  

#endif  
