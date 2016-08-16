// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_DISK_BASED_CERT_CACHE_H
#define NET_HTTP_DISK_BASED_CERT_CACHE_H

#include <string>

#include "base/callback.h"
#include "base/containers/hash_tables.h"
#include "base/containers/mru_cache.h"
#include "base/memory/weak_ptr.h"
#include "net/base/net_export.h"
#include "net/cert/x509_certificate.h"

namespace disk_cache {
class Backend;
}  

namespace net {

class NET_EXPORT_PRIVATE DiskBasedCertCache {
 public:
  typedef base::Callback<void(const X509Certificate::OSCertHandle cert_handle)>
      GetCallback;
  typedef base::Callback<void(const std::string&)> SetCallback;

  
  
  explicit DiskBasedCertCache(disk_cache::Backend* backend);
  ~DiskBasedCertCache();

  
  
  
  
  
  void GetCertificate(const std::string& key, const GetCallback& cb);

  
  
  
  void SetCertificate(const X509Certificate::OSCertHandle cert_handle,
                      const SetCallback& cb);

  
  
  
  size_t mem_cache_hits_for_testing() const { return mem_cache_hits_; }

  
  
  
  size_t mem_cache_misses_for_testing() const { return mem_cache_misses_; }

 private:
  class ReadWorker;
  class WriteWorker;

  
  struct CertFree {
    void operator()(X509Certificate::OSCertHandle cert_handle);
  };

  
  
  typedef base::MRUCacheBase<std::string,
                             X509Certificate::OSCertHandle,
                             CertFree> MRUCertCache;

  
  
  typedef base::hash_map<std::string, ReadWorker*> ReadWorkerMap;
  typedef base::hash_map<std::string, WriteWorker*> WriteWorkerMap;

  
  
  
  void FinishedReadOperation(const std::string& key,
                             X509Certificate::OSCertHandle cert_handle);
  void FinishedWriteOperation(const std::string& key,
                              X509Certificate::OSCertHandle cert_handle);

  disk_cache::Backend* backend_;

  ReadWorkerMap read_worker_map_;
  WriteWorkerMap write_worker_map_;
  MRUCertCache mru_cert_cache_;

  int mem_cache_hits_;
  int mem_cache_misses_;

  base::WeakPtrFactory<DiskBasedCertCache> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(DiskBasedCertCache);
};

}  

#endif  
