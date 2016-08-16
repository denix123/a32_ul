// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_CLOUD_USER_POLICY_SIGNIN_SERVICE_BASE_H_
#define CHROME_BROWSER_POLICY_CLOUD_USER_POLICY_SIGNIN_SERVICE_BASE_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/policy/core/common/cloud/cloud_policy_client.h"
#include "components/policy/core/common/cloud/cloud_policy_service.h"
#include "components/signin/core/browser/signin_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class PrefService;
class Profile;

namespace net {
class URLRequestContextGetter;
}

namespace policy {

class DeviceManagementService;
class UserCloudPolicyManager;

class UserPolicySigninServiceBase : public KeyedService,
                                    public CloudPolicyClient::Observer,
                                    public CloudPolicyService::Observer,
                                    public content::NotificationObserver,
                                    public SigninManagerBase::Observer {
 public:
  
  
  
  typedef base::Callback<void(const std::string& dm_token,
                              const std::string& client_id)>
      PolicyRegistrationCallback;

  
  
  typedef base::Callback<void(bool)> PolicyFetchCallback;

  
  UserPolicySigninServiceBase(
      Profile* profile,
      PrefService* local_state,
      DeviceManagementService* device_management_service,
      UserCloudPolicyManager* policy_manager,
      SigninManager* signin_manager,
      scoped_refptr<net::URLRequestContextGetter> system_request_context);
  virtual ~UserPolicySigninServiceBase();

  
  
  
  
  void FetchPolicyForSignedInUser(
      const std::string& username,
      const std::string& dm_token,
      const std::string& client_id,
      scoped_refptr<net::URLRequestContextGetter> profile_request_context,
      const PolicyFetchCallback& callback);

  
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnInitializationCompleted(CloudPolicyService* service) OVERRIDE;

  
  virtual void OnPolicyFetched(CloudPolicyClient* client) OVERRIDE;
  virtual void OnRegistrationStateChanged(CloudPolicyClient* client) OVERRIDE;
  virtual void OnClientError(CloudPolicyClient* client) OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;

  void SetSystemRequestContext(
      scoped_refptr<net::URLRequestContextGetter> request_context);

 protected:
  net::URLRequestContextGetter* system_request_context() {
    return system_request_context_.get();
  }

  
  
  scoped_ptr<CloudPolicyClient> CreateClientForRegistrationOnly(
      const std::string& username);

  
  
  
  bool ShouldLoadPolicyForUser(const std::string& email_address);

  
  
  
  
  void InitializeOnProfileReady(Profile* profile);

  
  
  
  
  
  void InitializeForSignedInUser(
      const std::string& username,
      scoped_refptr<net::URLRequestContextGetter> profile_request_context);

  
  
  
  
  virtual void InitializeUserCloudPolicyManager(
      const std::string& username,
      scoped_ptr<CloudPolicyClient> client);

  
  
  virtual void PrepareForUserCloudPolicyManagerShutdown();

  
  
  virtual void ShutdownUserCloudPolicyManager();

  
  
  UserCloudPolicyManager* policy_manager() { return policy_manager_; }
  SigninManager* signin_manager() { return signin_manager_; }

  content::NotificationRegistrar* registrar() { return &registrar_; }

 private:
  
  scoped_refptr<net::URLRequestContextGetter> CreateUserRequestContext(
      scoped_refptr<net::URLRequestContextGetter> profile_request_context);
  scoped_refptr<net::URLRequestContextGetter> CreateSystemRequestContext();

  
  
  UserCloudPolicyManager* policy_manager_;
  SigninManager* signin_manager_;

  content::NotificationRegistrar registrar_;

  PrefService* local_state_;
  DeviceManagementService* device_management_service_;
  scoped_refptr<net::URLRequestContextGetter> system_request_context_;

  base::WeakPtrFactory<UserPolicySigninServiceBase> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserPolicySigninServiceBase);
};

}  

#endif  
