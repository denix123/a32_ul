// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_CLOUD_USER_POLICY_SIGNIN_SERVICE_MOBILE_H_
#define CHROME_BROWSER_POLICY_CLOUD_USER_POLICY_SIGNIN_SERVICE_MOBILE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/policy/cloud/user_policy_signin_service_base.h"

class ProfileOAuth2TokenService;
class Profile;

namespace net {
class URLRequestContextGetter;
}

namespace policy {

class CloudPolicyClientRegistrationHelper;

class UserPolicySigninService : public UserPolicySigninServiceBase {
 public:
  
  UserPolicySigninService(
      Profile* profile,
      PrefService* local_state,
      DeviceManagementService* device_management_service,
      UserCloudPolicyManager* policy_manager,
      SigninManager* signin_manager,
      scoped_refptr<net::URLRequestContextGetter> system_request_context,
      ProfileOAuth2TokenService* token_service);
  virtual ~UserPolicySigninService();

  
  
  
  
  
  void RegisterForPolicy(const std::string& username,
                         const PolicyRegistrationCallback& callback);

#if !defined(OS_ANDROID)
  
  
  
  
  
  void RegisterForPolicyWithAccessToken(
      const std::string& username,
      const std::string& access_token,
      const PolicyRegistrationCallback& callback);

  
  static std::vector<std::string> GetScopes();
#endif

 private:
  void RegisterForPolicyInternal(
      const std::string& username,
      const std::string& access_token,
      const PolicyRegistrationCallback& callback);

  void CallPolicyRegistrationCallback(scoped_ptr<CloudPolicyClient> client,
                                      PolicyRegistrationCallback callback);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnInitializationCompleted(CloudPolicyService* service) OVERRIDE;

  
  
  virtual void ShutdownUserCloudPolicyManager() OVERRIDE;

  
  void RegisterCloudPolicyService();

  
  void CancelPendingRegistration();

  void OnRegistrationDone();

  scoped_ptr<CloudPolicyClientRegistrationHelper> registration_helper_;

  
  
  ProfileOAuth2TokenService* oauth2_token_service_;

  
  PrefService* profile_prefs_;

  base::WeakPtrFactory<UserPolicySigninService> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserPolicySigninService);
};

}  

#endif  