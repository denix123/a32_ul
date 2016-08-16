// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_TOOLS_PACKAGE_MANAGER_FETCHER_H_
#define MOJO_TOOLS_PACKAGE_MANAGER_FETCHER_H_

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "mojo/common/handle_watcher.h"
#include "mojo/public/cpp/system/macros.h"
#include "mojo/services/public/interfaces/network/network_service.mojom.h"
#include "mojo/services/public/interfaces/network/url_loader.mojom.h"
#include "url/gurl.h"

namespace base {
class FilePath;
}  

namespace mojo {

class PackageFetcherDelegate;

class PackageFetcher {
 public:
  PackageFetcher(NetworkService* network_service,
                 PackageFetcherDelegate* delegate,
                 const GURL& url);
  virtual ~PackageFetcher();

 private:
  void OnReceivedResponse(URLResponsePtr response);

  void ReadData(MojoResult);
  void WaitToReadMore();

  PackageFetcherDelegate* delegate_;

  
  GURL url_;

  URLLoaderPtr loader_;

  
  ScopedDataPipeConsumerHandle body_;
  common::HandleWatcher handle_watcher_;

  base::FilePath output_file_name_;
  base::File output_file_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(PackageFetcher);
};

class PackageFetcherDelegate {
 public:
  virtual void FetchSucceeded(const GURL& url, const base::FilePath& name) = 0;

  virtual void FetchFailed(const GURL& url) = 0;
};

}  

#endif  
