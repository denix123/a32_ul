// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_CONTENT_VERIFIER_DELEGATE_H_
#define EXTENSIONS_BROWSER_CONTENT_VERIFIER_DELEGATE_H_

#include <set>

#include "extensions/browser/content_verify_job.h"
#include "url/gurl.h"

namespace base {
class FilePath;
class Version;
}

namespace extensions {

class Extension;

struct ContentVerifierKey {
  const uint8* data;
  int size;

  ContentVerifierKey() : data(NULL), size(0) {}

  ContentVerifierKey(const uint8* data, int size) {
    this->data = data;
    this->size = size;
  }
};

class ContentVerifierDelegate {
 public:
  
  
  
  enum Mode {
    
    
    NONE = 0,

    
    BOOTSTRAP,

    
    
    ENFORCE,

    
    ENFORCE_STRICT
  };

  virtual ~ContentVerifierDelegate() {}

  
  
  virtual Mode ShouldBeVerified(const Extension& extension) = 0;

  
  
  
  virtual const ContentVerifierKey& PublicKey() = 0;

  
  
  
  virtual GURL GetSignatureFetchUrl(const std::string& extension_id,
                                    const base::Version& version) = 0;

  
  
  virtual std::set<base::FilePath> GetBrowserImagePaths(
      const extensions::Extension* extension) = 0;

  
  
  virtual void VerifyFailed(const std::string& extension_id,
                            ContentVerifyJob::FailureReason reason) = 0;
};

}  

#endif  
