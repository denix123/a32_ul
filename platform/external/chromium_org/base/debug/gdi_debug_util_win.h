// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_DEBUG_GDI_DEBUG_UTIL_WIN_H_
#define BASE_DEBUG_GDI_DEBUG_UTIL_WIN_H_

#include <windows.h>

#include "base/base_export.h"

namespace base {
namespace debug {

void BASE_EXPORT GDIBitmapAllocFailure(BITMAPINFOHEADER* header,
                                       HANDLE shared_section);

}  
}  

#endif  
