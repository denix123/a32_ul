// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_PEPPER_QUOTA_RESERVATION_H_
#define CONTENT_BROWSER_RENDERER_HOST_PEPPER_QUOTA_RESERVATION_H_

#include <map>

#include "base/basictypes.h"
#include "base/callback.h"
#include "content/common/content_export.h"
#include "ppapi/c/pp_stdint.h"  
#include "ppapi/shared_impl/file_growth.h"
#include "storage/browser/fileapi/file_system_context.h"
#include "url/gurl.h"

namespace storage {
class FileSystemURL;
class OpenFileHandle;
class QuotaReservation;
}

namespace content {

struct QuotaReservationDeleter;

class CONTENT_EXPORT QuotaReservation
    : public base::RefCountedThreadSafe<QuotaReservation,
                                        QuotaReservationDeleter> {
 public:
  
  static scoped_refptr<QuotaReservation> Create(
      scoped_refptr<storage::FileSystemContext> file_system_context,
      const GURL& origin_url,
      storage::FileSystemType file_system_type);

  
  int64_t OpenFile(int32_t id, const storage::FileSystemURL& url);
  
  void CloseFile(int32_t id, const ppapi::FileGrowth& file_growth);
  
  // ids with maximum written offsets is provided as input. The callback will
  
  typedef base::Callback<void(int64_t, const ppapi::FileSizeMap&)>
      ReserveQuotaCallback;
  void ReserveQuota(int64_t amount,
                    const ppapi::FileGrowthMap& file_growth,
                    const ReserveQuotaCallback& callback);

  
  
  void OnClientCrash();

 private:
  friend class base::RefCountedThreadSafe<QuotaReservation,
                                          QuotaReservationDeleter>;
  friend class base::DeleteHelper<QuotaReservation>;
  friend struct QuotaReservationDeleter;
  friend class QuotaReservationTest;

  QuotaReservation(
      scoped_refptr<storage::FileSystemContext> file_system_context,
      const GURL& origin_url,
      storage::FileSystemType file_system_type);

  
  
  QuotaReservation(scoped_refptr<storage::QuotaReservation> quota_reservation,
                   const GURL& origin_url,
                   storage::FileSystemType file_system_type);

  ~QuotaReservation();

  void GotReservedQuota(const ReserveQuotaCallback& callback,
                        base::File::Error error);

  void DeleteOnCorrectThread() const;

  scoped_refptr<storage::FileSystemContext> file_system_context_;
  scoped_refptr<storage::QuotaReservation> quota_reservation_;
  typedef std::map<int32_t, storage::OpenFileHandle*> FileMap;
  FileMap files_;

  DISALLOW_COPY_AND_ASSIGN(QuotaReservation);
};

struct QuotaReservationDeleter {
  static void Destruct(const QuotaReservation* quota_reservation) {
    quota_reservation->DeleteOnCorrectThread();
  }
};

}  

#endif  
