// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_BINARY_FEATURE_EXTRACTOR_H_
#define CHROME_BROWSER_SAFE_BROWSING_BINARY_FEATURE_EXTRACTOR_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"

namespace base {
class FilePath;
}

namespace safe_browsing {
class ClientDownloadRequest_ImageHeaders;
class ClientDownloadRequest_SignatureInfo;

class BinaryFeatureExtractor
    : public base::RefCountedThreadSafe<BinaryFeatureExtractor> {
 public:
  BinaryFeatureExtractor();

  
  
  virtual void CheckSignature(
      const base::FilePath& file_path,
      ClientDownloadRequest_SignatureInfo* signature_info);

  
  virtual void ExtractImageHeaders(
      const base::FilePath& file_path,
      ClientDownloadRequest_ImageHeaders* image_headers);

 protected:
  friend class base::RefCountedThreadSafe<BinaryFeatureExtractor>;
  virtual ~BinaryFeatureExtractor();

 private:
  DISALLOW_COPY_AND_ASSIGN(BinaryFeatureExtractor);
};
}  

#endif  
