// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_QUOTA_QUOTA_RESERVATION_H_
#define STORAGE_BROWSER_FILEAPI_QUOTA_QUOTA_RESERVATION_H_

#include "base/basictypes.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/quota/quota_reservation_manager.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/fileapi/file_system_types.h"

class GURL;

namespace storage {

class QuotaReservationBuffer;
class OpenFileHandle;

class STORAGE_EXPORT QuotaReservation
    : public base::RefCounted<QuotaReservation> {
 public:
  typedef base::Callback<void(base::File::Error error)> StatusCallback;

  
  
  
  
  
  void RefreshReservation(int64 size, const StatusCallback& callback);

  
  
  scoped_ptr<OpenFileHandle> GetOpenFileHandle(
      const base::FilePath& platform_path);

  
  
  
  
  
  
  void OnClientCrash();

  
  
  void ConsumeReservation(int64 size);

  
  int64 remaining_quota() const { return remaining_quota_; }

  QuotaReservationManager* reservation_manager();
  const GURL& origin() const;
  FileSystemType type() const;

 private:
  friend class QuotaReservationBuffer;

  
  explicit QuotaReservation(QuotaReservationBuffer* reservation_buffer);

  friend class base::RefCounted<QuotaReservation>;
  virtual ~QuotaReservation();

  static bool AdaptDidUpdateReservedQuota(
      const base::WeakPtr<QuotaReservation>& reservation,
      int64 previous_size,
      const StatusCallback& callback,
      base::File::Error error,
      int64 delta);
  bool DidUpdateReservedQuota(int64 previous_size,
                              const StatusCallback& callback,
                              base::File::Error error,
                              int64 delta);

  bool client_crashed_;
  bool running_refresh_request_;
  int64 remaining_quota_;

  scoped_refptr<QuotaReservationBuffer> reservation_buffer_;

  base::SequenceChecker sequence_checker_;
  base::WeakPtrFactory<QuotaReservation> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(QuotaReservation);
};

}  

#endif  
