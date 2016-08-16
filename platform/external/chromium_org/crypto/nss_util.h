// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRYPTO_NSS_UTIL_H_
#define CRYPTO_NSS_UTIL_H_

#include <string>
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "crypto/crypto_export.h"

namespace base {
class FilePath;
class Lock;
class Time;
}  

namespace crypto {

#if defined(USE_NSS)
CRYPTO_EXPORT void EarlySetupForNSSInit();
#endif

CRYPTO_EXPORT void EnsureNSPRInit();

CRYPTO_EXPORT void InitNSSSafely();

CRYPTO_EXPORT void EnsureNSSInit();

CRYPTO_EXPORT void ForceNSSNoDBInit();

CRYPTO_EXPORT void DisableNSSForkCheck();

CRYPTO_EXPORT void LoadNSSLibraries();

bool CheckNSSVersion(const char* version);

#if defined(OS_CHROMEOS)
CRYPTO_EXPORT void EnableTPMTokenForNSS();

CRYPTO_EXPORT bool IsTPMTokenEnabledForNSS();

CRYPTO_EXPORT bool IsTPMTokenReady(const base::Closure& callback)
    WARN_UNUSED_RESULT;

CRYPTO_EXPORT void InitializeTPMTokenAndSystemSlot(
    int system_slot_id,
    const base::Callback<void(bool)>& callback);
#endif

CRYPTO_EXPORT base::Time PRTimeToBaseTime(int64 prtime);

CRYPTO_EXPORT int64 BaseTimeToPRTime(base::Time time);

#if defined(USE_NSS)
base::Lock* GetNSSWriteLock();

class CRYPTO_EXPORT AutoNSSWriteLock {
 public:
  AutoNSSWriteLock();
  ~AutoNSSWriteLock();
 private:
  base::Lock *lock_;
  DISALLOW_COPY_AND_ASSIGN(AutoNSSWriteLock);
};
#endif  

}  

#endif  
