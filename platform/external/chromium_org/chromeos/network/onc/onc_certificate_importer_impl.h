// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_ONC_ONC_CERTIFICATE_IMPORTER_IMPL_H_
#define CHROMEOS_NETWORK_ONC_ONC_CERTIFICATE_IMPORTER_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/network/onc/onc_certificate_importer.h"
#include "components/onc/onc_constants.h"

namespace base {
class DictionaryValue;
class ListValue;
class SequencedTaskRunner;
class SingleThreadTaskRunner;
}

namespace net {
class NSSCertDatabase;
class X509Certificate;
typedef std::vector<scoped_refptr<X509Certificate> > CertificateList;
}

namespace chromeos {
namespace onc {

class CHROMEOS_EXPORT CertificateImporterImpl : public CertificateImporter {
 public:
  
  CertificateImporterImpl(
      const scoped_refptr<base::SequencedTaskRunner>& io_task_runner,
      net::NSSCertDatabase* target_nssdb_);
  virtual ~CertificateImporterImpl();

  
  virtual void ImportCertificates(const base::ListValue& certificates,
                                  ::onc::ONCSource source,
                                  const DoneCallback& done_callback) OVERRIDE;

 private:
  void RunDoneCallback(const CertificateImporter::DoneCallback& callback,
                       bool success,
                       const net::CertificateList& onc_trusted_certificates);

  
  
  static void ParseAndStoreCertificates(::onc::ONCSource source,
                                        const DoneCallback& done_callback,
                                        base::ListValue* certificates,
                                        net::NSSCertDatabase* nssdb);

  
  
  static void ListCertsWithNickname(const std::string& label,
                                    net::CertificateList* result,
                                    net::NSSCertDatabase* target_nssdb);

  
  
  static bool DeleteCertAndKeyByNickname(const std::string& label,
                                         net::NSSCertDatabase* target_nssdb);

  
  
  static bool ParseAndStoreCertificate(
      bool allow_trust_imports,
      const base::DictionaryValue& certificate,
      net::NSSCertDatabase* nssdb,
      net::CertificateList* onc_trusted_certificates);

  
  
  
  
  static bool ParseServerOrCaCertificate(
      bool allow_trust_imports,
      const std::string& cert_type,
      const std::string& guid,
      const base::DictionaryValue& certificate,
      net::NSSCertDatabase* nssdb,
      net::CertificateList* onc_trusted_certificates);

  static bool ParseClientCertificate(const std::string& guid,
                                     const base::DictionaryValue& certificate,
                                     net::NSSCertDatabase* nssdb);

  
  scoped_refptr<base::SequencedTaskRunner> io_task_runner_;

  
  net::NSSCertDatabase* target_nssdb_;

  base::WeakPtrFactory<CertificateImporterImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CertificateImporterImpl);
};

}  
}  

#endif  
