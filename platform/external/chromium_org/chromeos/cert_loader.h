// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_CERT_LOADER_H_
#define CHROMEOS_CERT_LOADER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/threading/thread_checker.h"
#include "chromeos/chromeos_export.h"
#include "net/cert/cert_database.h"

namespace net {
class NSSCertDatabase;
class X509Certificate;
typedef std::vector<scoped_refptr<X509Certificate> > CertificateList;
}

namespace chromeos {

class CHROMEOS_EXPORT CertLoader : public net::CertDatabase::Observer {
 public:
  class Observer {
   public:
    
    
    
    virtual void OnCertificatesLoaded(const net::CertificateList& cert_list,
                                      bool initial_load) = 0;

   protected:
    virtual ~Observer() {}
  };

  
  static void Initialize();

  
  static void Shutdown();

  
  static CertLoader* Get();

  
  static bool IsInitialized();

  
  
  
  
  static std::string GetPkcs11IdAndSlotForCert(const net::X509Certificate& cert,
                                               int* slot_id);

  
  
  
  
  
  void StartWithNSSDB(net::NSSCertDatabase* database);

  void AddObserver(CertLoader::Observer* observer);
  void RemoveObserver(CertLoader::Observer* observer);

  bool IsHardwareBacked() const;

  
  
  
  bool IsCertificateHardwareBacked(const net::X509Certificate* cert) const;

  
  bool CertificatesLoading() const;

  bool certificates_loaded() const { return certificates_loaded_; }

  
  const net::CertificateList& cert_list() const { return *cert_list_; }

  void force_hardware_backed_for_test() {
    force_hardware_backed_for_test_ = true;
  }

 private:
  CertLoader();
  virtual ~CertLoader();

  
  
  void LoadCertificates();

  
  void UpdateCertificates(scoped_ptr<net::CertificateList> cert_list);

  void NotifyCertificatesLoaded(bool initial_load);

  
  virtual void OnCACertChanged(const net::X509Certificate* cert) OVERRIDE;
  virtual void OnCertAdded(const net::X509Certificate* cert) OVERRIDE;
  virtual void OnCertRemoved(const net::X509Certificate* cert) OVERRIDE;

  ObserverList<Observer> observers_;

  
  bool certificates_loaded_;
  bool certificates_update_required_;
  bool certificates_update_running_;

  
  
  net::NSSCertDatabase* database_;

  
  bool force_hardware_backed_for_test_;

  
  scoped_ptr<net::CertificateList> cert_list_;

  base::ThreadChecker thread_checker_;

  base::WeakPtrFactory<CertLoader> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CertLoader);
};

}  

#endif  
