// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_PLATFORM_KEYS_PLATFORM_KEYS_SERVICE_H_
#define CHROME_BROWSER_CHROMEOS_PLATFORM_KEYS_PLATFORM_KEYS_SERVICE_H_

#include <string>

#include "base/callback_forward.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/platform_keys/platform_keys.h"
#include "components/keyed_service/core/keyed_service.h"

namespace content {
class BrowserContext;
}

namespace base {
class ListValue;
class Value;
}

namespace extensions {
class StateStore;
}

namespace chromeos {

class PlatformKeysService : public KeyedService {
 public:
  
  
  
  // The format written to |state_store| is:
  
  
  
  explicit PlatformKeysService(content::BrowserContext* browser_context,
                               extensions::StateStore* state_store);
  virtual ~PlatformKeysService();

  
  
  
  
  typedef base::Callback<void(const std::string& public_key_spki_der,
                              const std::string& error_message)>
      GenerateKeyCallback;

  
  
  
  
  
  
  void GenerateRSAKey(const std::string& token_id,
                      unsigned int modulus_length_bits,
                      const std::string& extension_id,
                      const GenerateKeyCallback& callback);

  
  
  
  typedef base::Callback<void(const std::string& signature,
                              const std::string& error_message)> SignCallback;

  
  
  
  
  
  
  
  
  
  
  void Sign(const std::string& token_id,
            const std::string& public_key_spki_der,
            platform_keys::HashAlgorithm hash_algorithm,
            const std::string& data,
            const std::string& extension_id,
            const SignCallback& callback);

 private:
  typedef base::Callback<void(scoped_ptr<base::ListValue> platform_keys)>
      GetPlatformKeysCallback;

  
  
  
  
  void RegisterPublicKey(const std::string& extension_id,
                         const std::string& public_key_spki_der,
                         const base::Callback<void(bool)>& callback);

  
  
  
  void ReadValidityAndInvalidateKey(const std::string& extension_id,
                                    const std::string& public_key_spki_der,
                                    const base::Callback<void(bool)>& callback);

  
  
  
  void GetPlatformKeysOfExtension(const std::string& extension_id,
                                  const GetPlatformKeysCallback& callback);

  
  
  
  
  
  void GenerateRSAKeyCallback(const std::string& extension_id,
                              const GenerateKeyCallback& callback,
                              const std::string& public_key_spki_der,
                              const std::string& error_message);

  
  
  
  void RegisterPublicKeyGotPlatformKeys(
      const std::string& extension_id,
      const std::string& public_key_spki_der,
      const base::Callback<void(bool)>& callback,
      scoped_ptr<base::ListValue> platform_keys);

  
  
  
  void InvalidateKey(const std::string& extension_id,
                     const std::string& public_key_spki_der,
                     const base::Callback<void(bool)>& callback,
                     scoped_ptr<base::ListValue> platform_keys);

  
  
  
  
  void GotPlatformKeysOfExtension(const std::string& extension_id,
                                  const GetPlatformKeysCallback& callback,
                                  scoped_ptr<base::Value> value);

  content::BrowserContext* browser_context_;
  extensions::StateStore* state_store_;
  base::WeakPtrFactory<PlatformKeysService> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(PlatformKeysService);
};

}  

#endif  
