// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_IMAGE_WRITER_IMAGE_WRITER_UTIL_MAC_H
#define CHROME_COMMON_EXTENSIONS_IMAGE_WRITER_IMAGE_WRITER_UTIL_MAC_H

#include <IOKit/IOKitLib.h>

namespace extensions {

bool IsUsbDevice(io_object_t disk_obj);

}  

#endif  
