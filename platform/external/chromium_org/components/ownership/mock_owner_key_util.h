// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_OWNERSHIP_MOCK_OWNER_KEY_UTIL_H_
#define COMPONENTS_OWNERSHIP_MOCK_OWNER_KEY_UTIL_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "components/ownership/owner_key_util.h"
#include "components/ownership/ownership_export.h"

namespace ownership {

class OWNERSHIP_EXPORT MockOwnerKeyUtil : public OwnerKeyUtil {
 public:
  MockOwnerKeyUtil();

  
  virtual bool ImportPublicKey(std::vector<uint8>* output) OVERRIDE;
#if defined(USE_NSS)
  virtual crypto::RSAPrivateKey* FindPrivateKeyInSlot(
      const std::vector<uint8>& key,
      PK11SlotInfo* slot) OVERRIDE;
#endif  
  virtual bool IsPublicKeyPresent() OVERRIDE;

  
  void Clear();

  
  void SetPublicKey(const std::vector<uint8>& key);

  
  
  void SetPublicKeyFromPrivateKey(const crypto::RSAPrivateKey& key);

  
  void SetPrivateKey(scoped_ptr<crypto::RSAPrivateKey> key);

 private:
  virtual ~MockOwnerKeyUtil();

  std::vector<uint8> public_key_;
  scoped_ptr<crypto::RSAPrivateKey> private_key_;

  DISALLOW_COPY_AND_ASSIGN(MockOwnerKeyUtil);
};

}  

#endif  
