// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_CONTENT_HASH_FETCHER_H_
#define EXTENSIONS_BROWSER_CONTENT_HASH_FETCHER_H_

#include <set>
#include <string>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "extensions/common/extension.h"

namespace content {
class BrowserContext;
}

namespace extensions {

class ExtensionRegistry;
class ContentHashFetcherJob;
class ContentVerifierDelegate;

class ContentHashFetcher {
 public:
  
  
  
  
  
  
  typedef base::Callback<
      void(const std::string&, bool, bool, const std::set<base::FilePath>&)>
      FetchCallback;

  
  
  ContentHashFetcher(content::BrowserContext* context,
                     ContentVerifierDelegate* delegate,
                     const FetchCallback& callback);
  virtual ~ContentHashFetcher();

  
  
  
  void DoFetch(const Extension* extension, bool force);

  
  virtual void ExtensionLoaded(const Extension* extension);
  virtual void ExtensionUnloaded(const Extension* extension);

 private:
  
  void JobFinished(ContentHashFetcherJob* job);

  content::BrowserContext* context_;
  ContentVerifierDelegate* delegate_;
  FetchCallback fetch_callback_;

  
  
  
  typedef std::pair<ExtensionId, std::string> IdAndVersion;
  typedef std::map<IdAndVersion, scoped_refptr<ContentHashFetcherJob> > JobMap;
  JobMap jobs_;

  
  base::WeakPtrFactory<ContentHashFetcher> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ContentHashFetcher);
};

}  

#endif  
