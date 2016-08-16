// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_COMMON_TEST_TEST_UTILS_H_
#define MOJO_COMMON_TEST_TEST_UTILS_H_

#include <stddef.h>
#include <stdio.h>

#include <string>

#include "base/files/file_path.h"
#include "base/files/scoped_file.h"
#include "mojo/embedder/platform_handle.h"
#include "mojo/embedder/scoped_platform_handle.h"

namespace mojo {
namespace test {

// On success, |bytes_written| is updated to the number of bytes written;
bool BlockingWrite(const embedder::PlatformHandle& handle,
                   const void* buffer,
                   size_t bytes_to_write,
                   size_t* bytes_written);

bool BlockingRead(const embedder::PlatformHandle& handle,
                  void* buffer,
                  size_t buffer_size,
                  size_t* bytes_read);

bool NonBlockingRead(const embedder::PlatformHandle& handle,
                     void* buffer,
                     size_t buffer_size,
                     size_t* bytes_read);

embedder::ScopedPlatformHandle PlatformHandleFromFILE(base::ScopedFILE fp);

base::ScopedFILE FILEFromPlatformHandle(embedder::ScopedPlatformHandle h,
                                        const char* mode);

base::FilePath GetFilePathForJSResource(const std::string& path);

}  
}  

#endif  
