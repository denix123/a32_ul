// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_CERT_NSS_CERT_DATABASE_CHROMEOS_
#define NET_CERT_NSS_CERT_DATABASE_CHROMEOS_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "crypto/scoped_nss_types.h"
#include "net/base/net_export.h"
#include "net/cert/nss_cert_database.h"
#include "net/cert/nss_profile_filter_chromeos.h"

namespace net {

class NET_EXPORT NSSCertDatabaseChromeOS : public NSSCertDatabase {
 public:
  NSSCertDatabaseChromeOS(crypto::ScopedPK11Slot public_slot,
                          crypto::ScopedPK11Slot private_slot);
  virtual ~NSSCertDatabaseChromeOS();

  
  
  void SetSystemSlot(crypto::ScopedPK11Slot system_slot);

  
  virtual void ListCertsSync(CertificateList* certs) OVERRIDE;
  virtual void ListCerts(const NSSCertDatabase::ListCertsCallback& callback)
      OVERRIDE;
  virtual void ListModules(CryptoModuleList* modules, bool need_rw) const
      OVERRIDE;
  virtual crypto::ScopedPK11Slot GetSystemSlot() const OVERRIDE;

  
  
  

 private:
  
  
  
  
  static void ListCertsImpl(const NSSProfileFilterChromeOS& profile_filter,
                            CertificateList* certs);

  NSSProfileFilterChromeOS profile_filter_;
  crypto::ScopedPK11Slot system_slot_;

  DISALLOW_COPY_AND_ASSIGN(NSSCertDatabaseChromeOS);
};

}  

#endif  
