// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_NSS_UTIL_INTERNAL_H_
#define CRYPTO_NSS_UTIL_INTERNAL_H_

#include <secmodt.h>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "crypto/crypto_export.h"
#include "crypto/scoped_nss_types.h"

namespace base {
class FilePath;
}


namespace crypto {

CRYPTO_EXPORT_PRIVATE ScopedPK11Slot
    OpenSoftwareNSSDB(const base::FilePath& path,
                      const std::string& description);

#if !defined(OS_CHROMEOS)
CRYPTO_EXPORT PK11SlotInfo* GetPersistentNSSKeySlot() WARN_UNUSED_RESULT;
#endif

class CRYPTO_EXPORT AutoSECMODListReadLock {
 public:
  AutoSECMODListReadLock();
  ~AutoSECMODListReadLock();

 private:
  SECMODListLock* lock_;
  DISALLOW_COPY_AND_ASSIGN(AutoSECMODListReadLock);
};

#if defined(OS_CHROMEOS)
CRYPTO_EXPORT ScopedPK11Slot GetSystemNSSKeySlot(
    const base::Callback<void(ScopedPK11Slot)>& callback) WARN_UNUSED_RESULT;

CRYPTO_EXPORT_PRIVATE void SetSystemKeySlotForTesting(ScopedPK11Slot slot);

CRYPTO_EXPORT bool InitializeNSSForChromeOSUser(
    const std::string& username_hash,
    const base::FilePath& path);

CRYPTO_EXPORT bool ShouldInitializeTPMForChromeOSUser(
    const std::string& username_hash) WARN_UNUSED_RESULT;

CRYPTO_EXPORT void WillInitializeTPMForChromeOSUser(
    const std::string& username_hash);

CRYPTO_EXPORT void InitializeTPMForChromeOSUser(
    const std::string& username_hash,
    CK_SLOT_ID slot_id);

CRYPTO_EXPORT void InitializePrivateSoftwareSlotForChromeOSUser(
    const std::string& username_hash);

CRYPTO_EXPORT ScopedPK11Slot GetPublicSlotForChromeOSUser(
    const std::string& username_hash) WARN_UNUSED_RESULT;

CRYPTO_EXPORT ScopedPK11Slot GetPrivateSlotForChromeOSUser(
    const std::string& username_hash,
    const base::Callback<void(ScopedPK11Slot)>& callback) WARN_UNUSED_RESULT;

CRYPTO_EXPORT_PRIVATE void CloseChromeOSUserForTesting(
    const std::string& username_hash);
#endif  

}  

#endif  
