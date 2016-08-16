// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CERTIFICATE_MANAGER_MODEL_H_
#define CHROME_BROWSER_CERTIFICATE_MANAGER_MODEL_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string16.h"
#include "net/cert/nss_cert_database.h"

namespace content {
class BrowserContext;
class ResourceContext;
}  

class CertificateManagerModel {
 public:
  
  
  
  typedef std::map<std::string, net::CertificateList> OrgGroupingMap;

  typedef base::Callback<void(scoped_ptr<CertificateManagerModel>)>
      CreationCallback;

  
  enum Column {
    COL_SUBJECT_NAME,
    COL_CERTIFICATE_STORE,
    COL_SERIAL_NUMBER,
    COL_EXPIRES_ON,
  };

  class Observer {
   public:
    
    
    
    virtual void CertificatesRefreshed() = 0;
  };

  
  
  
  static void Create(content::BrowserContext* browser_context,
                     Observer* observer,
                     const CreationCallback& callback);

  ~CertificateManagerModel();

  bool is_user_db_available() const { return is_user_db_available_; }
  bool is_tpm_available() const { return is_tpm_available_; }

  
  const net::NSSCertDatabase* cert_db() const { return cert_db_; }

  
  
  
  
  void Refresh();

  
  void FilterAndBuildOrgGroupingMap(net::CertType filter_type,
                                    OrgGroupingMap* map) const;

  
  base::string16 GetColumnText(const net::X509Certificate& cert, Column column) const;

  
  
  
  
  int ImportFromPKCS12(net::CryptoModule* module, const std::string& data,
                       const base::string16& password, bool is_extractable);

  
  
  
  
  
  
  
  
  bool ImportCACerts(const net::CertificateList& certificates,
                     net::NSSCertDatabase::TrustBits trust_bits,
                     net::NSSCertDatabase::ImportCertFailureList* not_imported);

  
  
  
  
  
  
  
  
  
  
  bool ImportServerCert(
      const net::CertificateList& certificates,
      net::NSSCertDatabase::TrustBits trust_bits,
      net::NSSCertDatabase::ImportCertFailureList* not_imported);

  
  
  
  bool SetCertTrust(const net::X509Certificate* cert,
                    net::CertType type,
                    net::NSSCertDatabase::TrustBits trust_bits);

  
  
  bool Delete(net::X509Certificate* cert);

  
  bool IsHardwareBacked(const net::X509Certificate* cert) const;

 private:
  CertificateManagerModel(net::NSSCertDatabase* nss_cert_database,
                          bool is_user_db_available,
                          bool is_tpm_available,
                          Observer* observer);

  
  
  static void DidGetCertDBOnUIThread(
      net::NSSCertDatabase* cert_db,
      bool is_user_db_available,
      bool is_tpm_available,
      CertificateManagerModel::Observer* observer,
      const CreationCallback& callback);
  static void DidGetCertDBOnIOThread(
      CertificateManagerModel::Observer* observer,
      const CreationCallback& callback,
      net::NSSCertDatabase* cert_db);
  static void GetCertDBOnIOThread(content::ResourceContext* context,
                                  CertificateManagerModel::Observer* observer,
                                  const CreationCallback& callback);

  
  
  void RefreshSlotsUnlocked();

  net::NSSCertDatabase* cert_db_;
  net::CertificateList cert_list_;
  
  
  bool is_user_db_available_;
  bool is_tpm_available_;

  
  Observer* observer_;

  DISALLOW_COPY_AND_ASSIGN(CertificateManagerModel);
};

#endif  