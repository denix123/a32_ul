// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_USER_NETWORK_CONFIGURATION_UPDATER_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_USER_NETWORK_CONFIGURATION_UPDATER_H_

#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/policy/network_configuration_updater.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class Profile;

namespace base {
class ListValue;
}

namespace user_manager {
class User;
}

namespace chromeos {

namespace onc {
class CertificateImporter;
}
}

namespace net {
class NSSCertDatabase;
class X509Certificate;
typedef std::vector<scoped_refptr<X509Certificate> > CertificateList;
}

namespace policy {

class PolicyService;

class UserNetworkConfigurationUpdater : public NetworkConfigurationUpdater,
                                        public KeyedService,
                                        public content::NotificationObserver {
 public:
  class WebTrustedCertsObserver {
   public:
    
    
    virtual void OnTrustAnchorsChanged(
        const net::CertificateList& trust_anchors) = 0;
  };

  virtual ~UserNetworkConfigurationUpdater();

  
  
  
  
  
  static scoped_ptr<UserNetworkConfigurationUpdater> CreateForUserPolicy(
      Profile* profile,
      bool allow_trusted_certs_from_policy,
      const user_manager::User& user,
      PolicyService* policy_service,
      chromeos::ManagedNetworkConfigurationHandler* network_config_handler);

  void AddTrustedCertsObserver(WebTrustedCertsObserver* observer);
  void RemoveTrustedCertsObserver(WebTrustedCertsObserver* observer);

  
  
  void GetWebTrustedCertificates(net::CertificateList* certs) const;

  
  void SetCertificateImporterForTest(
      scoped_ptr<chromeos::onc::CertificateImporter> certificate_importer);

 private:
  class CrosTrustAnchorProvider;

  UserNetworkConfigurationUpdater(
      Profile* profile,
      bool allow_trusted_certs_from_policy,
      const user_manager::User& user,
      PolicyService* policy_service,
      chromeos::ManagedNetworkConfigurationHandler* network_config_handler);

  
  void OnCertificatesImported(
      bool success,
      const net::CertificateList& onc_trusted_certificates);

  
  virtual void ImportCertificates(
      const base::ListValue& certificates_onc) OVERRIDE;
  virtual void ApplyNetworkPolicy(
      base::ListValue* network_configs_onc,
      base::DictionaryValue* global_network_config) OVERRIDE;

  
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  void CreateAndSetCertificateImporter(net::NSSCertDatabase* database);

  
  
  void SetCertificateImporter(
      scoped_ptr<chromeos::onc::CertificateImporter> certificate_importer);

  void NotifyTrustAnchorsChanged();

  
  bool allow_trusted_certificates_from_policy_;

  
  const user_manager::User* user_;

  ObserverList<WebTrustedCertsObserver, true> observer_list_;

  
  
  net::CertificateList web_trust_certs_;

  
  
  
  scoped_ptr<base::ListValue> pending_certificates_onc_;

  
  
  scoped_ptr<chromeos::onc::CertificateImporter> certificate_importer_;

  content::NotificationRegistrar registrar_;

  base::WeakPtrFactory<UserNetworkConfigurationUpdater> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserNetworkConfigurationUpdater);
};

}  

#endif  
