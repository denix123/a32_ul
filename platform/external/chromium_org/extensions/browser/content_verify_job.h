// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_CONTENT_VERIFY_JOB_H_
#define EXTENSIONS_BROWSER_CONTENT_VERIFY_JOB_H_

#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"

namespace base {
class FilePath;
}

namespace crypto {
class SecureHash;
}

namespace extensions {

class ContentHashReader;

class ContentVerifyJob : public base::RefCountedThreadSafe<ContentVerifyJob> {
 public:
  enum FailureReason {
    
    NONE,

    
    
    MISSING_ALL_HASHES,

    
    NO_HASHES_FOR_FILE,

    
    HASH_MISMATCH,

    FAILURE_REASON_MAX
  };
  typedef base::Callback<void(FailureReason)> FailureCallback;

  
  ContentVerifyJob(ContentHashReader* hash_reader,
                   const FailureCallback& failure_callback);

  
  
  void Start();

  
  
  
  
  
  
  void BytesRead(int count, const char* data);

  
  void DoneReading();

  class TestDelegate {
   public:
    
    
    
    virtual FailureReason BytesRead(const std::string& extension_id,
                                    int count,
                                    const char* data) = 0;
    virtual FailureReason DoneReading(const std::string& extension_id) = 0;
  };

  class TestObserver {
   public:
    virtual void JobStarted(const std::string& extension_id,
                            const base::FilePath& relative_path) = 0;

    virtual void JobFinished(const std::string& extension_id,
                             const base::FilePath& relative_path,
                             bool failed) = 0;
  };

  static void SetDelegateForTests(TestDelegate* delegate);
  static void SetObserverForTests(TestObserver* observer);

 private:
  DISALLOW_COPY_AND_ASSIGN(ContentVerifyJob);

  virtual ~ContentVerifyJob();
  friend class base::RefCountedThreadSafe<ContentVerifyJob>;

  
  
  
  
  bool FinishBlock();

  
  void DispatchFailureCallback(FailureReason reason);

  
  void OnHashesReady(bool success);

  
  bool done_reading_;

  
  bool hashes_ready_;

  
  
  std::string queue_;

  
  int64 total_bytes_read_;

  
  int current_block_;

  
  scoped_ptr<crypto::SecureHash> current_hash_;

  
  int current_hash_byte_count_;

  scoped_refptr<ContentHashReader> hash_reader_;

  base::TimeDelta time_spent_;

  
  FailureCallback failure_callback_;

  
  bool failed_;

  
  base::ThreadChecker thread_checker_;
};

}  

#endif  
