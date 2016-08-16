// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_NACL_BROWSER_NACL_BROWSER_H_
#define COMPONENTS_NACL_BROWSER_NACL_BROWSER_H_

#include <deque>

#include "base/bind.h"
#include "base/containers/mru_cache.h"
#include "base/files/file.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "components/nacl/browser/nacl_browser_delegate.h"
#include "components/nacl/browser/nacl_validation_cache.h"

class URLPattern;
class GURL;

namespace base {
class FileProxy;
}

namespace nacl {

static const int kGdbDebugStubPortUnknown = -1;
static const int kGdbDebugStubPortUnused = 0;

base::File OpenNaClReadExecImpl(const base::FilePath& file_path,
                                bool is_executable);

class NaClBrowser {
 public:
  static NaClBrowser* GetInstance();

  
  bool IsOk() const;

  
  bool IsReady() const;

  
  
  void EnsureAllResourcesAvailable();

  
  
  void WaitForResources(const base::Closure& reply);

  
  
  
  
  void EnsureIrtAvailable();

  
  const base::FilePath& GetIrtFilePath();

  
  const base::File& IrtFile() const;

  
  
  

  
  void SetProcessGdbDebugStubPort(int process_id, int port);
  void SetGdbDebugStubPortListener(base::Callback<void(int)> listener);
  void ClearGdbDebugStubPortListener();

  int GetProcessGdbDebugStubPort(int process_id);

  enum ValidationCacheStatus {
    CACHE_MISS = 0,
    CACHE_HIT,
    CACHE_MAX
  };

  bool ValidationCacheIsEnabled() const {
    return validation_cache_is_enabled_;
  }

  const std::string& GetValidationCacheKey() const {
    return validation_cache_.GetValidationCacheKey();
  }

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void PutFilePath(const base::FilePath& path, uint64* file_token_lo,
                   uint64* file_token_hi);
  bool GetFilePath(uint64 file_token_lo, uint64 file_token_hi,
                   base::FilePath* path);

  bool QueryKnownToValidate(const std::string& signature, bool off_the_record);
  void SetKnownToValidate(const std::string& signature, bool off_the_record);
  void ClearValidationCache(const base::Closure& callback);
#if defined(OS_WIN)
  
  
  bool GetNaCl64ExePath(base::FilePath* exe_path);
#endif

  void EarlyStartup();
  static void SetDelegate(NaClBrowserDelegate* delegate);
  static NaClBrowserDelegate* GetDelegate();

  
  void OnProcessEnd(int process_id);
  
  
  void OnProcessCrashed();
  
  
  bool IsThrottled();

 private:
  friend struct DefaultSingletonTraits<NaClBrowser>;

  enum NaClResourceState {
    NaClResourceUninitialized,
    NaClResourceRequested,
    NaClResourceReady
  };

  NaClBrowser();
  ~NaClBrowser();

  void InitIrtFilePath();

  void OpenIrtLibraryFile();

  void OnIrtOpened(scoped_ptr<base::FileProxy> file_proxy,
                   base::File::Error error_code);

  void InitValidationCacheFilePath();
  void EnsureValidationCacheAvailable();
  void OnValidationCacheLoaded(const std::string* data);
  void RunWithoutValidationCache();

  
  void CheckWaiting();

  
  void MarkAsFailed();

  void MarkValidationCacheAsModified();
  void PersistValidationCache();


  base::File irt_file_;
  base::FilePath irt_filepath_;
  NaClResourceState irt_state_;
  NaClValidationCache validation_cache_;
  NaClValidationCache off_the_record_validation_cache_;
  base::FilePath validation_cache_file_path_;
  bool validation_cache_is_enabled_;
  bool validation_cache_is_modified_;
  NaClResourceState validation_cache_state_;
  base::Callback<void(int)> debug_stub_port_listener_;

  
  typedef std::map<int, int> GdbDebugStubPortMap;
  GdbDebugStubPortMap gdb_debug_stub_port_map_;

  typedef base::HashingMRUCache<std::string, base::FilePath> PathCacheType;
  PathCacheType path_cache_;

  bool ok_;

  
  std::vector<base::Closure> waiting_;

  scoped_ptr<NaClBrowserDelegate> browser_delegate_;

  std::deque<base::Time> crash_times_;

  
  base::WeakPtrFactory<NaClBrowser> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(NaClBrowser);
};

} 

#endif  
