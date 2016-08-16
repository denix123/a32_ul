// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_METRICS_VARIATIONS_VARIATIONS_SEED_STORE_H_
#define CHROME_BROWSER_METRICS_VARIATIONS_VARIATIONS_SEED_STORE_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/time/time.h"

class PrefService;
class PrefRegistrySimple;

namespace variations {
class VariationsSeed;
}

namespace chrome_variations {

class VariationsSeedStore {
 public:
  explicit VariationsSeedStore(PrefService* local_state);
  virtual ~VariationsSeedStore();

  
  
  
  bool LoadSeed(variations::VariationsSeed* seed);

  
  
  
  
  
  
  bool StoreSeedData(const std::string& seed_data,
                     const std::string& base64_seed_signature,
                     const base::Time& date_fetched,
                     variations::VariationsSeed* parsed_seed);

  
  
  void UpdateSeedDateAndLogDayChange(const base::Time& server_date_fetched);

  
  const std::string& variations_serial_number() const {
    return variations_serial_number_;
  }

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 protected:
  
  enum VerifySignatureResult {
    VARIATIONS_SEED_SIGNATURE_MISSING,
    VARIATIONS_SEED_SIGNATURE_DECODE_FAILED,
    VARIATIONS_SEED_SIGNATURE_INVALID_SIGNATURE,
    VARIATIONS_SEED_SIGNATURE_INVALID_SEED,
    VARIATIONS_SEED_SIGNATURE_VALID,
    VARIATIONS_SEED_SIGNATURE_ENUM_SIZE,
  };

  
  
  
  
  
  
  virtual VariationsSeedStore::VerifySignatureResult VerifySeedSignature(
      const std::string& seed_bytes,
      const std::string& base64_seed_signature);

 private:
  FRIEND_TEST_ALL_PREFIXES(VariationsSeedStoreTest, VerifySeedSignature);

  
  void ClearPrefs();

  
  PrefService* local_state_;

  
  std::string variations_serial_number_;

  DISALLOW_COPY_AND_ASSIGN(VariationsSeedStore);
};

}  

#endif  
