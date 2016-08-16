// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_QUOTA_OPEN_FILE_HANDLE_H_
#define STORAGE_BROWSER_FILEAPI_QUOTA_OPEN_FILE_HANDLE_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/storage_browser_export.h"

namespace base {
class FilePath;
}

namespace storage {

class QuotaReservation;
class OpenFileHandleContext;
class QuotaReservationBuffer;

class STORAGE_EXPORT OpenFileHandle {
 public:
  ~OpenFileHandle();

  
  
  
  
  void UpdateMaxWrittenOffset(int64 offset);

  // Notifies that |amount| of data is written to the file in append mode, and
  
  // Both this and UpdateMaxWrittenOffset should be called for each modified
  
  
  void AddAppendModeWriteAmount(int64 amount);

  
  
  
  
  
  
  int64 GetEstimatedFileSize() const;

  int64 GetMaxWrittenOffset() const;
  const base::FilePath& platform_path() const;

 private:
  friend class QuotaReservationBuffer;

  OpenFileHandle(QuotaReservation* reservation,
                 OpenFileHandleContext* context);

  scoped_refptr<QuotaReservation> reservation_;
  scoped_refptr<OpenFileHandleContext> context_;

  base::SequenceChecker sequence_checker_;

  DISALLOW_COPY_AND_ASSIGN(OpenFileHandle);
};

}  

#endif  
