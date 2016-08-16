// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_ENHANCED_BOOKMARKS_IMAGE_STORE_UTIL_H_
#define COMPONENTS_ENHANCED_BOOKMARKS_IMAGE_STORE_UTIL_H_

#include "base/memory/ref_counted_memory.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/image/image.h"

namespace enhanced_bookmarks {

scoped_refptr<base::RefCountedMemory> BytesForImage(const gfx::Image& image);

gfx::Image ImageForBytes(const scoped_refptr<base::RefCountedMemory>& data);

}

#endif  
