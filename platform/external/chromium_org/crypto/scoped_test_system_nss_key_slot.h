// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_SCOPED_TEST_SYSTEM_NSS_KEY_SLOT_H_
#define CRYPTO_SCOPED_TEST_SYSTEM_NSS_KEY_SLOT_H_

#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "crypto/crypto_export.h"

typedef struct PK11SlotInfoStr PK11SlotInfo;

namespace crypto {

class ScopedTestNSSDB;

class CRYPTO_EXPORT_PRIVATE ScopedTestSystemNSSKeySlot {
 public:
  explicit ScopedTestSystemNSSKeySlot();
  ~ScopedTestSystemNSSKeySlot();

  bool ConstructedSuccessfully() const;
  PK11SlotInfo* slot() const;

 private:
  scoped_ptr<ScopedTestNSSDB> test_db_;

  DISALLOW_COPY_AND_ASSIGN(ScopedTestSystemNSSKeySlot);
};

}  

#endif  
