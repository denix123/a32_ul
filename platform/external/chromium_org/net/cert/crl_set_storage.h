// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_CERT_CRL_SET_STORAGE_H_
#define NET_CERT_CRL_SET_STORAGE_H_

#include <string>
#include <utility>
#include <vector>

#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/cert/crl_set.h"

namespace base {
class DictionaryValue;
}

namespace net {

class NET_EXPORT CRLSetStorage {
 public:
  
  
  static bool Parse(base::StringPiece data,
                    scoped_refptr<CRLSet>* out_crl_set);

  
  
  static bool ApplyDelta(const CRLSet* in_crl_set,
                         const base::StringPiece& delta_bytes,
                         scoped_refptr<CRLSet>* out_crl_set);

  
  
  
  static bool GetIsDeltaUpdate(const base::StringPiece& bytes, bool *is_delta);

  
  
  
  static std::string Serialize(const CRLSet* crl_set);

 private:
  
  
  static bool CopyBlockedSPKIsFromHeader(CRLSet* crl_set,
                                         base::DictionaryValue* header_dict);
};

}  

#endif  
