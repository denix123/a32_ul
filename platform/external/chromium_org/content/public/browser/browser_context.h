// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_BROWSER_CONTEXT_H_
#define CONTENT_PUBLIC_BROWSER_BROWSER_CONTEXT_H_

#include "base/callback_forward.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "base/supports_user_data.h"
#include "content/common/content_export.h"
#include "content/public/common/push_messaging_status.h"

class GURL;

namespace base {
class FilePath;
}

namespace storage {
class ExternalMountPoints;
}

namespace net {
class URLRequestContextGetter;
}

namespace storage {
class SpecialStoragePolicy;
}

namespace content {

class BlobHandle;
class BrowserPluginGuestManager;
class DownloadManager;
class DownloadManagerDelegate;
class IndexedDBContext;
class PushMessagingService;
class ResourceContext;
class SiteInstance;
class StoragePartition;
class SSLHostStateDelegate;

class CONTENT_EXPORT BrowserContext : public base::SupportsUserData {
 public:
  static DownloadManager* GetDownloadManager(BrowserContext* browser_context);

  
  
  
  static storage::ExternalMountPoints* GetMountPoints(BrowserContext* context);

  static content::StoragePartition* GetStoragePartition(
      BrowserContext* browser_context, SiteInstance* site_instance);
  static content::StoragePartition* GetStoragePartitionForSite(
      BrowserContext* browser_context, const GURL& site);
  typedef base::Callback<void(StoragePartition*)> StoragePartitionCallback;
  static void ForEachStoragePartition(
      BrowserContext* browser_context,
      const StoragePartitionCallback& callback);
  static void AsyncObliterateStoragePartition(
      BrowserContext* browser_context,
      const GURL& site,
      const base::Closure& on_gc_required);

  
  
  static void GarbageCollectStoragePartitions(
      BrowserContext* browser_context,
      scoped_ptr<base::hash_set<base::FilePath> > active_paths,
      const base::Closure& done);

  
  
  static content::StoragePartition* GetDefaultStoragePartition(
      BrowserContext* browser_context);

  typedef base::Callback<void(scoped_ptr<BlobHandle>)> BlobCallback;

  
  static void CreateMemoryBackedBlob(BrowserContext* browser_context,
                                     const char* data, size_t length,
                                     const BlobCallback& callback);

  
  
  static void DeliverPushMessage(
      BrowserContext* browser_context,
      const GURL& origin,
      int64 service_worker_registration_id,
      const std::string& data,
      const base::Callback<void(PushMessagingStatus)>& callback);

  
  
  
  
  
  static void EnsureResourceContextInitialized(BrowserContext* browser_context);

  
  
  static void SaveSessionState(BrowserContext* browser_context);

  virtual ~BrowserContext();

  
  virtual base::FilePath GetPath() const = 0;

  
  virtual bool IsOffTheRecord() const = 0;

  
  
  
  
  virtual net::URLRequestContextGetter* GetRequestContext() = 0;

  
  
  
  
  virtual net::URLRequestContextGetter* GetRequestContextForRenderProcess(
      int renderer_child_id) = 0;

  
  
  
  virtual net::URLRequestContextGetter* GetMediaRequestContext() = 0;

  
  
  virtual net::URLRequestContextGetter* GetMediaRequestContextForRenderProcess(
      int renderer_child_id) = 0;
  virtual net::URLRequestContextGetter*
      GetMediaRequestContextForStoragePartition(
          const base::FilePath& partition_path,
          bool in_memory) = 0;

  
  virtual ResourceContext* GetResourceContext() = 0;

  
  
  
  virtual DownloadManagerDelegate* GetDownloadManagerDelegate() = 0;

  
  virtual BrowserPluginGuestManager* GetGuestManager() = 0;

  
  virtual storage::SpecialStoragePolicy* GetSpecialStoragePolicy() = 0;

  
  
  
  virtual PushMessagingService* GetPushMessagingService() = 0;

  
  
  virtual SSLHostStateDelegate* GetSSLHostStateDelegate() = 0;
};

}  

#if defined(COMPILER_GCC)
namespace BASE_HASH_NAMESPACE {

template<>
struct hash<content::BrowserContext*> {
  std::size_t operator()(content::BrowserContext* const& p) const {
    return reinterpret_cast<std::size_t>(p);
  }
};

}  
#endif

#endif  
