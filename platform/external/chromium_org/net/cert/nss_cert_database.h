// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_CERT_NSS_CERT_DATABASE_H_
#define NET_CERT_NSS_CERT_DATABASE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "crypto/scoped_nss_types.h"
#include "net/base/net_errors.h"
#include "net/base/net_export.h"
#include "net/cert/cert_type.h"
#include "net/cert/x509_certificate.h"

namespace base {
class TaskRunner;
}
template <class ObserverType> class ObserverListThreadSafe;

namespace net {

class CryptoModule;
typedef std::vector<scoped_refptr<CryptoModule> > CryptoModuleList;

class NET_EXPORT NSSCertDatabase {
 public:
  class NET_EXPORT Observer {
   public:
    virtual ~Observer() {}

    
    
    
    virtual void OnCertAdded(const X509Certificate* cert) {}

    
    virtual void OnCertRemoved(const X509Certificate* cert) {}

    
    
    
    virtual void OnCACertChanged(const X509Certificate* cert) {}

   protected:
    Observer() {}

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  
  struct NET_EXPORT ImportCertFailure {
   public:
    ImportCertFailure(const scoped_refptr<X509Certificate>& cert, int err);
    ~ImportCertFailure();

    scoped_refptr<X509Certificate> certificate;
    int net_error;
  };
  typedef std::vector<ImportCertFailure> ImportCertFailureList;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef uint32 TrustBits;
  enum {
    TRUST_DEFAULT         =      0,
    TRUSTED_SSL           = 1 << 0,
    TRUSTED_EMAIL         = 1 << 1,
    TRUSTED_OBJ_SIGN      = 1 << 2,
    DISTRUSTED_SSL        = 1 << 3,
    DISTRUSTED_EMAIL      = 1 << 4,
    DISTRUSTED_OBJ_SIGN   = 1 << 5,
  };

  typedef base::Callback<void(scoped_ptr<CertificateList> certs)>
      ListCertsCallback;

  typedef base::Callback<void(bool)> DeleteCertCallback;

  
  
  
  
  
  
  
  
  
  NSSCertDatabase(crypto::ScopedPK11Slot public_slot,
                  crypto::ScopedPK11Slot private_slot);
  virtual ~NSSCertDatabase();

  
  
  
  virtual void ListCertsSync(CertificateList* certs);

  
  
  
  virtual void ListCerts(const ListCertsCallback& callback);

  
  
  
  
  
  virtual void ListCertsInSlot(const ListCertsCallback& callback,
                               PK11SlotInfo* slot);

#if defined(OS_CHROMEOS)
  
  
  
  
  
  
  virtual crypto::ScopedPK11Slot GetSystemSlot() const;
#endif

  
  crypto::ScopedPK11Slot GetPublicSlot() const;

  
  
  crypto::ScopedPK11Slot GetPrivateSlot() const;

  
  
  
  
  CryptoModule* GetPublicModule() const;

  
  
  
  
  CryptoModule* GetPrivateModule() const;

  
  
  
  virtual void ListModules(CryptoModuleList* modules, bool need_rw) const;

  
  
  
  
  
  
  int ImportFromPKCS12(CryptoModule* module,
                       const std::string& data,
                       const base::string16& password,
                       bool is_extractable,
                       CertificateList* imported_certs);

  
  
  
  int ExportToPKCS12(const CertificateList& certs,
                     const base::string16& password,
                     std::string* output) const;

  
  
  
  
  X509Certificate* FindRootInList(const CertificateList& certificates) const;

  
  
  
  
  
  
  
  bool ImportCACerts(const CertificateList& certificates,
                     TrustBits trust_bits,
                     ImportCertFailureList* not_imported);

  
  
  
  
  
  
  
  
  
  
  bool ImportServerCert(const CertificateList& certificates,
                        TrustBits trust_bits,
                        ImportCertFailureList* not_imported);

  
  TrustBits GetCertTrust(const X509Certificate* cert, CertType type) const;

  
  
  
  bool IsUntrusted(const X509Certificate* cert) const;

  
  
  bool SetCertTrust(const X509Certificate* cert,
                    CertType type,
                    TrustBits trust_bits);

  
  
  
  bool DeleteCertAndKey(X509Certificate* cert);

  
  
  
  void DeleteCertAndKeyAsync(const scoped_refptr<X509Certificate>& cert,
                             const DeleteCertCallback& callback);

  
  bool IsReadOnly(const X509Certificate* cert) const;

  
  bool IsHardwareBacked(const X509Certificate* cert) const;

  
  void SetSlowTaskRunnerForTest(
      const scoped_refptr<base::TaskRunner>& task_runner);

 protected:
  
  
  
  
  static void ListCertsImpl(crypto::ScopedPK11Slot slot,
                            CertificateList* certs);

  
  
  
  scoped_refptr<base::TaskRunner> GetSlowTaskRunner() const;

 private:
  
  
  
  
  
  
  void AddObserver(Observer* observer);

  
  
  void RemoveObserver(Observer* observer);

  
  
  void NotifyCertRemovalAndCallBack(scoped_refptr<X509Certificate> cert,
                                    const DeleteCertCallback& callback,
                                    bool success);

  
  void NotifyObserversOfCertAdded(const X509Certificate* cert);
  void NotifyObserversOfCertRemoved(const X509Certificate* cert);
  void NotifyObserversOfCACertChanged(const X509Certificate* cert);

  
  
  static bool DeleteCertAndKeyImpl(scoped_refptr<X509Certificate> cert);

  crypto::ScopedPK11Slot public_slot_;
  crypto::ScopedPK11Slot private_slot_;

  
  scoped_ptr<Observer> cert_notification_forwarder_;

  
  scoped_refptr<base::TaskRunner> slow_task_runner_for_test_;

  const scoped_refptr<ObserverListThreadSafe<Observer> > observer_list_;

  base::WeakPtrFactory<NSSCertDatabase> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(NSSCertDatabase);
};

}  

#endif  
