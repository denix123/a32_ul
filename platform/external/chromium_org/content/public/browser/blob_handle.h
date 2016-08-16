// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_BLOB_HANDLE_H_
#define CONTENT_PUBLIC_BROWSER_BLOB_HANDLE_H_

#include <string>

namespace content {

class BlobHandle {
 public:
  virtual ~BlobHandle() {}
  virtual std::string GetUUID() = 0;

 protected:
  BlobHandle() {}
};

}  

#endif  
