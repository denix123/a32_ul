// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_EASY_UNLOCK_PRIVATE_EASY_UNLOCK_PRIVATE_CRYPTO_DELEGATE_H_
#define CHROME_BROWSER_EXTENSIONS_API_EASY_UNLOCK_PRIVATE_EASY_UNLOCK_PRIVATE_CRYPTO_DELEGATE_H_

#include <string>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/common/extensions/api/easy_unlock_private.h"

namespace extensions {
namespace api {

class EasyUnlockPrivateCryptoDelegate {
 public:
  typedef base::Callback<void(const std::string& data)> DataCallback;

  typedef base::Callback<void(const std::string& public_key,
                              const std::string& private_key)>
      KeyPairCallback;

  virtual ~EasyUnlockPrivateCryptoDelegate() {}

  
  
  static scoped_ptr<EasyUnlockPrivateCryptoDelegate> Create();

  
  virtual void GenerateEcP256KeyPair(const KeyPairCallback& callback) = 0;
  virtual void PerformECDHKeyAgreement(
      const easy_unlock_private::PerformECDHKeyAgreement::Params& params,
      const DataCallback& callback) = 0;
  virtual void CreateSecureMessage(
      const easy_unlock_private::CreateSecureMessage::Params& params,
      const DataCallback& callback) = 0;
  virtual void UnwrapSecureMessage(
      const easy_unlock_private::UnwrapSecureMessage::Params& params,
      const DataCallback& callback) = 0;
};

}  
}  

#endif  
