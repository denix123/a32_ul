// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_SCOPED_TEST_NSS_DB_H_
#define CRYPTO_SCOPED_TEST_NSS_DB_H_

#include "base/files/scoped_temp_dir.h"
#include "base/macros.h"
#include "crypto/crypto_export.h"
#include "crypto/scoped_nss_types.h"

namespace crypto {

class CRYPTO_EXPORT_PRIVATE ScopedTestNSSDB {
 public:
  ScopedTestNSSDB();
  ~ScopedTestNSSDB();

  bool is_open() const { return slot_; }
  PK11SlotInfo* slot() const { return slot_.get(); }

 private:
  base::ScopedTempDir temp_dir_;
  ScopedPK11Slot slot_;

  DISALLOW_COPY_AND_ASSIGN(ScopedTestNSSDB);
};

}  

#endif  
