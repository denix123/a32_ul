// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_CONTENT_VERIFIER_H_
#define EXTENSIONS_BROWSER_CONTENT_VERIFIER_H_

#include <set>
#include <string>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/scoped_observer.h"
#include "base/version.h"
#include "extensions/browser/content_verifier_delegate.h"
#include "extensions/browser/content_verify_job.h"
#include "extensions/browser/extension_registry_observer.h"

namespace base {
class FilePath;
}

namespace content {
class BrowserContext;
}

namespace extensions {

class Extension;
class ContentHashFetcher;
class ContentVerifierIOData;

class ContentVerifier : public base::RefCountedThreadSafe<ContentVerifier>,
                        public ExtensionRegistryObserver {
 public:
  
  ContentVerifier(content::BrowserContext* context,
                  ContentVerifierDelegate* delegate);
  void Start();
  void Shutdown();

  
  
  ContentVerifyJob* CreateJobFor(const std::string& extension_id,
                                 const base::FilePath& extension_root,
                                 const base::FilePath& relative_path);

  
  
  void VerifyFailed(const std::string& extension_id,
                    ContentVerifyJob::FailureReason reason);

  
  virtual void OnExtensionLoaded(content::BrowserContext* browser_context,
                                 const Extension* extension) OVERRIDE;
  virtual void OnExtensionUnloaded(
      content::BrowserContext* browser_context,
      const Extension* extension,
      UnloadedExtensionInfo::Reason reason) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(ContentVerifier);

  friend class base::RefCountedThreadSafe<ContentVerifier>;
  virtual ~ContentVerifier();

  void OnFetchComplete(const std::string& extension_id,
                       bool success,
                       bool was_force_check,
                       const std::set<base::FilePath>& hash_mismatch_paths);

  void OnFetchCompleteHelper(const std::string& extension_id,
                             bool shouldVerifyAnyPathsResult);

  
  
  
  
  bool ShouldVerifyAnyPaths(const std::string& extension_id,
                            const base::FilePath& extension_root,
                            const std::set<base::FilePath>& relative_paths);

  
  bool shutdown_;

  content::BrowserContext* context_;

  scoped_ptr<ContentVerifierDelegate> delegate_;

  
  scoped_ptr<ContentHashFetcher> fetcher_;

  
  ScopedObserver<ExtensionRegistry, ExtensionRegistryObserver> observer_;

  
  scoped_refptr<ContentVerifierIOData> io_data_;
};

}  

#endif  
