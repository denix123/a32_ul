// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_CLIENT_CERT_UTIL_H_
#define CHROMEOS_NETWORK_CLIENT_CERT_UTIL_H_

#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/network/certificate_pattern.h"

namespace base {
class DictionaryValue;
}

namespace net {
struct CertPrincipal;
class X509Certificate;
typedef std::vector<scoped_refptr<X509Certificate> > CertificateList;
}

namespace chromeos {

namespace client_cert {

enum ConfigType {
  CONFIG_TYPE_NONE,
  CONFIG_TYPE_OPENVPN,
  CONFIG_TYPE_IPSEC,
  CONFIG_TYPE_EAP
};

struct CHROMEOS_EXPORT ClientCertConfig {
  ClientCertConfig();

  
  
  
  ConfigType location;

  
  std::string client_cert_type;

  
  CertificatePattern pattern;
};

bool CertPrincipalMatches(const IssuerSubjectPattern& pattern,
                          const net::CertPrincipal& principal);

CHROMEOS_EXPORT std::string GetPkcs11AndSlotIdFromEapCertId(
    const std::string& cert_id,
    int* slot_id);

CHROMEOS_EXPORT void GetClientCertFromShillProperties(
    const base::DictionaryValue& shill_properties,
    ConfigType* cert_config_type,
    int* tpm_slot,
    std::string* pkcs11_id);

CHROMEOS_EXPORT void SetShillProperties(const ConfigType cert_config_type,
                                        const int tpm_slot,
                                        const std::string& pkcs11_id,
                                        base::DictionaryValue* properties);

CHROMEOS_EXPORT void SetEmptyShillProperties(const ConfigType cert_config_type,
                                             base::DictionaryValue* properties);

bool IsCertificateConfigured(const client_cert::ConfigType cert_config_type,
                             const base::DictionaryValue& service_properties);

CHROMEOS_EXPORT void OncToClientCertConfig(
    const base::DictionaryValue& network_config,
    ClientCertConfig* cert_config);

}  

}  

#endif  
