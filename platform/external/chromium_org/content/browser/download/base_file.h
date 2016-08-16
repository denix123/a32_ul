// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DOWNLOAD_BASE_FILE_H_
#define CONTENT_BROWSER_DOWNLOAD_BASE_FILE_H_

#include <string>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/logging.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/public/browser/download_interrupt_reasons.h"
#include "crypto/sha2.h"
#include "net/base/net_errors.h"
#include "net/base/net_log.h"
#include "url/gurl.h"

namespace crypto {
class SecureHash;
}

namespace content {

class CONTENT_EXPORT BaseFile {
 public:
  
  
  BaseFile(const base::FilePath& full_path,
           const GURL& source_url,
           const GURL& referrer_url,
           int64 received_bytes,
           bool calculate_hash,
           const std::string& hash_state,
           base::File file,
           const net::BoundNetLog& bound_net_log);
  virtual ~BaseFile();

  
  
  
  
  
  
  DownloadInterruptReason Initialize(const base::FilePath& default_directory);

  
  
  DownloadInterruptReason AppendDataToFile(const char* data, size_t data_len);

  
  
  
  
  
  virtual DownloadInterruptReason Rename(const base::FilePath& full_path);

  
  virtual void Detach();

  
  void Cancel();

  
  void Finish();

  
  
  
  void SetClientGuid(const std::string& guid);

  
  
  
  
  DownloadInterruptReason AnnotateWithSourceInformation();

  
  
  const base::FilePath& full_path() const { return full_path_; }

  // Returns true if the file is open. If true, the file can be written to or
  
  bool in_progress() const { return file_.IsValid(); }

  
  int64 bytes_so_far() const { return bytes_so_far_; }

  
  
  virtual bool GetHash(std::string* hash);

  
  virtual std::string GetHashState();

  
  
  
  static bool IsEmptyHash(const std::string& hash);

  virtual std::string DebugString() const;

 private:
  friend class BaseFileTest;
  FRIEND_TEST_ALL_PREFIXES(BaseFileTest, IsEmptyHash);

  
  DownloadInterruptReason Open();

  
  void Close();

  
  void ClearFile();

  
  
  
  DownloadInterruptReason MoveFileAndAdjustPermissions(
      const base::FilePath& new_path);

  
  int64 CurrentSpeedAtTime(base::TimeTicks current_time) const;

  
  
  DownloadInterruptReason LogNetError(const char* operation, net::Error error);

  
  
  DownloadInterruptReason LogSystemError(const char* operation,
                                         logging::SystemErrorCode os_error);

  
  
  DownloadInterruptReason LogInterruptReason(
      const char* operation, int os_error,
      DownloadInterruptReason reason);

  static const unsigned char kEmptySha256Hash[crypto::kSHA256Length];

  
  base::FilePath full_path_;

  
  GURL source_url_;

  
  GURL referrer_url_;

  std::string client_guid_;

  
  base::File file_;

  
  int64 bytes_so_far_;

  
  base::TimeTicks start_tick_;

  
  bool calculate_hash_;

  
  
  scoped_ptr<crypto::SecureHash> secure_hash_;

  unsigned char sha256_hash_[crypto::kSHA256Length];

  
  
  bool detached_;

  net::BoundNetLog bound_net_log_;

  DISALLOW_COPY_AND_ASSIGN(BaseFile);
};

}  

#endif  
