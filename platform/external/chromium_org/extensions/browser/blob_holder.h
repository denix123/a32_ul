// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_BLOB_HOLDER_H_
#define EXTENSIONS_BROWSER_BLOB_HOLDER_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/supports_user_data.h"

namespace content {
class BlobHandle;
class RenderProcessHost;
}

namespace extensions {

class ExtensionMessageFilter;

class BlobHolder : public base::SupportsUserData::Data {
 public:
  
  static BlobHolder* FromRenderProcessHost(
      content::RenderProcessHost* render_process_host);

  virtual ~BlobHolder();

  
  void HoldBlobReference(scoped_ptr<content::BlobHandle> blob);

 private:
  typedef std::multimap<std::string, linked_ptr<content::BlobHandle> >
      BlobHandleMultimap;

  explicit BlobHolder(content::RenderProcessHost* render_process_host);

  
  
  
  void DropBlobs(const std::vector<std::string>& blob_uuids);
  friend class ExtensionMessageFilter;

  bool ContainsBlobHandle(content::BlobHandle* handle) const;

  
  content::RenderProcessHost* render_process_host_;

  BlobHandleMultimap held_blobs_;

  DISALLOW_COPY_AND_ASSIGN(BlobHolder);
};

}  

#endif  
